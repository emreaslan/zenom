//==============================================================================
// UDPXn.hpp - Native UDP class.
//
// Author        : 
// Version       : 2.0.01 (Agustos 2009)
// Compatibility : NATIVE, GCC, rtnet 0.9.11
//==============================================================================

#ifndef _UDPXN_HPP_INCLUDED
#define _UDPXN_HPP_INCLUDED


#include <stdio.h> /* memset */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <rtnet.h>
#include <rtnet_config.h> 
#include <native/timer.h>



//==============================================================================
// class UDPXn
//------------------------------------------------------------------------------
// \brief
// UDP obje, rtnet uzerinden gercek zamanlı UDP haberlesmeye imkan saglarç

// <b>Example Program:</b>
//
// \include UDPXn.t.cpp
//==============================================================================


class UDPXn
{
    
public:

    /**
     * Constructor
     * Udp objesi olusturulur. Socket alma ve baglanma islemleri yapilmaktadir.
     * Bu islemlerde olusabilecek hata degerine getErrnoError() fonksiyonu ile
     * ulasılabilir.
     * @param port Baglanilacak port numarasi
     */
    UDPXn();

    /**
     * Destructor
     * Socket kapatilir.
     **/
    ~UDPXn();

    /**
     * Socket baglanma islemi yapilir.
     * @param port    Baglanilacak port numarasi
     * @return        Basarili olursa gonderilen mesaj boyutu, hata meydana
     *                gelirse -1 getirir, hata degerine getErrnoError()
     *                fonksiyonu ile ulasılabilir.
     */
    int bind(int portNo);

    /**
     * Mesaj gonderir.
     * @param buf     Gonderilecek mesaj
     * @param len     Gonerilecek mesaj uzunlugu
     * @param flags   Mesaj gonderim bayraklari
     * @return        Basarili olursa gonderilen mesaj boyutu, hata meydana
     *                gelirse -1 getirir, hata degerine getErrnoError()
     *                fonksiyonu ile ulasılabilir.
     */
    int send(const void *buf, size_t len, int flags);
    
    /**
     * Mesaj gonderir.
     * @param buf     Gonderilecek mesaj
     * @param len     Gonerilecek mesaj uzunlugu
     * @param flags   Mesaj gonderim bayraklari
     * @param destIp  Mesajin varis adresi
     * @return        Basarili olursa gonderilen mesaj boyutu, hata meydana
     *                gelirse -1 getirir, hata degerine getErrnoError()
     *                fonksiyonu ile ulasılabilir.
     */
    int send(const void* buf, size_t len, int flags, char* destIp);

    /**
     * Mesaj gonderir.
     * @param msg     Mesaj icerigi ve varis adresini iceren struct
     * @param flags   Mesaj gonderim bayraklari
     * @return        Basarili olursa gonderilen mesaj boyutu, hata meydana 
     *                gelirse -1 getirir, hata degerine getErrnoError()
     *                fonksiyonu ile ulasılabilir.
     */
    int send(struct msghdr *msg, int flags = 0);
    
    /**
     * Mesaj gonderir.
     * @param buf     Gonderilecek mesaj
     * @param len     Gonerilecek mesaj uzunlugu
     * @param flags   Mesaj gonderim bayraklari
     * @param from    Mesajin alinacagi adres
     * @param fromlen Mesaj adresi boyutu
     * @return        Basarili olursa gonderilen mesaj boyutu, hata meydana
     *                gelirse -1 getirir, hata degerine getErrnoError()
     *                fonksiyonu ile ulasılabilir.
     */
    int send(const void* buf, size_t len, int flags, const struct sockaddr* to,
    socklen_t tolen );


    /**
     * Mesaj alir.
     * @param buf     Gonderilecek mesaj
     * @param len     Gonerilecek mesaj uzunlugu
     * @param flags   Mesaj gonderim bayraklari
     * @return        Basarili olursa alinan mesaj boyutu, hata meydana gelirse
     *                -1 getirir, hata degerine getErrnoError() fonksiyonu ile
     *                ulasılabilir.
     */
    int recv(void *buf, size_t len, int flags);
        
    /**
     * Mesaj alir.
     * @param buf     Gonderilecek mesaj
     * @param len     Gonerilecek mesaj uzunlugu
     * @param flags   Mesaj gonderim bayraklari
     * @param recvIp  Mesajin varis adresi
     * @return        Basarili olursa alinan mesaj boyutu, hata meydana gelirse
     *                -1 getirir, hata degerine getErrnoError() fonksiyonu ile
     *                ulasılabilir.
     */
    int recv(void* buf, size_t len, int flags, char* recvIp);
    
