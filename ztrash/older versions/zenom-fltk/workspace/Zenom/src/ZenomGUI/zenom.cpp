#include "zenom.h"

Zenom::Zenom()
{
	zenomLogo = new ZenomLogo();
	zenom.size_range(400,310,400,800);
}

Zenom::~Zenom()
{

}

void Zenom::show()
{
	zenomLogo->show();
	fltk::add_timeout(1.0, Zenom::cbCloseLogo, this);
}

void Zenom::cbCloseLogo(void* pZenom)
{
	Zenom* zenom = (Zenom*) (pZenom);
	zenom->zenomLogo->hide();
	delete zenom->zenomLogo;

	zenom->zenom.show();
	fltk::add_timeout(1.0/20, Zenom::cbRedraw, &(zenom->zenom));
}

void Zenom::cbRedraw(void* pZenomWindow)
{
	//TODO
    ZenomWindow* zenomWindow = (ZenomWindow*)pZenomWindow;
    zenomWindow->redraw();
    fltk::redraw();

    fltk::repeat_timeout(1.0/20,Zenom::cbRedraw, zenomWindow);
}
