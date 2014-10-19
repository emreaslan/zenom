//==============================================================================
// ZButton.cpp - Arayuz icin temel buton objesi.
//
// Author        :
// Version       : fltk 2.0
// Compatibility : GCC
//==============================================================================
#include "ZButton.h"

//==============================================================================
// ZButton::ZButton
//==============================================================================
ZButton::ZButton(int X, int Y, int W, int H, const char * name)
: Group(X, Y, W, H)
{
    box(fltk::BORDER_BOX);
    begin();
    zButton = new Button(1, 1, W-2, H-2, name);
    zButton->box(fltk::PLASTIC_UP_BOX);
    zButton->labelsize(13);
    zButton->color(fltk::GRAY65);
    zButton->highlight_color(fltk::GRAY40);
    end();
}

//==============================================================================
// ZButton::ZButton
//==============================================================================
ZButton::ZButton(const ZButton& orig)
: Group(orig.x(), orig.y(), orig.w(), orig.h(), orig.label())
{
    box(orig.box());
    begin();
    zButton = new Button(orig.zButton->x(), orig.zButton->y(), orig.zButton->w(),
            orig.zButton->h(), orig.zButton->label() );
    zButton->box(orig.zButton->box());
    zButton->labelsize(orig.zButton->labelsize());
    zButton->color(orig.zButton->color());
    zButton->highlight_color(orig.zButton->highlight_color());
    end();
}

//==============================================================================
// ZButton::~ZButton
//==============================================================================
ZButton::~ZButton()
{
    delete zButton;
}

