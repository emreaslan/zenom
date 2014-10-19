/* 
 * File:   Message.h
 * Author: root
 *
 * Created on September 10, 2009, 10:57 AM
 */

#ifndef _RTMESSAGE_H
#define	_RTMESSAGE_H

#include "Variable.h"
#include "Array.h"
#include <RowVector.hpp>
#include <ColumnVector.hpp>
#include <UDPXn.hpp>
#include <iostream>

using namespace std;

#define MESSAGESIZE 256



class RTMessage
{

public:

    RTMessage();
    
    ~RTMessage();

    int initialize(int port, char* ip);
    
    char* getIp() { return ipAddress; }

    virtual void communicate() = 0;
    
    /**
     * Degiskenleri pakete kaydeden fonksiyon
     *
     * @param variable  Kaydedilecek degisken
     * @param nm        Degiskenin ismi
     * @param desc      Degiskenin aciklamasi
     */
    bool add(double &variable);

    /**
     * Degiskenleri pakete kaydeden fonksiyon
     *
     * @param variable  Kaydedilecek degisken
     * @param nm        Degiskenin ismi
     * @param desc      Degiskenin aciklamasi
     */
    bool add(double *variable,int row = 1 , int col = 1  );

    /**
     * Degiskenleri pakete kaydeden fonksiyon
     *
     * @param variable  Kaydedilecek degisken
     * @param nm        Degiskenin ismi
     * @param desc      Degiskenin aciklamasi
     */
    bool add(double **variable,int row = 1 , int col = 1  );

    /**
     * Degiskenleri pakete kaydeden fonksiyon
     *
     * @param variable  Kaydedilecek degisken
     * @param nm        Degiskenin ismi
     * @param desc      Degiskenin aciklamasi
     */
    bool add(int **variable,int row = 1 , int col = 1  );

    /**
     * Degiskenleri pakete kaydeden fonksiyon
     *
     * @param variable  Kaydedilecek degisken
     * @param nm        Degiskenin ismi
     * @param desc      Degiskenin aciklamasi
     */
    bool add(int *variable,int row = 1 , int col = 1  );

    /**
     * Degiskenleri pakete kaydeden fonksiyon
     *
     * @param variable  Kaydedilecek degisken
     * @param nm        Degiskenin ismi
     * @param desc      Degiskenin aciklamasi
     */
    bool add(int &variable,int row = 1 , int col = 1  );


    /**
     * Degiskenleri pakete kaydeden fonksiyon
     *
     * @param varArray  Kaydedilecek degisken dizisi
     * @param nm        Degiskenin ismi
     * @param desc      Degiskenin aciklamasi
     */
    bool add(MatrixBase<double> &varMatrix);

    /**
     * Degiskenleri pakete kaydeden fonksiyon
     *
     * @param varArray  Kaydedilecek degisken dizisi
     * @param nm        Degiskenin ismi
     * @param desc      Degiskenin aciklamasi
     */
    bool add(MatrixBase<int> &varMatrix);


    /** Mesaj alim islemindeki bekleme suresini ayarlayan fonksiyon */
    void setTimeout( RTIME timeout );

    
protected:
    int mMessageSize;

    /** Gonderilecek degiskenlerini tutan dizi */
    Array< Variable* > variableArray;

    struct sockaddr_in sockAddr;

    UDPXn udp;

    struct in_addr ipAddr;
    
    char* ipAddress;
};

#endif	/* _MESSAGE_H */

