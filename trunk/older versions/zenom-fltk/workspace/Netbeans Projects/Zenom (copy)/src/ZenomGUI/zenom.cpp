//==============================================================================
// Zenom.h - Header File of Main Class of Zenom Project
//
// Author        : Adil Karaöz, Cüneyt Ay, Hüsnü Karaküçük
// Version       : 0.99 (Agustos 2009)
// Compatibility : FLTK, GCC
//==============================================================================

#include "zenom.h"

//==============================================================================
// Zenom::Zenom
//==============================================================================
Zenom::Zenom( int X, int Y, int W, int H, const char *title )
: Window( X, Y, W, H, title ){
    
    // baslangic degerleri
    initialize();

}

//==============================================================================
// Zenom::Zenom
//==============================================================================
Zenom::Zenom( int W, int H, const char *title )
: Window( W, H, title ){
    
    // baslangic degerleri
    initialize();

}

//==============================================================================
// Zenom::~Zenom
//==============================================================================
Zenom::~Zenom()
{
    
    delete startButton;
    delete stopButton;

    delete frequencyInput;
    delete durationInput;

    delete programs;
    delete windows;
    delete help;
    delete main_menu;
    
    delete logoBox;

    unload();

    // Watch Window Guncelleyen Thread ve Watch Window temizlenir
    
    

   /* delete timeinfo;
    delete logo;*/
}

//==============================================================================
// Zenom::initialize
//==============================================================================
void Zenom::initialize()
{
    // resim gostermek icin programa resim kullanilacagi soylenir
    //register_images();
    
    // ana pencereye ekleme islemi baslangici
    this->begin();
    
    Group* gbox  = new Group(5, 5, w()-10, h()-10);
    gbox->box(fltk::EMBOSSED_BOX);
        
    //  ----- Menu -----
    main_menu = new MenuBar( 5, 5, w()-80, 25);
    main_menu->box( fltk::EMBOSSED_BOX );
    main_menu->begin();
    programs = new ItemGroup("Program");
    programs->box(fltk::PLASTIC_UP_BOX);
    programs->color(fltk::GRAY90);
   
    programs->begin();
    programs->add("Load Zenom File", CTRL + 'L', cbLoadConfigFile);
    programs->add("Save", CTRL + 'S', cbSaveFile );
    programs->add("Save As", CTRL + SHIFT + 'S', cbSaveAsFile );
    new Divider();
    programs->add("Quit", 0, cbQuit);
    programs->end();
    
    windows = new ItemGroup("Windows");
    windows->box(fltk::PLASTIC_UP_BOX);
    windows->color(fltk::GRAY90);
    windows->begin();
    windows->add("Plot Window", 0, cbPlotWindow);
    windows->add("XY Plot Window", 0, cbPlotXYWindow);
    new Divider();
    windows->add("Scene Window", 0, cbSceneWindow);
    new Divider();
    windows->add("Watch Window", 0, cbWatchSelectWindow );
    new Divider();
    windows->add("Control Variable Window", 0, cbControlVarWindow );
    windows->add("Log Variable Window", 0, cbLogVarWindow );
    windows->end();
    
    help = new ItemGroup("   Help   ");
    help->box(fltk::PLASTIC_UP_BOX);
    help->color(fltk::GRAY90);
    help->begin();
    help->add("Contents", 0, cb_Help_Contents );
    help->add("About", 0, cb_Help_About );
    help->end();
    main_menu->end();
    //  ----- Menu -----;

    TextDisplayWidget::initialize(main_menu->x(), main_menu->y());

   

    //  --- Logo ---
    // program logosu icin obje yaratilir ve resim konulur
    logoBox = new Widget( main_menu->w(), 5, w() - main_menu->w() - 5, main_menu->h());
    logoBox->box(fltk::EMBOSSED_BOX);
    logoBox->image( new TiledImage(SharedImage::get("./images/bg.jpg")));
    logoBox->align(fltk::ALIGN_INSIDE);    
    //  --- Logo ---


    //  --- Start Stop Frequency Duration ---
    // buttonlar ve inputlar icin objeler tartilir ve ozellikleri ayarlanir
    Group* border = new Group( 23, main_menu->h() + 18, 52, 52 );
    border->box(fltk::BORDER_BOX);
    border->begin();
    startButton = new Button( 1, 1, 50, 50, "@>;" );
    startButton->box(fltk::PLASTIC_UP_BOX);
    startButton->labelsize(15);
    startButton->color(fltk::GRAY65);
    startButton->highlight_color(fltk::GREEN);
    startButton->callback(cbStartButton);
    border->end();

    border = new Group( 88, main_menu->h() + 18, 52, 52 );
    border->box(fltk::BORDER_BOX);
    border->begin();
    stopButton = new Button( 1, 1, 50, 50, "@square" );
    stopButton->box(fltk::PLASTIC_UP_BOX);
    stopButton->labelsize(13);
    stopButton->color(fltk::GRAY65);
    stopButton->highlight_color(fltk::RED);
    stopButton->callback(cbStopButton);
    border->end();
    
    frequencyInput = new IntInput(245, main_menu->h() + 20, 120, 25, "Frequency " );
    frequencyInput->color(fltk::GRAY95);
    frequencyInput->labelcolor( RED );
    frequencyInput->align(fltk::ALIGN_LEFT);
    frequencyInput->callback(cbFreqDurUpdate);
    frequencyInput->when(fltk::WHEN_ENTER_KEY);


    durationInput = new IntInput(245, main_menu->h() + 50, 120, 25, "Duration    " );
    durationInput->color(fltk::GRAY95);
    durationInput->align(fltk::ALIGN_LEFT);
    durationInput->labelcolor( RED );
    durationInput->callback(cbFreqDurUpdate);
    durationInput->when(fltk::WHEN_ENTER_KEY);
    //  --- Start Stop Frequency Duration ---


    //  --- ProgressBar ---
    progressBar = new ProgressBar(190, main_menu->h() + 50, 165, 15);
    progressBar->box(fltk::PLASTIC_DOWN_BOX);    
    progressBar->selection_color(fltk::color(68,100,198));
    progressBar->selection_textcolor(fltk::color(223,240,255));
    progressBar->labelsize(10);
    progressBar->labelcolor(fltk::GRAY25);
    progressBar->align(fltk::ALIGN_BOTTOMRIGHT);
    progressBar->hide();
    //  --- ProgressBar ---
    
    this->resizable( TextDisplayWidget::mTextDisplay );
    this->end();
    size_range(400,310,400,800);
    color(fltk::color(167,162,178));

    // pasif yapma islemi
    deactiveItems();

    
    state = STOP;
    load = false;


    applicationName = NULL;
    applicationPath = NULL;
    applicationConfigPath = NULL;

}


