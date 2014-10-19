//==============================================================================
// PlotBaseWindow.cpp - PlotBase Window implementasyonu
//
// Author        : 
// Version       :
// Compatibility : GCC
//==============================================================================

#include "PlotBaseWindow.h"

const int PlotBaseWindow::colorArray[PlotBaseWindow::colorSize][3] = {
        {255,186,20},//sarimsi
        {219,58,15}, // turuncu
        {161,0,61}, // morumsu
        {15,36,89}, // mavimsi
        {190,20,5}, // koyu kirmizi
        {170,190,170} //acik mavi
};


PlotBaseWindow::PlotBaseWindow( Array<LogVariableGUI*>& logVars, char* name )
 : Window( 600, 300, name )
{

    this->begin();
    color(fltk::color(167,162,178));
    gbox  = new Group(5, 5, w()-10, h()-10);
    gbox->box(fltk::EMBOSSED_BOX);

    //  ----- Menu -----
    menu = new MenuBar( 5, 5, w()-10, 25);
    menu->box( fltk::EMBOSSED_BOX );
    menu->begin();
    addButton = new Button(0,0,60,23,"Add");
    addButton->callback(cbSelectWindow);
    addButton->box(fltk::PLASTIC_UP_BOX);
    addButton->color(fltk::GRAY70);
    addButton->highlight_color(fltk::GRAY60);

    addButton = new Button(0,0,100,23,"Matlab Export");
    addButton->callback(cbExportAsMatlab);
    addButton->box(fltk::PLASTIC_UP_BOX);
    addButton->color(fltk::GRAY70);
    addButton->highlight_color(fltk::GRAY60);
    menu->end();
    //  --- Menu ---

    //  ----- ThumbWheel -----
    zoomYthumb = new ThumbWheel(15,50,15,150,"Zy");
    zoomYthumb->set_vertical();
    zoomYthumb->step(0.02);
    zoomYthumb->range(-100000000,100000000);
    zoomYthumb->value(0);
    zoomYthumb->callback(cbZoomY);
    zoomYthumb->tooltip("Zoom Y Axis");

    translateYthumb = new ThumbWheel(35,50,15,150,"Ty");
    translateYthumb->set_vertical();
    translateYthumb->step(0.1);
    translateYthumb->range(-100000000,100000000);
    translateYthumb->value(0);
    translateYthumb->callback(cbTranslateY);
    translateYthumb->tooltip("Translate Y Axis");

    translateXthumb = new ThumbWheel(165,230,150,15,"Tx");
    translateXthumb->set_horizontal();
    translateXthumb->step(0.1);
    translateXthumb->range(-100000000,100000000);
    translateXthumb->value(0);
    translateXthumb->align(fltk::ALIGN_RIGHT);
    translateXthumb->callback(cbTranslateX);
    translateXthumb->tooltip("Translate X Axis");

    zoomXthumb = new ThumbWheel(165,250,150,15,"Zx");
    zoomXthumb->set_horizontal();
    zoomXthumb->step(0.02);
    zoomXthumb->range(-100000000,100000000);
    zoomXthumb->value(0);
    zoomXthumb->align(fltk::ALIGN_RIGHT);
    zoomXthumb->callback(cbZoomX);
    zoomXthumb->tooltip("Zoom X Axis");
    //  ----- ThumbWheel -----

    autoScale = new CheckButton(350,230,15,15,"Auto Scale");
    autoScale->align(fltk::ALIGN_RIGHT);
    autoScale->callback(cbAutoScale);

    autoTranslate = new CheckButton(350,250,15,15,"Auto Translate");
    autoTranslate->align(fltk::ALIGN_RIGHT);
    autoTranslate->callback(cbAutoTranslate);


    statusBar = new StatusBarGroup(20, 10, 110, 20);

    selectedGroup  = new ScrollGroup(440, 40, 150, 195);

    this->end();
    

    //  ----- Plot Select Window -----
    selectLogVarWindow = new Window(240,230,"Plot Select");
    selectLogVarWindow->begin();
    selectMBrowser = new MultiBrowser(10, 10, 220, 180);
    selectMBrowser->indented(true);
    
    selectAddButton = new ZButton(15, 200, 65, 22, "Add");
    selectAddAllButton = new ZButton(85, 200, 65, 22, "Add All");    
    
    selectCancelButton = new ZButton(155, 200, 65, 22, "Cancel");

    selectLogVarWindow->resizable(selectMBrowser);
    selectLogVarWindow->end();
    selectLogVarWindow->set_modal();
    //  ----- Plot Select Window -----

    LogVariablesGUI = &logVars;

    colorIndex = 0;
}
//==============================================================================
// PlotBaseWindow::~PlotBaseWindow
//==============================================================================
PlotBaseWindow::~PlotBaseWindow()
{
     // Plot Select Window temizlenir
    delete selectMBrowser;
    delete selectAddButton;
    delete selectAddAllButton;
    delete selectCancelButton;
    delete selectLogVarWindow;

    delete gbox;

    // Menu temizlenir
    delete addButton;
    delete menu;

    // ThumbWheel temizlenir
    delete zoomYthumb;
    delete zoomXthumb;
    delete translateXthumb;
    delete translateYthumb;

    // CheckBox Temizlenir
    delete autoScale;
    delete autoTranslate;

    // Secilen Degiskenler silinir.
    for(int i = 0; i < selectedLogVars.getNumElements(); ++i)
        delete selectedLogVars.getElement(i);
    delete selectedGroup;
}

