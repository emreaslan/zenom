/* 
 * File:   TextDisplayWidget.h
 * Author: root
 *
 * Created on October 24, 2010, 10:23 AM
 */

#ifndef TEXTDISPLAYWIDGET_H
#define	TEXTDISPLAYWIDGET_H

#include <iostream>
#include <signal.h>
#include <cstring>

#include <fltk/TextDisplay.h>
#include <fltk/Output.h>

using namespace fltk;

class TextDisplayWidget
{
   friend class ZenomWindow;
public:
    TextDisplayWidget();
    ~TextDisplayWidget();
    static void initialize(const int pWindowX, const int pWindowY);
    static void destroy();
    static void printText(const char *pInfo, int pErrCode = 0);

private:
    static const char *getDateAndTime();
    static TextBuffer *mOutputBuffer;
    static TextDisplay *mTextDisplay;
};

#endif	/* TEXTDISPLAYWIDGET_H */

