/* 
 * File:   MessageSend.cpp
 * Author: root
 * 
 * Created on September 10, 2009, 1:53 PM
 */

#include "RTMessageSend.h"

//==============================================================================
// RTMessageSend::communicate
//==============================================================================
void RTMessageSend::communicate()
{
    double packet[128];
    int packetIndex = 0;

    // Bilgiler paketlenir
    for(int i = 0; i < variableArray.getNumElements(); ++i)
    {
        for(int j = 0; j < variableArray.getElement(i)->getSize(); ++j)
        {
            packet[packetIndex] = variableArray.getElement(i)->getElement(j);
            ++packetIndex;
        }
    }
    udp.send(packet, sizeof(double)*128, 0, (struct sockaddr*)&sockAddr, sizeof(sockaddr_in));
}