//==============================================================================
// Zenom::Quit
//==============================================================================
void Zenom::cbQuit( Widget *w, void *userData )
{
    userData = userData;
    Zenom *zenom = (Zenom*)w->window();
    zenom->hide();
}


//==============================================================================
// Zenom::PlottingWindow
//==============================================================================
void Zenom::cbPlotWindow( Widget *w, void* userData )
{
    userData = userData;
    Zenom *zenom = (Zenom*)w->window();

    // Plot Pencereleri temizlenir.
    int i = 0;
    while( i < zenom->plotWindows.getNumElements())
    {
        if(!zenom->plotWindows.getElement(i)->visible())
        {
            delete zenom->plotWindows.getElement(i);
            zenom->plotWindows.removeElement(i);            
        }
        else
            ++i;
    }

    PlotBaseWindow* newPlot;
    newPlot = new PlotWindow(zenom->logVariableGUIArray,zenom->guiComQueueSender);
    newPlot->show();
    zenom->plotWindows.appendElement(newPlot);
}

//==============================================================================
// Zenom::cbPlotXYWindow
//==============================================================================
void Zenom::cbPlotXYWindow( Widget *w, void* userData )
{
    userData = userData;
    Zenom *zenom = (Zenom*)w->window();

    // Plot Pencereleri temizlenir.
    int i = 0;
    while( i < zenom->plotWindows.getNumElements())
    {
        if(!zenom->plotWindows.getElement(i)->visible())
        {
            delete zenom->plotWindows.getElement(i);
            zenom->plotWindows.removeElement(i);
        }
        else
            ++i;
    }

    PlotBaseWindow* newPlot;
    newPlot = new PlotXYWindow(zenom->logVariableGUIArray,zenom->guiComQueueSender);
    newPlot->show();
    zenom->plotWindows.appendElement(newPlot);
}

//==============================================================================
// Zenom::cbSceneWindow
//==============================================================================
void Zenom::cbSceneWindow( Widget *w, void* userData )
{
    userData = userData;
    Zenom *zenom = (Zenom*)w->window();

    // Plot Pencereleri temizlenir.
    int i = 0;
    while( i < zenom->sceneWindows.getNumElements())
    {
        if(!zenom->sceneWindows.getElement(i)->visible())
        {
            delete zenom->sceneWindows.getElement(i);
            zenom->sceneWindows.removeElement(i);            
        }
        else
            ++i;
    }

    SceneWindow* newScene;
    newScene = new SceneWindow(zenom->logVariableGUIArray);
    newScene->show();
    zenom->sceneWindows.appendElement(newScene);

}

