//==============================================================================
// controlVarWindow.cpp - Control Variable Window implementasyonu
//
// Author        :
// Version       :
// Compatibility : GCC
//==============================================================================

#include "logVarWindow.h"


//==============================================================================
// LogVarWindow::LogVarWindow
//==============================================================================
LogVarWindow::LogVarWindow( Array<LogVariableGUI*>& logVars, int mainfrequency, int mainduration  )
 : Window( 250, 100, "Log Variables" )
{
    LogVariableGUIs = &logVars;
    mainFrequency = mainfrequency;
    mainDuration = mainduration;

    if(LogVariableGUIs->getNumElements())
        fillWindow();
    else
        emptyWindow();

}

//==============================================================================
// LogVarWindow::~LogVarWindow
//==============================================================================
LogVarWindow::~LogVarWindow()
{
    if(LogVariableGUIs->getNumElements())
    {
        delete frequency;
        delete startTime;
        delete duration;
        delete sortByName;
        
        for(int i = 0; i < LogVariableGUIsGroups.getNumElements(); ++i)
        {
            // Inputlar silinir
            for(int j = 0; j < LogVariableGUIsGroups.getElement(i)->children(); ++j)
                delete LogVariableGUIsGroups.getElement(i)->child(j);
            delete LogVariableGUIsGroups.getElement(i);
        }
    
        delete scrollGroup;
    }
    delete gbox;
}

//==============================================================================
// LogVarWindow::update
//==============================================================================
void LogVarWindow::update(int mainfrequency, int mainduration)
{
    mainFrequency = mainfrequency;
    mainDuration = mainduration;

    for(int i = 0; i < LogVariableGUIsGroups.getNumElements(); ++i)
        changeInput(i);
}

//==============================================================================
// LogVarWindow::cbChangeInput
//==============================================================================
void LogVarWindow::cbChangeInput(Widget *o, long userData)
{
    LogVarWindow* logWindow = (LogVarWindow*) o->window();
    int index = (int) userData;

    logWindow->changeInput(index);
}

//==============================================================================
// LogVarWindow::changeInput
//==============================================================================
void LogVarWindow::changeInput( int index )
{
    //----- Log Variable frekans -----
    IntInput* input = (IntInput* )LogVariableGUIsGroups.getElement(index)->child(0);
    // Ana Frekansin sadece katlari girilebilir.
    if( input->ivalue() <= 0 || input->ivalue() > mainFrequency )
        input->value(mainFrequency);
    else if( mainFrequency % input->ivalue() )
    {
        int coefficient = mainFrequency / input->ivalue();
        while( mainFrequency % coefficient )
            ++coefficient;

        input->value(mainFrequency/coefficient);
        
    }
    LogVariableGUIs->getElement(index)->setFrequency(input->ivalue());
     //----------


    //----- Log Variable baslangic zamani -----
    input = (IntInput* )LogVariableGUIsGroups.getElement(index)->child(1);
    
    // Baslangic zamani ana programdan buyuk ise 0 atanir.
    if( input->ivalue() > mainDuration || input->ivalue() < 0 )
        input->value(0);   
    LogVariableGUIs->getElement(index)->setStartTime(input->ivalue());
    //----------

    //----- Log variable suresi ----- 
    int start = input->ivalue();
    input = (IntInput* )LogVariableGUIsGroups.getElement(index)->child(2);
    // Log suresi ve baslangıc degeri toplami ana sureden buyuk olamz
    if( start+input->ivalue() > mainDuration || input->ivalue() < 0)
        input->value(mainDuration-start);
    LogVariableGUIs->getElement(index)->setDuration(input->ivalue());
    //----------

    // Kullanici yanlis deger yazdigi zaman, 
    // hangi degerin kabul edildigini gormek icin
    controlInputValue(index);
    
    // Yeni degerler ana heape yazilir.
    LogVariableGUIs->getElement(index)->copyTFSDtoHeap();
}

//==============================================================================
// LogVarWindow::controlInputValue
//==============================================================================
void LogVarWindow::controlInputValue( int index )
{
    IntInput* input = (IntInput* )LogVariableGUIsGroups.getElement(index)->child(0);
    input->value(LogVariableGUIs->getElement(index)->getFrequency());

    input = (IntInput* )LogVariableGUIsGroups.getElement(index)->child(1);
    input->value(LogVariableGUIs->getElement(index)->getStartTime());

    input = (IntInput* )LogVariableGUIsGroups.getElement(index)->child(2);
    input->value(LogVariableGUIs->getElement(index)->getDuration());
}