    /**
     * Mesaj alir.
     * @param msg     Mesaj icerigi ve varis adresini iceren struct
     * @param flags   Mesaj gonderim bayraklari
     * @return        Basarili olursa alinan mesaj boyutu, hata meydana gelirse
     *                -1 getirir, hata degerine getErrnoError() fonksiyonu ile
     *                ulasılabilir.
     */
    int recv(struct msghdr *msg, int flags = 0);

    /**
     * Mesaj alir.
     * @param buf     Gonderilecek mesaj
     * @param len     Gonerilecek mesaj uzunlugu
     * @param flags   Mesaj gonderim bayraklari
     * @param from    Mesajin alinacagi adres
     * @param fromlen Mesaj adresi boyutu
     * @return        Basarili olursa alinan mesaj boyutu, hata meydana gelirse
     *                -1 getirir, hata degerine getErrnoError() fonksiyonu ile
     *                ulasılabilir.
     */
    int recv(void* buf, size_t len, int flags, struct sockaddr* from,
    socklen_t* fromlen );

    /**
     * Soketi kapatir.
     * @return Basarili olursa 0, hata meydana gelirse -1 getirir,
     *         hata degerine getErrnoError() fonksiyonu ile ulasılabilir.
     */
    int close();

    /**
     * Soketin mesaj alma ve yolla operasyonlarini kapatir.
     * @param how  Kapatilma bicimi
     *             SHUT_RD Mesaj alma operasyonlarini kapatir.
     *             SHUT_WR Mesaj gonderme operasyonlarini kapatir.
     *             SHUT_RDWR Mesaj gonderme/alma operasyonlarini kapatir.
     * @return     Basarili olursa 0, hata meydana gelirse -1 getirir,
     *             hata degerine getErrnoError() fonksiyonu ile ulasılabilir.
     */
    int shutdown(int how);

    /**
     * Socket seceneklerini getirir.
     * @param level   Stack level
     * @param optname Secenek ID
     * @param optval  Buffer degeri
     * @param optlen  Buffer boyutu
     * @return        Basarili olursa 0, hata meydana gelirse -1 getirir,
     *                hata degerine getErrnoError() fonksiyonu ile ulasılabilir.
     */
    int getSockOpt(int level, int optname, void* optval, socklen_t *optlen);

    /**
     * Socket seceneklerini gunceller.
     * @param level   Stack level
     * @param optname Secenek ID
     * @param optval  Buffer degeri
     * @param optlen  Buffer boyutu
     * @return        Basarili olursa 0, hata meydana gelirse -1 getirir,
     *                hata degerine getErrnoError() fonksiyonu ile ulasılabilir.
     */
    int setSockOpt(int level, int optname, const void *optval, socklen_t optlen);

    /**
     * Veri bekleme icin zaman asimi suresini gunceller.
     * @param timeout Zaman asimi suresi(nanosaniye)
     *                 0 (default) Mesaj gelmesini sonsuza kadar bekler.
     *                -1 Hemen geri doner (Non-Blocking)
     * @return Basarili olursa 0, hata meydana gelirse -1 getirir,
     *         hata degerine getErrnoError() fonksiyonu ile ulasılabilir.
     */
    int setTimeout( RTIME timeout );

    /**
     * Socket buffer havuzunu genisletir. Bu buffer, gelen verileri user buffera
     * kopyalamadan once saklanan alandir.
     * @param delta Buffer havuzunun genisletilecegi buyukluk. (default 16)
     * @return Basarili olursa 0, hata meydana gelirse -1 getirir,
     *         hata degerine getErrnoError() fonksiyonu ile ulasılabilir.
     */
    int extendPool(unsigned int delta);

    /**
     * Socket buffer havuzunu daraltir. Bu buffer, gelen verileri user buffera
     * kopyalamadan once saklanan alandir.
     * @param delta Buffer havuzunun genisletilecegi buyukluk. (default 16)
     * @return Basarili olursa 0, hata meydana gelirse -1 getirir,
     *         hata degerine getErrnoError() fonksiyonu ile ulasılabilir.
     */
    int shrinkPool(unsigned int delta);

    /**
     * En son meydana gelen hatayi getirir.
     * @return En son olusan hata kodu
     */
    inline int getErrnoError() const;  

private:
    
    /** Socket numarasi */
    int sock;

    /** Port numarasi */
    int port;

    struct sockaddr_in local_addr;
  
    // Hatalarin saklandigi degisken
    int d_errno;
};


//==============================================================================
// UDPXn::getErrnoError
//==============================================================================
int UDPXn::getErrnoError() const
{
    return d_errno;
}

#endif // _UDPXN_HPP_INCLUDED