//==============================================================================
// Zenom::activeItems
//==============================================================================
void Zenom::activeItems()
{
    startButton->activate();
    frequencyInput->activate();
    durationInput->activate();

    programs->child(1)->activate();
    programs->child(2)->activate();

    windows->child(0)->activate();
    windows->child(1)->activate();
    windows->child(2)->activate();
    windows->child(3)->activate();
    windows->child(4)->activate();
    windows->child(5)->activate();
}

//==============================================================================
// Zenom::deactiveItems
//==============================================================================
void Zenom::deactiveItems()
{
    startButton->deactivate();
    stopButton->deactivate();
    frequencyInput->deactivate();
    durationInput->deactivate();

    programs->child(1)->deactivate();
    programs->child(2)->deactivate();

    windows->child(0)->deactivate();
    windows->child(1)->deactivate();
    windows->child(2)->deactivate();
    windows->child(3)->deactivate();
    windows->child(4)->deactivate();
    windows->child(5)->deactivate();
}

//==============================================================================
// Zenom::loadConfigFile
//==============================================================================
int Zenom::loadConfigFile()
{
    // home dizininden baslayan .znm uzantisini default olarak arayan, tek secimli dosya secici
    FileChooser *fc = new FileChooser("./", "Configuration Files(*.znm)", FileChooser::SINGLE, "Please select config file" );


    fc->exec(this->window(), true);

    if( fc->count()  == 1 )
    {        
        // secilen dosya .cfg ile secildiyse veya all files ile secilip uzantisi .cfg ise yap
        if( checkExtension(fc->value(1)) )
        {
            unload();
            preparePaths(fc->value(1));
            runControl();

            cout << applicationName << endl;
                        
            char buffer[ NAMELENGTH ];

            snprintf(buffer,NAMELENGTH,"%s%s",applicationName,"GUIToBase");
            guiComQueueSender = new guiMessenger(buffer,true);

            snprintf(buffer,NAMELENGTH,"%s%s",applicationName,"BaseToGUI");
            guiComQueueReceiver = new guiMessenger(buffer,true);
            
            snprintf(buffer,NAMELENGTH,"%s%s",applicationName,"RTNETListener");
            rtnetComQueueReceiver = new guiMessenger(buffer,true);

            if(guiComQueueReceiver->getErrnoError())
                TextDisplayWidget::printText(strerror(guiComQueueReceiver->getErrnoError()));


            cout << "Listener creeated" << endl;
            snprintf(buffer,NAMELENGTH,"%s%s",applicationName,"Listenerasd");
            watchUpdater = new WindowUpdater( this );
            if(watchUpdater->create(buffer))
                cout << "Listener error " <<  strerror(watchUpdater->getErrnoError()) << endl;
            watchUpdater->start();
            
            
                        
            controlHeap = new HeapXn;
            controlHeapAddress = (double*)controlHeap->bind(applicationName);

            if(controlHeapAddress == NULL)
                cout << "Control heap err" << endl;

            confGUI = new Config(applicationConfigPath,true);
            confGUI->setValueGUI(logVariableGUIArray);
            confGUI->setValueGUI(controlVariableArray);
            selectWatch = new WatchSelectWindow(logVariableGUIArray);
            selectWatch->set_modal();

           
            double dtemp;
            confGUI->setValue(GENERAL,"Frequency",&dtemp);
            frequency = static_cast<int>(dtemp);
            frequencyInput->value(frequency);

            confGUI->setValue(GENERAL,"Duration",&dtemp);
            duration = static_cast<int>(dtemp);
            durationInput->value(duration);
            
            assignHeapPointers();
            //printArrays();
            openConfigurationWindows();

            controlVarWindow = new ControlVarWindow(controlVariableArray);
            logVarWindow = new LogVarWindow(logVariableGUIArray, frequency, duration);
            state = STOP;
            firstRun = true;
            load = true;

            
            label(applicationName);
            
            activeItems();

            TextDisplayWidget::printText("Configuration file loaded successfully");
        
        } else
            alert("please choice configuration file");
    }
    delete fc;
    return 0;
}

//==============================================================================
// Zenom::assignHeapPointers
//==============================================================================
void Zenom::assignHeapPointers()
{
    double *tempHeapIndex = controlHeapAddress + 4;

    for (int counter = 0 ; counter < logVariableGUIArray.getNumElements() ; ++counter )
    {
        logVariableGUIArray.getElement(counter)->setTimeAddress(controlHeapAddress);
        logVariableGUIArray.getElement(counter)->setHeapTFSDaddr( tempHeapIndex );
        tempHeapIndex += 4 ;
        logVariableGUIArray.getElement(counter)->setSourceAddress(tempHeapIndex);
        tempHeapIndex += logVariableGUIArray.getElement(counter)->getSize();
    }

    for (int counter = 0 ; counter < controlVariableArray.getNumElements() ; ++counter )
    {
        controlVariableArray.getElement(counter)->setSourceHeapAddress(tempHeapIndex);
        tempHeapIndex += controlVariableArray.getElement(counter)->getSize();
    }

}

