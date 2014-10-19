#ifndef _ZBUTTON_H
#define	_ZBUTTON_H

#include <fltk/Button.h>
#include <fltk/Group.h>

using namespace fltk;

/**
 * ZButton class.
 * Arayuz icin temel buton objesi.
 *
 * not: Etrafina border koymak icin group siniftan turetildi
 */
        

class ZButton : public Group
{
public:

    /**
     * Constructor
     * Temel ozelliklere sahip buton olusturur.
     * @param X     Butonun gosterilecegi x ekseni degeri
     * @param Y     Butonun gosterilecegi y ekseni degeri
     * @param W     Buton genisligi
     * @param H     Buton yuksekligi
     * @param name  Buton basligi
     */
    ZButton(int X, int Y, int W, int H, const char * name);


    /**
     * Copy Constructor
     * Temel ozelliklere sahip buton olusturur.
     * @param orig  Kopyasi alinacak buton
     */
    ZButton(const ZButton& orig);
    
    /**
     * Destructor
     * Sistemden alinan yerler geri verilir.
     */
    virtual ~ZButton();

    /**
     * Buton uzerindeki degisikler bu fonksiyon ile buton objesi elde edilerek
     * gerceklestirilir.
     * @return button objesi getirilir.
     */
    inline Button* button() { return zButton; }
    
private:

    /** Buton degiskeni */
    Button* zButton;

};

#endif	/* _ZBUTTON_H */

