/*
 * File:   zenomstartup.h
 * Author: root
 *
 * Created on October 27, 2010, 10:09 PM
 */

#ifndef ZENOMLOGO_H
#define	ZENOMLOGO_H

#include <fltk/Monitor.h>
#include <fltk/ShapedWindow.h>
#include <fltk/xpmImage.h>
#include <fltk/xbmImage.h>
#include <fltk/run.h>

using namespace fltk;

class ZenomLogo : public ShapedWindow
{
public:
    ZenomLogo();
    ~ZenomLogo();

private:

	void initLogo();
	void initLogoShape();

    Widget *imageWidget;
    xbmImage* xbm;
    xpmImage* xpm;

	char* zenomLogo[507];
	char zenomLogoShape[15750];
	int zenomLogoShapeWidth;
	int zenomLogoShapeHeight;
};

#endif	/* ZENOMLOGO_H */