//==============================================================================
// Zenom::runControl
//==============================================================================
int Zenom::runControl()
{    
    int err;

    child = fork();
    if (child == -1)
    {
        cout << "fork" << endl;
        return -1;
    }

    cout << "Control PID: " << child << endl;

    if(!child )
    {
        err = execl(applicationPath, applicationName, applicationConfigPath, "--gui",(char*)0);
        if( err == -1 )
            cout << "execl hata" << endl;
    }
    return 0;
}


//==============================================================================
// Zenom::unload
//==============================================================================
int Zenom::unload()
{
    if(load)
    {
        // Program yuklendi fakat hic calistirilmama durumu
        if(!firstRun)
        {
            // Threadler kapatilir.
            messageHandler->stopThread();
            messageHandler->join();
            delete messageHandler;
        }


   

        
        if(state == START)
        {
            guiComQueueSender->sendStopMessage();
            guiComQueueSender->sendUnbindMessage();
        }

        
        // LogVariableGUI temizlenir.
        delete logVarWindow;
        for(int i = 0; i < logVariableGUIArray.getNumElements(); ++i)
            logVariableGUIArray.getElement(i)->unbindHeap();
        logVariableGUIArray.removeAllElements();


        selectWatch->hideAllWatchs();
        delete selectWatch;

        for(int i = 0; i < plotWindows.getNumElements(); ++i )
            delete plotWindows.getElement(i);
        plotWindows.removeAllElements();

        for(int i = 0; i < sceneWindows.getNumElements(); ++i )
            delete sceneWindows.getElement(i);
        sceneWindows.removeAllElements();
        
        controlHeap->unbind();
        delete controlHeap;
        
        delete guiComQueueReceiver;
        delete guiComQueueSender;
        delete rtnetComQueueReceiver;



        watchUpdater->stopThread();
        watchUpdater->join();
        delete watchUpdater;
        
        

        // ControlVariable temizlenir.
        delete controlVarWindow;
        //for(int i = 0; i < controlVariableArray.getNumElements(); ++i)
            //delete controlVariableArray.getElement(i);
        controlVariableArray.removeAllElements();
        
        cout << "Child: " <<child<< endl;
        kill( child, SIGKILL );
        cout << "Kill Mesaji gonderildi" << endl;



        // Watch ekranlari temizlenir.


        // plot ekranlari silinir

        
        delete[] applicationPath;
        delete[] applicationConfigPath;
        delete[] applicationName;

        delete confGUI;
    }
    return 0;
}



//==============================================================================
// Zenom::cbControlVarWindow
//==============================================================================
void Zenom::cbControlVarWindow( Widget *w, void *userData )
{
    userData = userData;
    Zenom *zenom = (Zenom*)w->window();
    zenom->controlVarWindow->show();
}

//==============================================================================
// Zenom::cbLogVarWindow
//==============================================================================
void Zenom::cbLogVarWindow( Widget *w, void *userData )
{
    userData = userData;
    Zenom *zenom = (Zenom*)w->window();
    zenom->logVarWindow->show();
}

//==============================================================================
// Zenom::cbLoadConfigFile
//==============================================================================
void Zenom::cbLoadConfigFile( Widget *w, void *userData )
{
    userData = userData;
    Zenom *zenom = (Zenom*)w->window();
    zenom->loadConfigFile();
}

//==============================================================================
// Zenom::ReloadConfigFile
//==============================================================================
void Zenom::cb_ReloadConfigFile( Widget *w, void *userData )
{
    userData = userData;
    w = w;
    //Zenom *zenom = (Zenom*)w->window();
}

//==============================================================================
// Zenom::cbWatchSelectWindow
//==============================================================================
void Zenom::cbWatchSelectWindow( Widget *w, void *userData )
{
    userData = userData;
    Zenom *zenom = (Zenom*)w->window();
    zenom->selectWatch->show();;
}

