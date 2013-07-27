#include "WatchSelectWindow.h"

//==============================================================================
// WatchSelectWindow::WatchSelectWindow
//==============================================================================
WatchSelectWindow::WatchSelectWindow( Array< LogVariableGUI* >& logVarGUIArray )
 : Window( 240, 230, "Select a log variable:" )
{
    logVariableGUIArray = &logVarGUIArray;

    color(fltk::color(167,162,178));
    
    begin();    
    gbox  = new Group(5, 5, w()-10, h()-10);
    gbox->box(fltk::EMBOSSED_BOX);
    selectionBrowser = new MultiBrowser(10, 10, w()-20, h()-50);

    watchButton = new ZButton(15, 195, 65, 22, "Watch");
    watchButton->button()->callback((Callback*)this->cbWatch,this);

    watchAllButton = new ZButton(85, 195, 65, 22, "Watch All");
    watchAllButton->button()->callback((Callback*)this->cbWatchAll,this);

    cancelButton = new ZButton(155, 195, 65, 22, "Cancel");
    cancelButton->button()->callback((Callback*)this->cbCancel,this);
    end();

    for(int i = 0; i < logVariableGUIArray->getNumElements(); ++i)
        selectionBrowser->add(logVariableGUIArray->getElement(i)->getName());

}

//==============================================================================
// WatchSelectWindow::~WatchSelectWindow
//==============================================================================
WatchSelectWindow::~WatchSelectWindow()
{
    for(int i = 0; i < watchWindows.getNumElements(); ++i )
        delete watchWindows.getElement(i);

    delete gbox;
    delete selectionBrowser;
    delete watchButton;
    delete watchAllButton;
    delete cancelButton;
}

//==============================================================================
// WatchSelectWindow::cbWatch
//==============================================================================
void WatchSelectWindow::cbWatch(Widget* w, void* arg)
{
    arg = arg;
    WatchSelectWindow *watchSelect = (WatchSelectWindow*)w->window();
    Array< WatchWindow* >* watchWindows = &(watchSelect->watchWindows);
    MultiBrowser* selectionBrowser = watchSelect->selectionBrowser;
    Array< LogVariableGUI* >* logVariableGUIArray = watchSelect->logVariableGUIArray;

    int i = 0;
    while( i < watchWindows->getNumElements())
    {
        if(!watchWindows->getElement(i)->visible())
        {
            delete watchWindows->getElement(i);
            watchWindows->removeElement(i);
        }
        else
            ++i;
    }

    /** Secili olan index numarasindaki degisken icin watch window acilir.*/
    for( int i = 0;  i < selectionBrowser->size(); ++i )
        if(selectionBrowser->selected(i))
        {
            watchWindows->appendElement( new WatchWindow ( logVariableGUIArray->getElement(i)) );
        }

    //watchSelect->hide();
}

//==============================================================================
// WatchSelectWindow::cbWatchAll
//==============================================================================
void WatchSelectWindow::cbWatchAll(Widget* w, void* arg)
{
    arg = arg;
    WatchSelectWindow *watchSelect = (WatchSelectWindow*)w->window();
    Array< WatchWindow* >* watchWindows = &(watchSelect->watchWindows);
    MultiBrowser* selectionBrowser = watchSelect->selectionBrowser;
    Array< LogVariableGUI* >* logVariableGUIArray = watchSelect->logVariableGUIArray;

    for( int i = 0;  i < selectionBrowser->size(); ++i )
    {
        watchWindows->appendElement(new WatchWindow ( logVariableGUIArray->getElement(i)) );
    }

    //watchSelect->hide();
}

//==============================================================================
// WatchSelectWindow::cbCancel
//==============================================================================
void WatchSelectWindow::cbCancel(Widget* w, void* arg)
{
    arg = arg;
    WatchSelectWindow *watchSelect = (WatchSelectWindow*)w->window();
    watchSelect->hide();
}

//==============================================================================
// WatchSelectWindow::updateSevenSegments
//==============================================================================
void WatchSelectWindow::updateSevenSegments()
{
    for(int i = 0; i < watchWindows.getNumElements(); ++i)
        watchWindows.getElement(i)->updateSevenSegment();
}

//==============================================================================
// WatchSelectWindow::resetSevenSegments
//==============================================================================
void WatchSelectWindow::resetSevenSegments()
{
    for(int i = 0; i < watchWindows.getNumElements(); ++i)
        watchWindows.getElement(i)->resetSevenSegment();
}

//==============================================================================
// WatchSelectWindow::createWatchWindows
//=============================================================================
void WatchSelectWindow::load(Array<WatchConfig>& watchWindowArray)
{
    WatchWindow *watch;
    for(int i = 0; i < watchWindowArray.getNumElements(); ++i)
    {
        watch = new WatchWindow ( watchWindowArray.getElement(i).logVariable );

        watch->resize(watchWindowArray.getElement(i).x , watchWindowArray.getElement(i).y ,
                watchWindowArray.getElement(i).w, watchWindowArray.getElement(i).h);
        watch->layout();
        
        watch->setBackgroundColor(watchWindowArray.getElement(i).backgroundColor);
        watch->setSevenSegmentColor(watchWindowArray.getElement(i).sevenSegmentColor);
        watch->setPrecision(watchWindowArray.getElement(i).precision);
        
        watchWindows.appendElement(watch);                
    }
    
}

//==============================================================================
// WatchSelectWindow::save
//==============================================================================
Array<WatchConfig> WatchSelectWindow::save()
{
    Array<WatchConfig> rValue;
    for( int i = 0; i < watchWindows.getNumElements(); ++i)
    {
        if(watchWindows.getElement(i)->visible())
            rValue.appendElement(watchWindows.getElement(i)->save());

    }

    return rValue;
}

//==============================================================================
// WatchSelectWindow::hideAllWatchs
//==============================================================================
void WatchSelectWindow::hideAllWatchs()
{
    for( int i = 0; i < watchWindows.getNumElements(); ++i)
        watchWindows.getElement(i)->hide();
}