//==============================================================================
// PlotBaseWindow::cbTranslateX
//==============================================================================
void PlotBaseWindow::cbTranslateX(Widget *o, void* userData)
{
    userData = userData;
    PlotBaseWindow *plotWindow = (PlotBaseWindow*) o->window();

    plotWindow->currentTranslateX = plotWindow->translateXthumb->value();
    double diff = plotWindow->currentTranslateX - plotWindow->preTranslateX;
    diff /= plotWindow->glWindow->getZoomX();
    plotWindow->glWindow->setTranslateX( diff + plotWindow->glWindow->getTranslateX()  );
    plotWindow->glWindow->setAutoTranslate(false);
    plotWindow->autoTranslate->value(false);
    plotWindow->glWindow->setAutoScale(false);
    plotWindow->autoScale->value(false);
    plotWindow->preTranslateX = plotWindow->currentTranslateX;


   
}

//==============================================================================
// PlotBaseWindow::cbTranslateY
//==============================================================================
void PlotBaseWindow::cbTranslateY(Widget *o, void* userData)
{
    userData = userData;
    PlotBaseWindow *plotWindow = (PlotBaseWindow*) o->window();
    
    plotWindow->currentTranslateY = plotWindow->translateYthumb->value();
    double diff = plotWindow->currentTranslateY - plotWindow->preTranslateY;
    diff /= plotWindow->glWindow->getZoomY();
    plotWindow->glWindow->setTranslateY( diff + plotWindow->glWindow->getTranslateY()  );

    plotWindow->glWindow->setAutoTranslate(false);
    plotWindow->autoTranslate->value(false);
    plotWindow->glWindow->setAutoScale(false);
    plotWindow->autoScale->value(false);
    plotWindow->preTranslateY = plotWindow->currentTranslateY;
}

//==============================================================================
// PlotBaseWindow::cbZoomX
//==============================================================================
void PlotBaseWindow::cbZoomX(Widget *o, void* userData)
{
    userData = userData;
    PlotBaseWindow *plotWindow = (PlotBaseWindow*) o->window();
    
    plotWindow->currentZoomX = plotWindow->zoomXthumb->value();
    double diff = plotWindow->currentZoomX - plotWindow->preZoomX;
    
    
    if(diff > 0)
        diff =  plotWindow->glWindow->getZoomX() * (diff+1) ;
    else if( diff < 0 )
        diff =  plotWindow->glWindow->getZoomX() / ((-diff)+1) ;
    else
        diff = plotWindow->glWindow->getZoomX();

    if( diff > 500000 )
        diff =  plotWindow->glWindow->getZoomX();

    plotWindow->glWindow->setZoomX( diff );
    plotWindow->glWindow->setAutoTranslate(false);
    plotWindow->autoTranslate->value(false);
    plotWindow->glWindow->setAutoScale(false);
    plotWindow->autoScale->value(false);
    plotWindow->preZoomX = plotWindow->currentZoomX;
}

//==============================================================================
// PlotBaseWindow::cbZoomY
//==============================================================================
void PlotBaseWindow::cbZoomY(Widget *o, void* userData)
{
    userData = userData;
    PlotBaseWindow *plotWindow = (PlotBaseWindow*) o->window();

    plotWindow->currentZoomY = plotWindow->zoomYthumb->value();
    double diff = plotWindow->currentZoomY - plotWindow->preZoomY;


    if(diff > 0)
        diff =  plotWindow->glWindow->getZoomY() * (diff+1) ;
    else if( diff < 0 )
        diff =  plotWindow->glWindow->getZoomY() / ((-diff)+1) ;
    else
        diff = plotWindow->glWindow->getZoomY();

    if( diff > 500000 )
        diff =  plotWindow->glWindow->getZoomX();

    plotWindow->glWindow->setZoomY( diff );
    plotWindow->glWindow->setAutoTranslate(false);
    plotWindow->autoTranslate->value(false);
    plotWindow->glWindow->setAutoScale(false);
    plotWindow->autoScale->value(false);
    plotWindow->preZoomY = plotWindow->currentZoomY;
}