//==============================================================================
// Zenom::SaveFile
//==============================================================================
void Zenom::cbSaveFile( Widget *w, void *userData )
{
    userData = userData;
    w = w;
    Zenom *zenom = (Zenom*)w->window();
    //zenom->confGUI->setFileName("/home/casper/Desktop/testSaved.cfg");

    // Main Window bilgileri dosyaya kaydedilir
    MainWindowConfig mainWindowConfig;
    mainWindowConfig.x = zenom->x();
    mainWindowConfig.y = zenom->y();
    mainWindowConfig.h = zenom->h();
    mainWindowConfig.w = zenom->w();
    zenom->confGUI->updateMainWindow(mainWindowConfig);

    // PlotWindows dosyaya kaydedilir
    Array< PlotConfig > plotWindowsVec;
    for (int i = 0; i < zenom->plotWindows.getNumElements(); ++i)
    {
        PlotWindow *plotW = dynamic_cast<PlotWindow*>(zenom->plotWindows.getElement(i));
        if( plotW != NULL )
        {
            plotWindowsVec.appendElement( plotW->save());
        }
    }
    zenom->confGUI->updatePlotWindows(plotWindowsVec);


    // PlotXYWindows dosyaya kaydedilir
    Array< PlotXYConfig > plotXYWindowsVec;
    for (int i = 0; i < zenom->plotWindows.getNumElements(); ++i)
    {
        PlotXYWindow *plotXYW = dynamic_cast<PlotXYWindow*>(zenom->plotWindows.getElement(i));
        if( plotXYW != NULL )
        {
            plotXYWindowsVec.appendElement( plotXYW->save());
        }
    }
    zenom->confGUI->updatePlotXYWindows(plotXYWindowsVec);

    // Watch Window bilgisini dosyaya kaydedilir
    Array< WatchConfig > watchWindowsVec = zenom->selectWatch->save();
    zenom->confGUI->updateWatchWindows(watchWindowsVec);

    // Scene Window bilgisi dosyaya kaydedilir
    Array< SceneWindowConfig > sceneWindowsVec;
    for (int i = 0; i < zenom->sceneWindows.getNumElements(); ++i)
    {
        sceneWindowsVec.appendElement(zenom->sceneWindows.getElement(i)->save());
    }
    zenom->confGUI->updateSceneWindows(sceneWindowsVec);


    zenom->confGUI->saveToFile();

    cout << "testing gui config Storage" << endl;
    zenom->confGUI->storeFileGUI();
    cout << "config storage testing finished" << endl;
}


//==============================================================================
// Zenom::SaveAsFile
//==============================================================================
void Zenom::cbSaveAsFile( Widget *w, void *userData )
{
    Zenom *zenom = (Zenom*)w->window();
    userData = userData;
    w = w;

    // home dizininden baslayan .cfg uzantisini default olarak arayan, tek secimli dosya kaydedici
    FileChooser *fc = new FileChooser("/home/", "Configuration Files(*.cfg)", FileChooser::SINGLE, "Save Config File" );
    // type ın 2 olmasi kaydetmek icin
    fc->type(2);
    // ana pencereyi window olarak gorerek basla
    fc->exec(zenom->window(), true);

     // eger dosya kaydedilmek istendiyse, cancel edilmedi ise
     if( fc->count() == 1 )
     {
         // ayni isimli dosya var mi yok mu diye bakalim
         FILE *filePtr = fopen(fc->value(0), "r");

         // eger yoksa yapilir
         // varsa kullaniciya uzerine yazilsin mi diye sorulur evet ise yapilir
         if( filePtr == NULL || ask("File already exist, overwrite it?") != 0 )
         {
             /*
             // dosya ismi kaydedilir
             zenom->configFilename = string(fc->value(0));

             // eger dosya sonuna .cfg eklenmedi ise eklenir
             if( strstr( fc->value(0), ".cfg") == NULL)
                 zenom->configFilename.append(".cfg");
              */
             
             // artik normal save edilebilir
             Zenom::cbSaveFile( w, userData );
         }
     }
}

//==============================================================================
// Zenom::Help_Contents
//==============================================================================
void Zenom::cb_Help_Contents( Widget *w, void *userData )
{
    userData = userData;
    w = w;
    //Zenom *zenom = (Zenom*)w->window();
}

//==============================================================================
// Zenom::Help_About
//==============================================================================
void Zenom::cb_Help_About( Widget *w, void *userData )
{
    userData = userData;
    w = w;
    //Zenom *zenom = (Zenom*)w->window();
}


//==============================================================================
// Zenom::cbStartButton
//==============================================================================
void Zenom::cbStartButton( Widget *w, void *userData )
{
    userData = userData;
    Zenom *zenom = (Zenom*)w->window();

    
    if(zenom->state == START)
    {
        zenom->pause();
    }
    else
    { 
        zenom->start();
    }
}

