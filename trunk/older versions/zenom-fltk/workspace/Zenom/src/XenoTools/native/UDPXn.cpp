//==============================================================================
// UDPXn.hpp - Native UDP class.
//
// Author        :
// Version       : 2.0.01 (Agustos 2009)
// Compatibility : NATIVE, GCC, rtnet 0.9.11
//==============================================================================

#include "UDPXn.hpp"

//==============================================================================
// UDPXn::UDPXn
//==============================================================================
UDPXn::UDPXn()
{
    d_errno = 0;
    /* rt-socket olusturulur */
    sock = rt_dev_socket(AF_INET,SOCK_DGRAM,0);
    if (sock < 0)
    {
        d_errno = -sock;
    }
}

//==============================================================================
// UDPXn::~UDPXn
//==============================================================================
UDPXn::~UDPXn()
{
    rt_dev_close(sock);
}

//==============================================================================
// UDPXn::bind
//==============================================================================
int UDPXn::bind(int portNo)
{
    int ret;
    port = portNo;

    /* rt-socket porta baglanir */
    memset(&local_addr, 0, sizeof(struct sockaddr_in));
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(port);
    local_addr.sin_addr.s_addr = INADDR_ANY;
    ret = rt_dev_bind(sock, (struct sockaddr *)&local_addr, sizeof(struct sockaddr_in));
    if (ret < 0)
    {
        rt_dev_close(sock);
        d_errno = -ret;
        return -1;
    }
    return 0;
}
//==============================================================================
// UDPXn::send
//==============================================================================
int UDPXn::send(const void *buf, size_t len, int flags)
{
    int err = rt_dev_send(sock, buf, len, flags);
    if( 0 > err)
    {
        d_errno = -err;
        return -1;
    }
    else
        return err;
}

//==============================================================================
// UDPXn::send
//==============================================================================
int UDPXn::send(const void* buf, size_t len, int flags, char* destIp)
{
    struct in_addr dest_ip;
    struct sockaddr_in dest_addr;
    
    inet_aton(destIp, &dest_ip);

    // Mesajin gidecegi adres ayarlanir.
    memset(&dest_addr, 0, sizeof(struct sockaddr_in));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(port);
    dest_addr.sin_addr = dest_ip;

    return send(buf, len, flags, (struct sockaddr*)&dest_addr, sizeof(sockaddr_in));
}

//==============================================================================
// UDPXn::send
//==============================================================================
int UDPXn::send(struct msghdr *msg, int flags)
{
    int err = rt_dev_sendmsg(sock, msg, flags);
    if( 0 > err)
    {
        d_errno = -err;
        return -1;
    }
    else
        return err;
}

//==============================================================================
// UDPXn::send
//==============================================================================
int UDPXn::send(const void* buf, size_t len, int flags,
const struct sockaddr* to, socklen_t tolen )
{
    int err = rt_dev_sendto(sock, buf, len, flags, to, tolen);
    if( 0 > err)
    {
        d_errno = -err;
        return -1;
    }
    else
        return err;
}

//==============================================================================
// UDPXn::recv
//==============================================================================
int UDPXn::recv(void *buf, size_t len, int flags)
{
    int err = rt_dev_recv(sock, buf, len, flags);
    if( 0 > err)
    {
        d_errno = -err;
        return -1;
    }
    else
        return err;
}

//==============================================================================
// UDPXn::recv
//==============================================================================
int UDPXn::recv(void* buf, size_t len, int flags, char* recvIp)
{
    struct in_addr recv_ip;
    struct sockaddr_in recv_addr;
    socklen_t recv_addr_s;

    inet_aton(recvIp, &recv_ip);

    // Mesajin gidecegi adre ayarlanir.
    memset(&recv_addr, 0, sizeof(struct sockaddr_in));
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_port = htons(port);
    recv_addr.sin_addr = recv_ip;

    return recv(buf, len, flags, (struct sockaddr*)&recv_addr, &recv_addr_s );
}

//==============================================================================
// UDPXn::recv
//==============================================================================
int UDPXn::recv(struct msghdr *msg, int flags)
{
    int err = rt_dev_recvmsg(sock, msg, flags);
    if( 0 > err)
    {
        d_errno = -err;
        return -1;
    }
    else
        return err;
}

//==============================================================================
// UDPXn::recv
//==============================================================================
int UDPXn::recv(void* buf, size_t len, int flags, struct sockaddr* from, 
socklen_t* fromlen )
{
    int err = rt_dev_recvfrom(sock, buf, len, flags, from, fromlen);
    if( 0 > err)
    {
        d_errno = -err;
        return -1;
    }
    else
        return err;
}


//==============================================================================
// UDPXn::close
//==============================================================================
int UDPXn::close()
{
    int err = rt_dev_close(sock);
    if(err)
    {
        d_errno = -err;
        return -1;
    }
    else
        return 0;
}

//==============================================================================
// UDPXn::getSockOpt
//==============================================================================
int UDPXn::shutdown(int how)
{
    int err = rt_dev_shutdown(sock, how);
    if( 0 > err)
    {
        d_errno = -err;
        return -1;
    }
    else
        return 0;
}

//==============================================================================
// UDPXn::getSockOpt
//==============================================================================
int UDPXn::getSockOpt(int level, int optname, void *optval, socklen_t *optlen)
{
    int err = rt_dev_getsockopt(sock, level, optname, optval, optlen);
    if( 0 > err)
    {
        d_errno = -err;
        return -1;
    }
    else
        return 0;
}

//==============================================================================
// UDPXn::setSockOpt
//==============================================================================
int UDPXn::setSockOpt(int level, int optname, const void *optval, socklen_t optlen)
{
    int err = rt_dev_setsockopt(sock, level, optname, optval, optlen);
    if( 0 > err)
    {
        d_errno = -err;
        return -1;
    }
    else
        return 0;
    
}

//==============================================================================
// UDPXn::setTimeout
//==============================================================================
int UDPXn::setTimeout( RTIME timeout )
{
    int err = rt_dev_ioctl(sock, RTNET_RTIOC_TIMEOUT, &timeout);
    if( 0 > err)
    {
        d_errno = -err;
        return -1;
    }
    else
        return 0;
}

//==============================================================================
// UDPXn::extendPool
//==============================================================================
int UDPXn::extendPool(unsigned int delta)
{
    int err = rt_dev_ioctl(sock, RTNET_RTIOC_EXTPOOL, &delta);
    if( 0 > err)
    {
        d_errno = -err;
        return -1;
    }
    else
        return 0;
}

//==============================================================================
// UDPXn::shrinkPool
//==============================================================================
int UDPXn::shrinkPool(unsigned int delta)
{
    int err = rt_dev_ioctl(sock, RTNET_RTIOC_SHRPOOL, &delta);
    if( 0 > err)
    {
        d_errno = -err;
        return -1;
    }
    else
        return 0;
}
