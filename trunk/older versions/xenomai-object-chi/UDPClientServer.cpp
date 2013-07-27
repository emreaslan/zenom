//==============================================================================
// UDPClientServer.cpp - UDP Client/server based on BSD socket API 
//
// Author        : Vilas Kumar Chitrakaran
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================

#include "UDPClientServer.hpp"

//==============================================================================
// UDPServerXp::UDPServerXp
//==============================================================================
UDPServerXp::UDPServerXp()
{
 d_init = false;
 d_fd = -1;
 d_rcvBuf = NULL;
 d_rcvBufSize = 0;
 setError(0, "UDPServerXp");
}


UDPServerXp::UDPServerXp(int port, int maxMsgSize, int bdp)
{
 d_init = false;
 d_fd = -1;
 d_rcvBuf = NULL;
 d_rcvBufSize = 0;
 
 // initialize
 if( init(port, maxMsgSize, bdp) == -1)
  return;
 
 setError(0, "UDPServerXp");
}


//==============================================================================
// UDPServerXp::~UDPServerXp
//==============================================================================
UDPServerXp::~UDPServerXp()
{
 if(d_fd)
 {
  close(d_fd);
  d_fd = -1;
 }

 if( d_rcvBuf )
 {
  free(d_rcvBuf);
  d_rcvBuf = NULL;
 }
 d_init = false;
}


//==============================================================================
// UDPServerXp::doMessageCycle
//==============================================================================
void UDPServerXp::doMessageCycle()
{
 if(!d_init)
 {
  d_status.setReport(-1, "doMessageCycle: server not initialized");
  return;
 }
 
 struct sockaddr_in clntAddr;
 int clntAddrLen, msgSize;

 clntAddrLen = sizeof(clntAddr);
 while(1)
 {
  // exit if we must
  pthread_testcancel();

  // wait for messages
  if( (msgSize = recvfrom(d_fd, d_rcvBuf, d_rcvBufSize, 0, 
      (struct sockaddr *) &clntAddr, (socklen_t *)&clntAddrLen)) == -1 )
  {
   setError(EIO, "doMessageCycle(recvfrom)");
   continue;
  }

  // Call user implemented function
  const char *outMsgBuf;
  int outMsgLen;
  outMsgBuf = receiveAndReply(d_rcvBuf, msgSize, &outMsgLen);

  if(outMsgBuf == NULL)
   continue;
   
  // reply to client
  if( sendto(d_fd, outMsgBuf, outMsgLen, 0, 
      (struct sockaddr *) &clntAddr, clntAddrLen) != outMsgLen )
  {
   setError(EIO, "doMessageCycle(sendto)");
   continue;
  }
 } // end while
}


//==============================================================================
// UDPServerXp::receiveAndReply
//==============================================================================
const char *UDPServerXp::receiveAndReply(const char *inMsgBuf, int inMsgLen, int *outMsgLen)
{
 inMsgBuf = inMsgBuf;
 inMsgLen = inMsgLen;
 *outMsgLen = 0;
 return NULL;
}