//==============================================================================
// Zenom::start
//==============================================================================
void Zenom::start()
{
    if(state == START)
        return;
        
    controlHeapAddress[1] = frequencyInput->fvalue();
    controlHeapAddress[2] = durationInput->fvalue();
    

    if( state == STOP)
    {
        durationInput->hide();
        frequencyInput->deactivate();

        progressBar->maximum(durationInput->ivalue());
        progressBar->minimum(0);
        progressBar->position(0);
        progressBar->show();

        logVarWindow->deactivate();

        if(!firstRun)
        {
            messageHandler->stopThread();
            messageHandler->join();
            delete messageHandler;
            
            unbindLogVarHeap();
            guiComQueueSender->sendUnbindMessage();
            cout << "GUI unbind mesaji gonderdi" << endl;

        }
        else
            firstRun = false;


        messageHandler = new MessageHandler(this);
        messageHandler->create("GUIMessageHandler");

        // Control Base sinifina start basildi mesaji gonderilir.
        guiComQueueSender->sendStartMessage();
        cout << "GUI start mesaji gonderdi" << endl;

        guiComQueueReceiver->receiveBindMessage();
        cout << "GUI bind mesaji aldi" << endl;

        bindLogVarHeap();

        // 7Segmentler resetlenir.
        selectWatch->resetSevenSegments();

        // Segment guncelleyen thread calisir
        messageHandler->start();
    }
    else if ( state == PAUSE )
    {
        guiComQueueSender->sendStartMessage();
    }
    
    stopButton->activate();
    startButton->label("@||;");
    startButton->highlight_color(fltk::YELLOW);
    state = START;

    TextDisplayWidget::printText("Program started" );

   if( durationInput->ivalue() == 0 )
        TextDisplayWidget::printText("Warning: Program won't stop untill you stop");

}

//==============================================================================
// Zenom::pause
//==============================================================================
void Zenom::pause()
{
    guiComQueueSender->sendPauseMessage();
    startButton->label("@>;");
    startButton->highlight_color(fltk::GREEN);
    state = PAUSE;

    TextDisplayWidget::printText( "Program paused" );
}

//==============================================================================
// Zenom::cbStopButton
//==============================================================================
void Zenom::cbStopButton( Widget *w, void *userData )
{
    userData = userData;
    Zenom *zenom = (Zenom*)w->window();

    zenom->stop();    

}

//==============================================================================
// Zenom::stop
//==============================================================================
void Zenom::stop()
{
    if(state == STOP)
        return;
    
    if(state == START)
    {
        startButton->highlight_color(fltk::GREEN);
        startButton->label("@>;");
        startButton->redraw();
    }
    stopButton->deactivate();
    //watchUpdater->stopThread();
    
    logVarWindow->activate();
    progressBar->hide();
    durationInput->show();
    frequencyInput->activate();
    state = STOP;    

    TextDisplayWidget::printText( "Program stopped" );
    guiComQueueSender->sendStopMessage();
}

//==============================================================================
// Zenom::bindLogVarHeap
//==============================================================================
int Zenom::bindLogVarHeap()
{
    cout << "GUI bind" << endl;
    for( int i = 0; i < logVariableGUIArray.getNumElements(); ++i)
        logVariableGUIArray.getElement(i)->bindHeap();
    cout << "GUI bind ok" << endl;
    return 0;
}

//==============================================================================
// Zenom::unbindLogVarHeap
//==============================================================================
int Zenom::unbindLogVarHeap()
{
    cout << "GUI unbind" << endl;
     for( int i = 0; i < logVariableGUIArray.getNumElements(); ++i)
        logVariableGUIArray.getElement(i)->unbindHeap();
     cout << "GUI unbindOk" << endl;
    return 0;
}

//==============================================================================
// Zenom::checkExtension
//==============================================================================
bool Zenom::checkExtension( const char *filePath )
{
    char *ext;
    char *filename;
    
    // Dosya ismi elde edilir.
    filename = strrchr( filePath, '/' );
    if(filename != NULL)
    {
        ++filename;
        ext = strrchr( filename, '.' );

        // Uzanti kontrolu yapilir.
        if( ext != NULL )
        {
            if(!strcmp(".znm",ext))
                return true;
            else
                return false;
        }
    }
    return false;
}

//==============================================================================
// Zenom::preparePaths
//==============================================================================
bool Zenom::preparePaths( const char *filename )
{
    char *temp;
    int nLen = strlen(filename);
    applicationPath = new char[ nLen ];    
    strcpy(applicationPath, filename );
    
    applicationConfigPath = new char[ nLen ];
    strcpy(applicationConfigPath, filename );
    temp = strrchr( applicationConfigPath, '.' );
    sprintf(temp,"%s",".cfg");

    // Dosya ismi elde edilir.
    temp = strrchr( applicationPath, '/' ) + 1;
    nLen = strlen(temp) - 4;
    applicationName = new char[ nLen ];
    for(int i = 0; i < nLen; ++i )
        applicationName[i] = temp[i];
    
    return false;
}

