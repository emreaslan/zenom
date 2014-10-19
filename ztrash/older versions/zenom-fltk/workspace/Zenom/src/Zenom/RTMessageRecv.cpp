/* 
 * File:   MessageRecv.cpp
 * Author: root
 * 
 * Created on September 10, 2009, 1:55 PM
 */

#include "RTMessageRecv.h"

//==============================================================================
// RTMessageRecv::RTMessageRecv
//==============================================================================
RTMessageRecv::RTMessageRecv()
{

}


//==============================================================================
// RTMessageRecv::communicate
//==============================================================================
void RTMessageRecv::communicate()
{
    int messageSize = 128;
    double* packet = new double[messageSize];
    int packetIndex = 0;
    socklen_t fromlen;

    // Hata olursa bilgiler guncellenmez
    if( udp.recv(packet, sizeof(double)*messageSize, 0, (struct sockaddr*)&sockAddr, &fromlen) == -1 )
    {
        cout << "Recv: " << strerror(udp.getErrnoError()) << endl;
        return;
    }
    
    // Bilgiler cikartilir.
    for(int i = 0; i < variableArray.getNumElements(); ++i)
    {
        for(int j = 0; j < variableArray.getElement(i)->getSize(); ++j)
        {
            variableArray.getElement(i)->setElement(j, packet[packetIndex]);
            //cout << "Message: " << packet[messageSize-1] << endl;
            ++packetIndex;
        }
    }
    delete[] packet;  
}

