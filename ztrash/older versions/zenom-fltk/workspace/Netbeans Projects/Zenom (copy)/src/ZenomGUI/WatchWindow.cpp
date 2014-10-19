//==============================================================================
// WatchWindow.cpp - Watch Window implementasyonu
//
// Author        :
// Version       :
// Compatibility : GCC
//==============================================================================

#include"WatchWindow.h"

//==============================================================================
// WatchWindow::WatchWindow
//==============================================================================
WatchWindow::WatchWindow( LogVariableGUI* logVar )
 : Window( 0, 0, logVar->getCols()*150 + 5, logVar->getRows()*40+5, logVar->getName() )
{   
    logVariable = logVar;

    begin();
    SevenSegment* varSegment;
    for(int i = 0; i < logVariable->getCols(); ++i)
    {
        for(int j = 0; j < logVariable->getRows(); ++j)
        {
            varSegment = new SevenSegment(i*150+5, j*40+5, 145, 35);
            varSegment->value("0.0000");
            varSegment->textcolor(fltk::GREEN);
            varSegment->color(fltk::BLACK);
            sevenSegments.appendElement( varSegment );            
        }
    }    

    popupMenu = new PopupMenu(0,0,w(),h());
    popupMenu->begin();
    popupMenu->add("&Edit...",0,cbEditWindow);
    popupMenu->end();
    popupMenu->type(PopupMenu::POPUP3);
    end();
    resizable(this);
    show();

   

    //  ----- Edit Window -----
    editWindow = new Window(170, 135, "Edit 7Seg");
    editWindow->set_modal();
    editWindow->begin();

    editGbox  = new Group(5, 5, editWindow->w()-10, editWindow->h()-10);
    editGbox->box(fltk::EMBOSSED_BOX);

    editBGColorButton = new Button( 115, 10, 30, 20, "Background  " );
    editBGColorButton->align(fltk::ALIGN_LEFT);
    editBGColorButton->box(fltk::EMBOSSED_BOX);
    editBGColorButton->color(fltk::BLACK);
    editBGColorButton->callback( cbChangeColor );

    edit7SColorButton = new Button( 115, 40, 30, 20, "7Segment     " );
    edit7SColorButton->align(fltk::ALIGN_LEFT);
    edit7SColorButton->box(fltk::EMBOSSED_BOX);
    edit7SColorButton->color(fltk::GREEN);
    edit7SColorButton->callback( cbChangeColor );

    precisionInput = new ValueInput( 115, 70, 30, 20, "Precision      " );
    precisionInput->align(fltk::ALIGN_LEFT);
    precisionInput->box(fltk::EMBOSSED_BOX);
    precisionInput->step(1);
    precisionInput->maximum(8);
    precisionInput->minimum(1);
    precisionInput->value(4);
    precision = 4;
    
    editOK = new ZButton(30,100,50,23,"OK");
    editOK->button()->callback(cbEditWindowOK,this);


    editCancel = new ZButton(90,100,50,23,"Cancel");
    editCancel->button()->callback(cbEditWindowCancel,this);

    editWindow->end();
    editWindow->color(fltk::color(167,162,178));
    //  ----- Edit Window -----
}

//==============================================================================
// WatchWindow::~WatchWindow
//==============================================================================
WatchWindow::~WatchWindow()
{
    for(int i = 0; i < sevenSegments.getNumElements(); ++i)
        delete sevenSegments.getElement(i);
    delete popupMenu;

    // Edit Penceresi silinir
    delete editBGColorButton;
    delete edit7SColorButton;
    delete precisionInput;
    delete editCancel;
    delete editOK;
    delete editGbox;
    delete editWindow;

}

//==============================================================================
// WatchWindow::updateSevenSegment
//==============================================================================
void WatchWindow::updateSevenSegment()
{
    char buffer[100];
    int len;
    double value;
    // ilk eleman heape eklenen eleman sayisini verir
    int index = (int)logVariable->getHeapElement(0);

    // En son veriler alinir ve 7Segment degeri guncellenir.
    for(int i = 0; i < logVariable->getSize(); ++i)
    {
        value = logVariable->getHeapElement(index+i);
        if( value > 1000000000 || value < -1000000000)
        {
            sprintf( buffer,"nAn");
            sevenSegments.getElement(i)->textcolor(fltk::RED);
            sevenSegments.getElement(i)->color(fltk::BLACK);
            sevenSegments.getElement(i)->value(buffer);
        }
        else
        {
            sprintf( buffer,"%.8f",value );
            len = 0;
            while( buffer[len] != '.' )
                ++len;
            len += precision + 1;
            buffer[len] = '\0';
            sevenSegments.getElement(i)->value(buffer);
        }       
        sevenSegments.getElement(i)->redraw();
    }
}

//==============================================================================
// WatchWindow::setBackgroundColor
//==============================================================================
void WatchWindow::setBackgroundColor(int pColor)
{
    editBGColorButton->color(pColor);
    editBGColorButton->redraw();
    for(int i = 0; i < sevenSegments.getNumElements(); ++i)
    {
        sevenSegments.getElement(i)->color(editBGColorButton->color());
        sevenSegments.getElement(i)->redraw();
    }
 
}