//==============================================================================
// Zenom::preparePaths
//==============================================================================
void Zenom::printGUI(char* text, int errCode)
{
    errCode = errCode;
    text = text;
    /*
    char max[50];
    int nLen = strlen(text);
    int row = nLen / 50;

    for(int i = 0; i < row; ++i)
    {
        strncpy(max,text,50);
        MOutput->insert( max );
    }
    sprintf( msgBuf,"   MessageQueue read error: %s", strerror(guiComQueue->getErrnoError()) );
    MOutput->append( getDateAndTime() );
    MOutput->move_left();
    MOutput->insert( msgBuf );*/
}

//==============================================================================
// Zenom::printArrays
//==============================================================================
void Zenom::printArrays()
{

    cout << endl << endl <<"--- ControlVariables ---" << endl << endl;

    for (int counter = 0 ; counter < controlVariableArray.getNumElements() ; ++counter)
    {
        cout << "Name : " <<  controlVariableArray.getElement(counter)->getName() << endl;
        cout << "Description : " <<  controlVariableArray.getElement(counter)->getDescription()<< endl;
        cout << "Row : " <<  controlVariableArray.getElement(counter)->getRows() << endl;
        cout << "Col : " <<  controlVariableArray.getElement(counter)->getCols() << endl;
        cout << "Values :";

        for (int counter2 = 0 ; counter2 < controlVariableArray.getElement(counter)->getSize() ; ++counter2 )
            cout << " " << controlVariableArray.getElement(counter)->getElement(counter2);

        cout << endl << endl;
    }

    cout << endl << endl <<"--- LogVariableGUIs ---" << endl << endl;

    for (int counter = 0 ; counter < logVariableGUIArray.getNumElements() ; ++counter)
    {
        cout << "Name : " <<  logVariableGUIArray.getElement(counter)->getName() << endl;
        cout << "Description : " <<  logVariableGUIArray.getElement(counter)->getDescription()<< endl;
        cout << "Frequency : " <<  logVariableGUIArray.getElement(counter)->getFrequency() << endl;
        cout << "Duration : " <<  logVariableGUIArray.getElement(counter)->getDuration() << endl;
        cout << "StartTime : " <<  logVariableGUIArray.getElement(counter)->getStartTime() << endl;
        cout << "Row : " <<  logVariableGUIArray.getElement(counter)->getRows() << endl;
        cout << "Col : " <<  logVariableGUIArray.getElement(counter)->getCols() << endl;
        cout << endl << endl;
    }
}

//==============================================================================
// Zenom::handle
//==============================================================================
int Zenom::handle(int e)
{
    switch(e)
    {
        case HIDE:
            if(load)
            {
                for( int i = 0; i < plotWindows.getNumElements(); ++i)
                    plotWindows.getElement(i)->hide();

                for( int i = 0; i < sceneWindows.getNumElements(); ++i)
                    sceneWindows.getElement(i)->hide();

                selectWatch->hideAllWatchs();

                controlVarWindow->hide();
                logVarWindow->hide();
                cout << "Kapat Mesaji geldi" << endl;

            }                
            break;
    }

    return fltk::Window::handle(e);
}

//==============================================================================
// Zenom::cbFreqDurUpdate
//==============================================================================
void Zenom::cbFreqDurUpdate( Widget *w, void *userData )
{
    userData = userData;
    Zenom *zenom = (Zenom*)w->window();
    if(zenom->frequencyInput->ivalue() < 1 || zenom->durationInput->ivalue() < 0)
    {
        zenom->frequencyInput->value(zenom->frequency);
        zenom->durationInput->value(zenom->duration);
        return;
    }

    zenom->frequency = zenom->frequencyInput->ivalue();
    zenom->duration = zenom->durationInput->ivalue();
    zenom->logVarWindow->update(zenom->frequency, zenom->duration);
}



//==============================================================================
// Zenom::openConfigurationWindows
//==============================================================================
void Zenom::openConfigurationWindows()
{    
    cout << "Loading GUI information From Conf File" << endl;
    confGUI->loadFileGUI();
    cout << "GUI information loaded" << endl;

    MainWindowConfig mainWindowConfig = confGUI->getMainWindow();
    x(mainWindowConfig.x);
    y(mainWindowConfig.y);
    w(mainWindowConfig.w);
    h(mainWindowConfig.h);

    openWatchWindows();
    openPlotWindows();
    openPlotXYWindows();
    openSceneWindows();

    cout << "openConfigurationWindows function finished" << endl;
        
}