//==============================================================================
// LogVarWindow::fillWindow
//==============================================================================
void LogVarWindow::fillWindow()
{
    // Input icin w h
    int wInput = 100, hInput = 23;

    // Pencere icin uygun boyut hesaplanir
    int nameOfWeight = 0;
    for(int i = 0; i < LogVariableGUIs->getNumElements(); ++i)
    {
        // Maksimum isim uzunlugu bulunur
        if( nameOfWeight < (int)strlen(LogVariableGUIs->getElement(i)->getName()) )
            nameOfWeight = strlen(LogVariableGUIs->getElement(i)->getName());
    }

    // isim icin gerekli uzunluk
    nameOfWeight = nameOfWeight * 7 + 10;

    if( LogVariableGUIs->getNumElements() < 4 )
        // Maksimum isim ve satir sayisana gore pencere boyutlanir
        resize( 3 * (wInput + 5) + 35 + nameOfWeight, (LogVariableGUIs->getNumElements()+1) * (hInput+12)+23);
    else
        // Maksimum isim ve satir sayisana gore pencere boyutlanir
        resize( 3 * (wInput + 5) + 35 + nameOfWeight, 5 * (hInput+12)+15);

    size_range(3 * (wInput + 5) + 35 + nameOfWeight, 100,
            3 * (wInput + 5) + 35 + nameOfWeight,
            (LogVariableGUIs->getNumElements()+1) * (hInput+12)+25);

    this->begin();

    gbox  = new Group(5, 5, w()-10, h()-10);
    gbox->box(fltk::EMBOSSED_BOX);
    
   
    sortByName = new Button (10,10,nameOfWeight-5,(hInput+7),"Name");
    sortByName->highlight_color(GRAY70);
    sortByName->color(GRAY80);
    sortByName->box(fltk::EMBOSSED_BOX);

    frequency = new Widget(0*(wInput + 5)+nameOfWeight+10, 10, wInput,(hInput+7));
    frequency->label("Frequency");
    frequency->box(fltk::ENGRAVED_BOX);
    frequency->color(GRAY80);

    startTime = new Widget(1*(wInput + 5)+nameOfWeight+10, 10, wInput,(hInput+7));
    startTime->label("Start Time");
    startTime->box(fltk::ENGRAVED_BOX);
    startTime->color(GRAY80);

    duration = new Widget(2*(wInput + 5)+nameOfWeight+10, 10, wInput,(hInput+7));
    duration->label("Duration");
    duration->box(fltk::ENGRAVED_BOX);
    duration->color(GRAY80);

    Group* cvGroup;
    IntInput* input;
    int y = 0;

    if( LogVariableGUIs->getNumElements() < 4 )
        scrollGroup  = new ScrollGroup(10, 45,
                3 *  (wInput + 5) + nameOfWeight + 15, 
                    (hInput+7)*LogVariableGUIs->getNumElements() + 10);
    else
        scrollGroup  = new ScrollGroup(10, 45,
                3 *  (wInput + 5) + nameOfWeight + 15, (hInput+7)*4 + 5);

    scrollGroup->begin();
    for(int i = 0; i < LogVariableGUIs->getNumElements(); ++i)
    {
        cvGroup = new Group(0, y, 3 *  (wInput + 5) + nameOfWeight, (hInput+7),
                LogVariableGUIs->getElement(i)->getName());


        if( i % 2)
            cvGroup->color(GRAY95);
        else
            cvGroup->color(GRAY85);

        cvGroup->box(fltk::BORDER_BOX);
        cvGroup->align(fltk::ALIGN_INSIDE_TOPLEFT);

        cvGroup->begin();

        input = new IntInput(0*(wInput + 5)+nameOfWeight, 3, wInput,hInput);
        input->value(LogVariableGUIs->getElement(i)->getFrequency());
        input->when(fltk::WHEN_ENTER_KEY);
        input->callback(cbChangeInput,i);

        input = new IntInput(1*(wInput + 5)+nameOfWeight, 3, wInput,hInput);
        input->value(LogVariableGUIs->getElement(i)->getStartTime());
        input->when(fltk::WHEN_ENTER_KEY);
        input->callback(cbChangeInput,i);

        input = new IntInput(2*(wInput + 5)+nameOfWeight, 3, wInput,hInput);
        input->value(LogVariableGUIs->getElement(i)->getDuration());
        input->when(fltk::WHEN_ENTER_KEY);
        input->callback(cbChangeInput,i);

        cvGroup->end();

        LogVariableGUIs->getElement(i)->copyTFSDtoHeap();
        LogVariableGUIsGroups.appendElement(cvGroup);
        y += (hInput+7) + 5;
    }
    scrollGroup->end();
    this->end();
    color(fltk::color(167,162,178));
    resizable(scrollGroup);


    update(mainFrequency, mainDuration);
}

//==============================================================================
// LogVarWindow::emptyWindow
//==============================================================================
void LogVarWindow::emptyWindow()
{
    begin();
    gbox  = new Group(5, 5, w()-10, h()-10);
    gbox->box(fltk::EMBOSSED_BOX);
    gbox->label("No Log Variable!\n(Forget register variable?)");
    gbox->labelsize(15);
    gbox->align(fltk::ALIGN_CENTER);
    end();

    size_range(250, 100, 250, 100);
}
