/*
 * File:   zenom.h
 * Author: root
 *
 * Created on October 27, 2010, 10:09 PM
 */

#ifndef ZENOM_H
#define	ZENOM_H

#include <fltk/run.h>
#include "zenomlogo.h"
#include "zenomwindow.h"

class Zenom
{
public:
    Zenom();
    ~Zenom();
    void show();

private:
	static void cbCloseLogo(void* pZenom);

	static void cbRedraw(void* pZenom);

	ZenomLogo* zenomLogo;
	ZenomWindow zenom;
};

#endif	/* ZENOM_H */