//==============================================================================
// Zenom::openPlotWindows
//==============================================================================
void Zenom::openPlotWindows()
{
    Array< PlotConfig > *plotWindowsVec = confGUI->getPlotWindows();

    cout << "Plot Windows Are Creating" << endl;
    cout << "Number of Plot Windows : "<< plotWindowsVec->getNumElements() << endl;

    PlotWindow* newPlot;
    for (int i = 0; i < plotWindowsVec->getNumElements(); ++i)
    {
        newPlot = new PlotWindow(logVariableGUIArray, guiComQueueSender);

        //cout << "Yeni pencere olusturuluyor" << endl;

        //cout << "Yeni eklenen elemanin adi : " << plotWindowsVec->getElement(i).line.getElement(0).logVariable->getName() << endl;

        //cout << "Yeni Penceredeki eleman sayisi "<< plotWindowsVec->getElement(i).line.getNumElements() << endl;
        /*for (int j = 0; j < plotWindowsVec->getElement(i).line.getNumElements(); ++j)
             cout << "Elemanlarin adi : "<< j << "- "
                  << plotWindowsVec->getElement(i).line.getElement(j).logVariable->getName()
                  <<" - Index : " << plotWindowsVec->getElement(i).line.getElement(j).index
                  <<" - Color : " << plotWindowsVec->getElement(i).line.getElement(j).color
                  << endl;
         */

        //cout << "Yeni Pencere load ediliyor" << endl;
        newPlot->load( &(plotWindowsVec->getElement(i)) );
        //cout << "Yeni Pencere show ediliyor" << endl;
        newPlot->show();
        //cout << "Yeni Pencere append ediliyor" << endl;
        plotWindows.appendElement(newPlot);
    }
}

//==============================================================================
// Zenom::openPlotXYWindows
//==============================================================================
void Zenom::openPlotXYWindows()
{
    Array< PlotXYConfig > *plotXYWindowsVec = confGUI->getPlotXYWindows();
    cout << "PlotXY Windows Are Creating" << endl;
    cout << "Number of PlotXY Windows : "<< plotXYWindowsVec->getNumElements() << endl;

    PlotXYWindow* newPlotXY;
    for (int i = 0; i < plotXYWindowsVec->getNumElements(); ++i)
    {
        newPlotXY = new PlotXYWindow(logVariableGUIArray, guiComQueueSender);

        //cout << "Yeni pencere olusturuluyor" << endl;

        //cout << "Yeni eklenen elemanin adi : " << plotXYWindowsVec->getElement(i).line.getElement(0).logVariable->getName() << endl;

        /*cout << "Yeni Penceredeki eleman sayisi "<< plotXYWindowsVec->getElement(i).line.getNumElements() << endl;
        for (int j = 0; j < plotXYWindowsVec->getElement(i).line.getNumElements(); ++j)
             cout << "Elemanlarin adi : "<< j << "- "
                  << plotXYWindowsVec->getElement(i).line.getElement(j).logVariable->getName()
                  <<" - Index : " << plotXYWindowsVec->getElement(i).line.getElement(j).index
                  <<" - Color : " << plotXYWindowsVec->getElement(i).line.getElement(j).color
                  << endl;
         */

        //cout << "Yeni Pencere load ediliyor" << endl;
        newPlotXY->load( &(plotXYWindowsVec->getElement(i)) );
        //cout << "Yeni Pencere show ediliyor" << endl;
        newPlotXY->show();
        //cout << "Yeni Pencere append ediliyor" << endl;
        plotWindows.appendElement(newPlotXY);
    }
}

//==============================================================================
// Zenom::openWatchWindows
//==============================================================================
void Zenom::openWatchWindows()
{
    cout << "Opening Watch Windows" << endl;
    Array< WatchConfig > *watchWindowsVec = confGUI->getWatchWindows();

    selectWatch->load(*watchWindowsVec);
    cout << "Watch windows opened" << endl;
}

//==============================================================================
// Zenom::openSceneWindows
//==============================================================================
void Zenom::openSceneWindows()
{
    Array< SceneWindowConfig > *sceneWindowsVec = confGUI->getSceneWindows();

    cout << "Scene Windows Are Creating" << endl;
    cout << "Number of Scene Windows : "<< sceneWindowsVec->getNumElements() << endl;

    SceneWindow* newScene;
    for (int i = 0; i < sceneWindowsVec->getNumElements(); ++i)
    {
        newScene = new SceneWindow(logVariableGUIArray);

        newScene->load( &(sceneWindowsVec->getElement(i)) );
        newScene->show();
        
        sceneWindows.appendElement(newScene);
    }

}
    