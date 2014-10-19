/* 
 * File:   guiMessenger.h
 * Author: root
 *
 * Created on August 20, 2009, 10:22 AM
 */

#ifndef _GUIMESSENGER_H
#define	_GUIMESSENGER_H

#include "Constants.h"
#include <MessageQueueXn.hpp>
#include <iostream>

using namespace std;
/**
 * class guiMessenger
 * --------------
 *
 * Gui ile simulasyon arasinda mesaj alisverisini saglayan obje
 *
 */

class guiMessenger
{
public:
    /**
     * Constructor
     * Programin ismini alir ve bu isimde bir mesaj kuyrugu olusturur
     *
     * @param gui   Objenin gui tarafından olusturulma bilgisi
     * @param nm    Programin ismi
     */
     guiMessenger (char *nm,bool gui = false);

    /**
     * Destructor
     * Objenin yokedilmesinden sorumlu fonksiyon
     */
     ~guiMessenger ();

    /**
     * sendStartMessage
     * start mesaji gonderen fonksiyon
     *
     * @return  mesaj gonderim sonucu 0 ise islem basarili
     */
     int sendStartMessage();

    /**
     * sendPauseMessage
     * pause mesaji gonderen fonksiyon
     *
     * @return  mesaj gonderim sonucu 0 ise islem basarili
     */
     int sendPauseMessage();


    /**
     * sendStopMessage
     * stop mesaji gonderen fonksiyon
     *
     * @return  mesaj gonderim sonucu 0 ise islem basarili
     */
     int sendStopMessage();
     
     /**
     * sendActiveMessage
     * active mesaji gonderen fonksiyon
     *
     * @return  mesaj gonderim sonucu 0 ise islem basarili
     */
     int sendActiveMessage();

    /**
     * sendUnbindMessage
     * unbind mesaji gonderen fonksiyon
     *
     * @return  mesaj gonderim sonucu 0 ise islem basarili
     */
     int sendUnbindMessage();

    /**
     * sendBindMessage
     * bind mesaji gonderen fonksiyon
     *
     * @return  mesaj gonderim sonucu 0 ise islem basarili
     */
     int sendBindMessage();


    /**
     * receiveStartMessage
     * start mesaji alan fonksiyon
     *
     * @return  mesaj alimi sonucu 0 ise islem basarili
     */
     int receiveStartMessage();

    /**
     * receivePauseMessage
     * pause mesaji alan fonksiyon
     *
     * @return  mesaj alimi sonucu 0 ise islem basarili
     */
     int receivePauseMessage();


    /**
     * receiveStopMessage
     * stop mesaji alan fonksiyon
     *
     * @return  mesaj alim sonucu 0 ise islem basarili
     */
     int receiveStopMessage();

     /**
     * receiveActiveMessage
     * active mesaji alan fonksiyon
     *
     * @return  mesaj alim sonucu 0 ise islem basarili
     */
     int receiveActiveMessage();
    
    /**
     * receiveUnbindMessage
     * unbind mesaji alan fonksiyon
     *
     * @return  mesaj gonderim sonucu 0 ise islem basarili
     */
     int receiveUnbindMessage();


    /**
     * receiveBindMessage
     * bind mesaji alan fonksiyon
     *
     * @return  mesaj gonderim sonucu 0 ise islem basarili
     */
     int receiveBindMessage();

    /**
     * receiveMessage
     * mesaj alan fonksiyon
     *
     * @param   Mesajin yazilicagi yer
     * @return  mesaj alim sonucu 0 ise islem basarili
     */
    int receiveMessage(char *msgBuf);

    /**
     * sendMessage
     * mesaji gonderen fonksiyon
     *
     * @param   Gonderilecek mesaj
     * @return  mesaj alim sonucu 0 ise islem basarili
     */
    int sendMessage(char *msgBuf);

    inline int getErrnoError() const { return guiComQueue->getErrnoError(); }

private:

    /** Programin ismi */
    char *applicationName;

    /** Mesaj gonderimini yapacak obje */
    MessageQueueXn *guiComQueue;

    /** Objenin gui tarafindan olusturuldugu bilgisi*/
    bool isGui;

    /** Mesaj kuyrugu ismi */
    char *queueName;
};



#endif	/* _GUIMESSENGER_H */