//==============================================================================
// WatchWindow::setSevenSegmentColor
//==============================================================================
void WatchWindow::setSevenSegmentColor(int pColor)
{
    edit7SColorButton->color(pColor);
    edit7SColorButton->redraw();
    for(int i = 0; i < sevenSegments.getNumElements(); ++i)
    {
        sevenSegments.getElement(i)->textcolor(edit7SColorButton->color());
        sevenSegments.getElement(i)->redraw();
    }
}

//==============================================================================
// WatchWindow::setPrecision
//==============================================================================
void WatchWindow::setPrecision(int pPrecison)
{
    if(pPrecison > 8 || pPrecison < 1)
    {
        precisionInput->value(4);
        precision = 4;
    }
    else
    {
        precisionInput->value(pPrecison);
        precision = pPrecison;
    }

    char buffer[100];
    int len;
    sprintf( buffer,"%.8f", 0 );
    len = 0;
    while( buffer[len] != '.' )
        ++len;
    len += precision + 1;
    buffer[len] = '\0';

    for(int i = 0; i < sevenSegments.getNumElements(); ++i)
    {
        sevenSegments.getElement(i)->value(buffer);
        sevenSegments.getElement(i)->redraw();
    }
}

//==============================================================================
// WatchWindow::save
//==============================================================================
WatchConfig WatchWindow::save()
{
    WatchConfig rValue;

    rValue.logVariable = logVariable;
    
    rValue.x = x();
    rValue.y = y();
    rValue.w = w();
    rValue.h = h();

    rValue.backgroundColor = editBGColorButton->color();
    rValue.sevenSegmentColor = edit7SColorButton->color();
    rValue.precision = precision;   

    return rValue;
}


//==============================================================================
// WatchWindow::cbEditWindow
//==============================================================================
void WatchWindow::cbEditWindow(Widget *o, void* userData)
{
    userData = userData;
    WatchWindow* watch = (WatchWindow*) o->window();
    watch->editWindow->show();    
}

//==============================================================================
// WatchWindow::cbEditWindowOK
//==============================================================================
void WatchWindow::cbEditWindowOK(Widget *o, void* userData)
{
    o = o;
    WatchWindow* watch = (WatchWindow*) userData;
    
    for(int i = 0; i < watch->sevenSegments.getNumElements(); ++i)
    {
        watch->sevenSegments.getElement(i)->textcolor(watch->edit7SColorButton->color());
        watch->sevenSegments.getElement(i)->color(watch->editBGColorButton->color());
        watch->precision = (int)watch->precisionInput->value();
        
        watch->sevenSegments.getElement(i)->redraw();
    }
    watch->editWindow->hide();
}

//==============================================================================
// WatchWindow::cbEditWindowCancel
//==============================================================================
void WatchWindow::cbEditWindowCancel(Widget *o, void* userData)
{
    WatchWindow* watch = (WatchWindow*) userData;
    Window* editWindow = (Window*) o->window();
    watch->edit7SColorButton->color(watch->sevenSegments.getElement(0)->textcolor());
    watch->editBGColorButton->color(watch->sevenSegments.getElement(0)->color());
    watch->precisionInput->value(watch->precision);
    editWindow->hide();
}

//==============================================================================
// WatchWindow::cbChangeColor
//==============================================================================
void WatchWindow::cbChangeColor(Widget *o, long userData)
{
    userData = userData;
    Button *button = (Button*)o;
    uchar r, g, b;
    fltk::split_color(o->parent()->color(),r,g,b);

    if (!fltk::color_chooser("New color:", r,g,b))
        return;

    button->color(fltk::color(r,g,b));
    button->redraw(); 
}

//==============================================================================
// WatchWindow::handle
//==============================================================================
int WatchWindow::handle(int e)
{
    switch(e)
    {
        case FOCUS:
            for(int i = 0; i < sevenSegments.getNumElements(); ++i)
            {
                int h = sevenSegments.getElement(i)->h() * (7.00 / 10.00);
                int w = h * (3.00 / 5.00);
                sevenSegments.getElement(i)->unit_h(h);
                sevenSegments.getElement(i)->unit_w(w);
                sevenSegments.getElement(i)->thickness(w * (3.00 / 10.00));
                sevenSegments.getElement(i)->redraw();
            }            
            break;
    }

    return fltk::Window::handle(e);
}


//==============================================================================
// WatchWindow::resetSevenSegment
//==============================================================================
void WatchWindow::resetSevenSegment()
{
    for(int i = 0; i < sevenSegments.getNumElements(); ++i)
    {
        sevenSegments.getElement(i)->textcolor(edit7SColorButton->color());
        sevenSegments.getElement(i)->color(editBGColorButton->color());
        precision = (int)precisionInput->value();
        sevenSegments.getElement(i)->redraw();
    }
}
