//==============================================================================
// controlVarWindow.cpp - Control Variable Window implementasyonu
//
// Author        : Cuneyt AY
// Version       :
// Compatibility : GCC
//==============================================================================

#include "controlVarWindow.h"

//==============================================================================
// ControlVarWindow::ControlVarWindow
//==============================================================================
ControlVarWindow::ControlVarWindow( Array<ControlVariable*>& controlVars )
 : Window(250, 100, "Control Variables")
{
    controlVariables = &controlVars;

    if(controlVariables->getNumElements())
        fillWindow();
    else
        emptyWindow();
}

//==============================================================================
// ControlVarWindow::~ControlVarWindow
//==============================================================================
ControlVarWindow::~ControlVarWindow()
{
    if(controlVariablesGroups.getNumElements())
    {
        for(int i = 0; i < controlVariablesGroups.getNumElements(); ++i)
        {
            // Inputlar silinir
            for(int j = 0; j < controlVariablesGroups.getElement(i)->children(); ++j)
                delete controlVariablesGroups.getElement(i)->child(j);
            delete controlVariablesGroups.getElement(i);
        }

        delete applyButton;
        delete cancelButton;

        delete scrollGroup;
    }

    delete gbox;
}

//==============================================================================
// ControlVarWindow::cbChangeInput
//==============================================================================
void ControlVarWindow::cbChangeInput(Widget *o, long)
{
    ControlVarWindow* controlWindow = (ControlVarWindow*) o->window();

    controlWindow->applyButton->button()->activate();
    controlWindow->cancelButton->button()->activate();
}

//==============================================================================
// ControlVarWindow::cbApply
//==============================================================================
void ControlVarWindow::cbApply(Widget *o, long)
{
    ControlVarWindow* controlWindow = (ControlVarWindow*) o->window();
    FloatInput* input;

    for(int i = 0; i < controlWindow->controlVariables->getNumElements(); ++i)
    {
        for(int j = 0; j < controlWindow->controlVariables->getElement(i)->getSize(); ++j)
        {
            input = (FloatInput* )controlWindow->controlVariablesGroups.getElement(i)->child(j);
            controlWindow->controlVariables->getElement(i)->setElement(j, input->fvalue());
            // Guncellenen veriler kullaniciya gosterilir.
            // Gecersiz bir giris yapildiginda kullaniciya guncellenen
            // deger gosterilir
            input->value(controlWindow->controlVariables->getElement(i)->getElement(j));
        }
        // Yeni degerler ana heape yazilir.
        controlWindow->controlVariables->getElement(i)->copyToHeap();
    }

    controlWindow->applyButton->button()->deactivate();
    controlWindow->cancelButton->button()->deactivate();
}

//==============================================================================
// ControlVarWindow::cbCancel
//==============================================================================
void ControlVarWindow::cbCancel(Widget *o, long)
{
    ControlVarWindow* controlWindow = (ControlVarWindow*) o->window();
    FloatInput* input;
       
    for(int i = 0; i < controlWindow->controlVariables->getNumElements(); ++i)
    {
        for(int j = 0; j < controlWindow->controlVariables->getElement(i)->getSize(); ++j)
        {
            // Inputlardaki degerler control degiskenine atanir
            input = (FloatInput* )controlWindow->controlVariablesGroups.getElement(i)->child(j);
            input->value(controlWindow->controlVariables->getElement(i)->getElement(j));
        }
    }

    controlWindow->applyButton->button()->deactivate();
    controlWindow->cancelButton->button()->deactivate();
}

//==============================================================================
// ControlVarWindow::fillWindow
//==============================================================================
void ControlVarWindow::fillWindow()
{
    Group* cvGroup;
    FloatInput* input;
    int y = 0;
    int wInput = 125, hInput = 24; // Input icin w h   
    int weight = 0, height = 0, nameOfWeight = 10;

    // Pencere icin uygun boyut hesaplanir
    for(int i = 0; i < controlVariables->getNumElements(); ++i)
    {
        // Maksimum kolon uzunlugu bulunur
        if( weight < controlVariables->getElement(i)->getCols() )
            weight = controlVariables->getElement(i)->getCols();
        height += controlVariables->getElement(i)->getRows() * (hInput+7) + 5;

        // Maksimum isim uzunlugu bulunur
        if( nameOfWeight < (int)strlen(controlVariables->getElement(i)->getName()) )
            nameOfWeight = strlen(controlVariables->getElement(i)->getName());
    }

    // isim icin gerekli uzunluk
    nameOfWeight = nameOfWeight * 7 + 10;
    // Maksimum kolon, isim ve satir sayisana gore pencere boyutlanir
    resize(weight * (wInput + 5) + 40 + nameOfWeight, height + 50);
    size_range(100,100,weight * (wInput + 5) + 40 + nameOfWeight, height + 50);

    begin();
    gbox  = new Group(5, 5, w()-10, h()-10);
    gbox->box(fltk::EMBOSSED_BOX);

    scrollGroup  = new ScrollGroup(15, 15, w()-25, h()-50);
    scrollGroup->begin();

    
    for(int i = 0; i < controlVariables->getNumElements(); ++i)
    {
        cvGroup = new Group(0, y, controlVariables->getElement(i)->getCols() *  (wInput + 5) + nameOfWeight,
                controlVariables->getElement(i)->getRows() * (hInput+7),
                controlVariables->getElement(i)->getName());

        if( i % 2)
            cvGroup->color(GRAY95);
        else
            cvGroup->color(GRAY85);

        cvGroup->box(fltk::BORDER_BOX);
        cvGroup->align(fltk::ALIGN_INSIDE_TOPLEFT);

        cvGroup->begin();

        for(int rows = 0; rows < controlVariables->getElement(i)->getRows(); ++rows)
            for(int cols = 0; cols < controlVariables->getElement(i)->getCols(); ++cols)
            {
                input = new FloatInput(cols*(wInput + 5)+nameOfWeight, 3+rows*(hInput+7), wInput,hInput);
                input->value(controlVariables->getElement(i)->getElement(rows,cols));
                input->when(fltk::WHEN_CHANGED);
                input->callback(cbChangeInput);
             }

        // Control degiskenlerin ilk degerleri heape yazilir.
        controlVariables->getElement(i)->copyToHeap();

        cvGroup->end();

        controlVariablesGroups.appendElement(cvGroup);
        y += controlVariables->getElement(i)->getRows() * (hInput+7) + 5;
    }
    scrollGroup->end();

    applyButton = new ZButton( scrollGroup->w() / 2 - 65, scrollGroup->h() + 15, 67, 24, "Apply" );
    applyButton->button()->callback(cbApply);
    applyButton->button()->deactivate();

    cancelButton = new ZButton( scrollGroup->w() / 2 + 10, scrollGroup->h() + 15, 67, 24, "Cancel" );
    cancelButton->button()->callback(cbCancel);
    cancelButton->button()->deactivate();

    end();

    resizable(scrollGroup);   
}

//==============================================================================
// ControlVarWindow::emptyWindow
//==============================================================================
void ControlVarWindow::emptyWindow()
{
    begin();
    gbox  = new Group(5, 5, w()-10, h()-10);
    gbox->box(fltk::EMBOSSED_BOX);
    gbox->label("No Control Variable!");
    gbox->labelsize(15);
    gbox->align(fltk::ALIGN_CENTER);
    end();

    resize(250, 100);
    size_range(250, 100, 250, 100);
}