//==============================================================================
// UDPServerXp::init
//==============================================================================
int UDPServerXp::init(int port, int maxMsgSize, int bdp)
{
 struct sockaddr_in name;
 int sockBufSize = bdp * 1024;
 
 if(d_init)
 {
  if(d_fd)
  {
   close(d_fd);
   d_fd = -1;
  }
 }
 d_init = false;

 // Create an endpoint for communication
 if( (d_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
 {
  setError(errno, "init(socket)");
  d_fd = -1;
  return -1;
 }
 
 // Allow reuse of port 
 int yes = 1;
 if( setsockopt(d_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
 {
  setError(errno, "init(setsockopt) SO_REUSEADDR");
  close(d_fd);
  d_fd = -1;
  return -1;
 }
 
 // set suggested optimal socket buffer sizes.
 if( sockBufSize != 0 ) {
  if( setsockopt(d_fd, SOL_SOCKET, SO_SNDBUF, (char *)&sockBufSize, sizeof(int)) == -1)
  {
   setError(errno, "init(setsockopt-SO_SNDBUF)");
   close(d_fd);
   d_fd = -1;
   return -1;
  }
  if( setsockopt(d_fd, SOL_SOCKET, SO_RCVBUF, (char *)&sockBufSize, sizeof(int)) == -1)
  {
   setError(errno, "init(setsockopt-SO_RCVBUF)");
   close(d_fd);
   d_fd = -1;
   return -1;
  }
 }
 
 // bind a name to the socket
 name.sin_family = AF_INET;
 name.sin_port = htons(port);
 name.sin_addr.s_addr = htonl(INADDR_ANY);
 memset(&(name.sin_zero), '\0', 8);
 if( bind(d_fd, (struct sockaddr *)&name, sizeof(struct sockaddr)) == -1)
 {
  setError(errno, "init(bind)");
  close(d_fd);
  d_fd = -1;
  return -1;
 }

 // Create the buffer to store client messages
 d_rcvBuf = (char *)realloc(d_rcvBuf, maxMsgSize * sizeof(char));
 if(d_rcvBuf == NULL)
 {
  setError(ENOMEM, "UDPServerXp(malloc)");
  close(d_fd);
  d_fd = -1;
  return -1;
 }
 d_rcvBufSize = maxMsgSize;
 d_init = true;
 
 return 0;
}


//==============================================================================
// UDPServerXp::getStatusCode
//==============================================================================
int UDPServerXp::getStatusCode() const
{
 return d_status.getReportCode();
}


//==============================================================================
// UDPServerXp::getStatusMessage
//==============================================================================
const char *UDPServerXp::getStatusMessage() const
{
 return d_status.getReportMessage();
}


//==============================================================================
// UDPServerXp::setError
//==============================================================================
void UDPServerXp::setError(int code, const char *functionName)
{
 char buf[80];
 snprintf(buf, 80, "%s: %s", functionName, strerror(code));
 d_status.setReport(code, buf);
}


//==============================================================================
// UDPClientXp::UDPClientXp
//==============================================================================
UDPClientXp::UDPClientXp()
{
 d_fd = -1;
 d_init = false;
 d_serverName = NULL;
 d_serverPort = 0;
 d_recvTimeout.tv_sec = 1;
 d_recvTimeout.tv_usec = 0;
 d_bdp = 0;
 setError(0, "UDPClientXp");
}


UDPClientXp::UDPClientXp(const char *serverIp, int port, struct timeval &t, int bdp)
{
 d_init = false;
 d_serverName = NULL;
 d_serverPort = 0;
 d_fd = -1;
 d_recvTimeout.tv_sec = 1;
 d_recvTimeout.tv_usec = 0;
 d_bdp = 0;
 
 // init connection to server
 if( init(serverIp, port, t, bdp) == -1 )
  return;
 
 setError(0, "UDPClientXp");
}


//==============================================================================
// UDPClientXp::~UDPClientXp
//==============================================================================
UDPClientXp::~UDPClientXp()
{
 if(d_fd)
 {
  close(d_fd);
  d_fd = -1;
 }
 if(d_serverName)
  free(d_serverName);
}


//==============================================================================
// UDPClientXp::sendAndReceive
//==============================================================================
int UDPClientXp::sendAndReceive(char *outMsgBuf, int outMsgLen,
                     char *inMsgBuf, int inBufLen, int *inMsgLen)
{
 int serverAddrLen;
 struct sockaddr_in fromAddress;
 char info[80];
 
 if(!d_init)
 {
  d_status.setReport(-1, "sendAndReceive: client not initialized");
  return -1;
 }

 // initialize connection again if we lost it due to error.
 if( fcntl(d_fd, F_GETFL) == -1 )
 {
  if( init(d_serverName, d_serverPort, d_recvTimeout, d_bdp) == -1 )
   return -1;
 }

 // check buffer pointers
 if( outMsgBuf == NULL )
 {
  d_status.setReport(EINVAL, "sendAndReceive: invalid buffer");
  return -1;
 }

 // write message to server
 serverAddrLen = sizeof(struct sockaddr_in);
 if( sendto(d_fd, outMsgBuf, outMsgLen, 0, (struct sockaddr *)&d_server, 
     serverAddrLen) < outMsgLen )
 {
  setError(errno, "sendAndReceive(send)");
  close(d_fd);
  return -1;
 }
 
 if( inMsgBuf == NULL)
  return 0;


 // receive reply
 if( (*inMsgLen = recvfrom(d_fd, inMsgBuf, inBufLen, 0, (struct sockaddr *)&fromAddress, 
     (socklen_t *)&serverAddrLen)) == -1 )
 { 
  setError(errno, "sendAndReceive(recv)");
  close(d_fd);
  return -1;
 }

 // received reply from someone else
 if(fromAddress.sin_addr.s_addr != d_server.sin_addr.s_addr)
 {
  snprintf(info, 80, "sendAndReceive(recv): Received message from some other source");
  d_status.setReport(-1, info);
  close(d_fd);
  d_fd = -1;
  return -1;
 }
 
 return 0;
} 
                   

//==============================================================================
// UDPClientXp::init
//==============================================================================
int UDPClientXp::init(const char *serverIp, int port, struct timeval &timout, int bdp)
{
 struct hostent *server;
 struct sockaddr_in clientSock;
 char info[80];
 
 d_recvTimeout.tv_sec = timout.tv_sec;
 d_recvTimeout.tv_usec = timout.tv_usec;
 d_bdp = bdp;

 if(d_fd)
 {
  close(d_fd);
  d_fd = -1;
 }

 d_init = false;
 
 // copy the server name
 int nlen;
 nlen = strlen(serverIp);
 if( !d_serverName ) {
  d_serverName = (char *)realloc(d_serverName, (nlen+1) * sizeof(char));
  if( d_serverName == NULL ) {
   setError(-1, "init(realloc)");
   return -1;
  }
  strncpy(d_serverName, serverIp, nlen);
  d_serverName[nlen] = '\0';
 }
 else if(strncmp(d_serverName, serverIp, nlen)) {
  d_serverName = (char *)realloc(d_serverName, (nlen+1) * sizeof(char));
  if( d_serverName == NULL ) {
   setError(-1, "init(realloc)");
   return -1;
  }
  strncpy(d_serverName, serverIp, nlen);
  d_serverName[nlen] = '\0';
 }
 d_serverPort = port;

 // set up client socket info
 clientSock.sin_family=AF_INET;
 clientSock.sin_addr.s_addr=htonl(INADDR_ANY);
 clientSock.sin_port=htons(0);
 memset(&(clientSock.sin_zero), '\0', 8);

 // open client socket
 if( (d_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
 {
  setError(errno, "init(socket)");
  return -1;
 }

 // set suggested optimal socket buffer sizes.
 int yes = d_bdp * 1024;
 if( yes != 0 ) {
  if( setsockopt(d_fd, SOL_SOCKET, SO_SNDBUF, (char *)&yes, sizeof(int)) == -1)
  {
   setError(errno, "init(setsockopt-SO_SNDBUF)");
   close(d_fd);
   d_fd = -1;
   return -1;
  }

  // set suggested optimal socket buffer sizes.
  if( setsockopt(d_fd, SOL_SOCKET, SO_RCVBUF, (char *)&yes, sizeof(int)) == -1)
  {
   setError(errno, "init(setsockopt-SO_RCVBUF)");
   close(d_fd);
   d_fd = -1;
   return -1;
  }
 }

 // set receive timeout 
 if( setsockopt(d_fd, SOL_SOCKET, SO_RCVTIMEO, &d_recvTimeout, 
     sizeof(struct timeval)) == -1)
 {
  setError(errno, "init(setsockopt) SO_RCVTIMEO");
  close(d_fd);
  d_fd = -1;
  return -1;
 }

 // bind client socket
 if( bind(d_fd, (struct sockaddr *)&clientSock, sizeof(struct sockaddr)) == -1)
 {
  setError(errno, "init(bind)");
  close(d_fd);
  d_fd = -1;
  return -1;
 }

 // get network server entry
 server = gethostbyname(serverIp);
 if( server == NULL )
 {
  snprintf(info, 80, "gethostbyname %s", hstrerror(h_errno));
  d_status.setReport(h_errno, info);
  close(d_fd);
  d_fd = -1;
  return -1;
 }
 
 // server socket info
 d_server.sin_family = AF_INET;
 d_server.sin_port = htons(port);
 d_server.sin_addr.s_addr = *((in_addr_t *)server->h_addr);
 memset(&(d_server.sin_zero), '\0', 8);

 d_init = true; 
 return 0;
}


//==============================================================================
// UDPClientXp::getStatusCode
//==============================================================================
int UDPClientXp::getStatusCode() const
{
 return d_status.getReportCode();
}


//==============================================================================
// UDPClientXp::getStatusMessage
//==============================================================================
const char *UDPClientXp::getStatusMessage() const
{
 return d_status.getReportMessage();
}


//==============================================================================
// UDPClientXp::setError
//==============================================================================
void UDPClientXp::setError(int code, const char *functionName)
{
 char buf[80];
 snprintf(buf, 80, "%s: %s", functionName, strerror(code));
 d_status.setReport(code, buf);
}