//==============================================================================
// PlotBaseWindow::cbAutoScale
//==============================================================================
void PlotBaseWindow::cbAutoScale( Widget* o, long userData )
{
    userData = userData;
    PlotBaseWindow *plotWindow = (PlotBaseWindow*) o->window();
    CheckButton* autoScale = (CheckButton*) o;
    plotWindow->glWindow->setAutoScale(autoScale->value());
    plotWindow->glWindow->setAutoTranslate(false);
    plotWindow->autoTranslate->value(false);
}

//==============================================================================
// PlotBaseWindow::cbAutoTranslate
//==============================================================================
void PlotBaseWindow::cbAutoTranslate( Widget* o, long userData )
{
    userData = userData;
    PlotBaseWindow *plotWindow = (PlotBaseWindow*) o->window();
    CheckButton* autoTranslate = (CheckButton*) o;
    plotWindow->glWindow->setAutoTranslate(autoTranslate->value());
    plotWindow->glWindow->setAutoScale(false);
    plotWindow->autoScale->value(false);
}

//==============================================================================
// PlotBaseWindow::cbSelectWindow
//==============================================================================
void PlotBaseWindow::cbSelectWindow(Widget *o, void* userData)
{
    userData = userData;
    PlotBaseWindow* plot = (PlotBaseWindow*) o->window();
    plot->selectLogVarWindow->show();
}


//==============================================================================
// PlotBaseWindow::cbExportAsMatlab
//==============================================================================
void PlotBaseWindow::cbExportAsMatlab(Widget *o, void* ){

	PlotBaseWindow* plot = (PlotBaseWindow*) o->window();
	 
	 // current directory'den baslayan .m uzantisini default olarak arayan, tek secimli dosya kaydedici
    FileChooser *fc = new FileChooser("./", "Matlab Files(*.m)", FileChooser::SINGLE, "Save Config File" );

    // type ın 2 olmasi kaydetmek icin
    fc->type(2);
    // ana pencereyi window olarak gorerek basla
    fc->exec(plot->window(), true);

     // eger dosya kaydedilmek istendiyse, cancel edilmedi ise
     if( fc->count() == 1 )
     {
         // ayni isimli dosya var mi yok mu diye bakalim
         FILE *filePtr = fopen(fc->value(0), "r");

         // eger yoksa yapilir
         // varsa kullaniciya uzerine yazilsin mi diye sorulur evet ise yapilir
         if( filePtr == NULL || ask("File already exist, overwrite it?") != 0 )
         {
         	ofstream matlabFile;
			matlabFile.open(fc->value(0), ios::out );

                        PlotBaseWindow *plotWindow = (PlotBaseWindow*) o->window();

                        plotWindow->glWindow->printLinesToMatlabFile(matlabFile);
            
            // gerekli fonksiyon cagrilir
            
            matlabFile.close();
         }
     }

}


//==============================================================================
// PlotBaseWindow::findLogVariableGUI
//==============================================================================
LogVariableGUI* PlotBaseWindow::findLogVariableGUI(const char* name)
{
    for(int i = 0; i < LogVariablesGUI->getNumElements(); ++i)
        if( !strcmp(LogVariablesGUI->getElement(i)->getName(),name) )
            return LogVariablesGUI->getElement(i);

    return NULL;
}

//==============================================================================
// PlotBaseWindow::reallignSelected
//==============================================================================
void PlotBaseWindow::reallignSelected()
{
    int i = 0;
    while(i < selectedLogVars.getNumElements() )
    {
        if(!selectedLogVars.getElement(i)->visible())
        {
            delete selectedLogVars.getElement(i);
            selectedLogVars.removeElement(i);
        } else 
            ++i;
    }

    for(int i = 0; i < selectedLogVars.getNumElements(); ++i)
        selectedLogVars.getElement(i)->y(i*25);
}


//==============================================================================
// PlotBaseWindow::handle
//==============================================================================
int PlotBaseWindow::handle(int e)
{
    switch(e)
    {
        case 50:
            // plot selected item silindi
            reallignSelected();
            break;

        case 2:
            autoScale->value(false);
            autoTranslate->value(false);
            break;
        case 200:
            statusBar->set(StatusBarGroup::SBAR_RIGHT, "X: %.4f\tY: %.4f  ",glWindow->calculateX(),glWindow->calculateY());
            break;
    }

    return fltk::Window::handle(e);
}
