//==============================================================================
// Zenom.h - Header File of Main Class of Zenom Project
//
// Author        : Adil Karaöz, Cüneyt Ay, Hüsnü Karaküçük
// Version       : 0.99 (Agustos 2009)
// Compatibility : FLTK, GCC
//==============================================================================

#include "zenomwindow.h"
//==============================================================================
// Zenom::Zenom
//==============================================================================
ZenomWindow::ZenomWindow( int W, int H, const char *title )
: Window( W, H, title ){
    
    // baslangic degerleri
    initialize();

}

//==============================================================================
// Zenom::~Zenom
//==============================================================================
ZenomWindow::~ZenomWindow()
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
void ZenomWindow::initialize()
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
    //programs->add("Save As", CTRL + SHIFT + 'S', cbSaveAsFile );
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

}


//==============================================================================
// Zenom::Quit
//==============================================================================
void ZenomWindow::cbQuit( Widget *w, void *userData )
{
    userData = userData;
    ZenomWindow *zenom = (ZenomWindow*)w->window();
    zenom->hide();
}


//==============================================================================
// Zenom::PlottingWindow
//==============================================================================
void ZenomWindow::cbPlotWindow( Widget *w, void* userData )
{
    userData = userData;
    ZenomWindow *zenom = (ZenomWindow*)w->window();
    zenom->plotWindowManager.newPlotWindow();
}

//==============================================================================
// Zenom::cbPlotXYWindow
//==============================================================================
void ZenomWindow::cbPlotXYWindow( Widget *w, void* userData )
{
    userData = userData;
    ZenomWindow *zenom = (ZenomWindow*)w->window();
    zenom->plotXYWindowManager.newPlotXYWindow();
}

//==============================================================================
// Zenom::cbSceneWindow
//==============================================================================
void ZenomWindow::cbSceneWindow( Widget *w, void* userData )
{
    userData = userData;
    ZenomWindow *zenom = (ZenomWindow*)w->window();
    zenom->sceneWindowManager.newSceneWindow();
}

//==============================================================================
// Zenom::activeItems
//==============================================================================
void ZenomWindow::activeItems()
{
    startButton->activate();
    frequencyInput->activate();
    durationInput->activate();

    programs->child(1)->activate();

    for(int i = 0; i < windows->children(); ++i)
    	windows->child(i)->activate();

}

//==============================================================================
// Zenom::deactiveItems
//==============================================================================
void ZenomWindow::deactiveItems()
{
    startButton->deactivate();
    stopButton->deactivate();
    frequencyInput->deactivate();
    durationInput->deactivate();

    programs->child(1)->deactivate();

    for(int i = 0; i < windows->children(); ++i)
    	windows->child(i)->deactivate();

    for(int i = 0; i < help->children(); ++i)
        help->child(i)->deactivate();
}

//==============================================================================
// Zenom::loadConfigFile
//==============================================================================
int ZenomWindow::loadConfigFile()
{
    // home dizininden baslayan .znm uzantisini default olarak arayan, tek secimli dosya secici
    FileChooser *fc = new FileChooser("./", "Configuration Files(*.znm)", FileChooser::SINGLE, "Please select config file" );

    fc->exec(this->window(), true);

    if( fc->count()  == 1 )
    {        
    	ZPath file(fc->value(1));
        // secilen dosya .cfg ile secildiyse veya all files ile secilip uzantisi .cfg ise yap
        if( file.extension() == "znm" )
        {
        	//TODO
        	// Ana heap veya konfigurasyon acilmaz ise, projeyi devam ettirme
            unload();
        	mProjectPath.setPath(fc->value(1));
        	mProjectConfigPath.setPath(mProjectPath.changeExtension("xml"));
            runControl();

            char buffer[ NAMELENGTH ];

            snprintf(buffer,NAMELENGTH,"%s%s",mProjectPath.fileNameWithoutExtension().c_str(),"GUIToBase");
            guiComQueueSender = new guiMessenger(buffer,true);

            snprintf(buffer,NAMELENGTH,"%s%s",mProjectPath.fileNameWithoutExtension().c_str(),"BaseToGUI");
            guiComQueueReceiver = new guiMessenger(buffer,true);
            
            snprintf(buffer,NAMELENGTH,"%s%s",mProjectPath.fileNameWithoutExtension().c_str(),"RTNETListener");
            rtnetComQueueReceiver = new guiMessenger(buffer,true);

            if(guiComQueueReceiver->getErrnoError())
                TextDisplayWidget::printText(strerror(guiComQueueReceiver->getErrnoError()));


            cout << "Listener creeated" << endl;
            snprintf(buffer,NAMELENGTH,"%s%s",mProjectPath.fileNameWithoutExtension().c_str(),"Listenerasd");
            watchUpdater = new WindowUpdater( this );
            if(watchUpdater->create(buffer))
                cout << "Listener error " <<  strerror(watchUpdater->getErrnoError()) << endl;
            watchUpdater->start();
                        

            controlHeap = new HeapXn;
            controlHeapAddress = (double*)controlHeap->bind(mProjectPath.fileNameWithoutExtension().c_str());

            if(controlHeapAddress == NULL)
                cout << "Control heap err" << endl;

            confGUI = new Config(mProjectConfigPath.fullPath().c_str());
            confGUI->setValueGUI(logVariableGUIArray);
            confGUI->setValueGUI(controlVariableArray);
            selectWatch = new WatchSelectWindow(logVariableGUIArray);
            selectWatch->set_modal();


            sceneWindowManager.setLogVariableArray(logVariableGUIArray);

            plotWindowManager.setLogVariableArray(logVariableGUIArray);
            plotWindowManager.setMessenger(guiComQueueSender);

            plotXYWindowManager.setLogVariableArray(logVariableGUIArray);
            plotXYWindowManager.setMessenger(guiComQueueSender);
           
            frequency = confGUI->getFrequency();
            frequencyInput->value(frequency);

            duration = confGUI->getDuration();
            durationInput->value(duration);
            
            assignHeapPointers();

            //printArrays();
            Utils::setLogVariableGUIVec(&logVariableGUIArray);
            openConfigurationWindows();

            controlVarWindow = new ControlVarWindow(controlVariableArray);
            logVarWindow = new LogVarWindow(logVariableGUIArray, frequency, duration);
            state = STOP;
            firstRun = true;
            load = true;

            
            label(mProjectPath.fileNameWithoutExtension().c_str());
            
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
void ZenomWindow::assignHeapPointers()
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
int ZenomWindow::runControl()
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
        err = execl(mProjectPath.fullPath().c_str(),
        		mProjectPath.fileNameWithoutExtension().c_str(),
        		"--gui",
        		mProjectConfigPath.fullPath().c_str(),
        		(char*)0);
        if( err == -1 )
            cout << "execl hata" << endl;
    }
    return 0;
}

//==============================================================================
// Zenom::cbUpdate
//==============================================================================
void ZenomWindow::cbUpdate(void *pZenomWindow)
{
	ZenomWindow* zenomWindow = (ZenomWindow*)(pZenomWindow);
	if(zenomWindow->state != START)
		return;

	char timeInfo[255];

	if( !zenomWindow->guiComQueueReceiver->receiveStopMessage())
    {
        cout << "Stop Mesahi geldi" << endl;
        zenomWindow->stop();
    }

	zenomWindow->selectWatch->updateSevenSegments();

	zenomWindow->progressBar->position(*(zenomWindow->controlHeapAddress));

    // Program sonsuz zamanda calisirken gecen sure gosterilir.
    if( zenomWindow->durationInput->ivalue() )
        snprintf(timeInfo,254,"Remaining Time: %.2f",
        		zenomWindow->durationInput->ivalue() - *(zenomWindow->controlHeapAddress));
    else
        snprintf(timeInfo,254,"Elapsed Time: %.2f", *(zenomWindow->controlHeapAddress));
    zenomWindow->progressBar->copy_label(timeInfo);


    zenomWindow->sceneWindowManager.update();

	fltk::repeat_timeout(1.0/20, ZenomWindow::cbUpdate, zenomWindow);
}

//==============================================================================
// Zenom::unload
//==============================================================================
int ZenomWindow::unload()
{
    if(load)
    {
        // Program yuklendi fakat hic calistirilmama durumu
    	/*
        if(!firstRun)
        {
            // Threadler kapatilir.
            messageHandler->stopThread();
            messageHandler->join();
            delete messageHandler;
        }
        */
        
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

        plotWindowManager.closeAllWindows();
        plotXYWindowManager.closeAllWindows();
        sceneWindowManager.closeAllWindows();
        
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

        delete confGUI;
    }
    return 0;
}



//==============================================================================
// Zenom::cbControlVarWindow
//==============================================================================
void ZenomWindow::cbControlVarWindow( Widget *w, void *userData )
{
    userData = userData;
    ZenomWindow *zenom = (ZenomWindow*)w->window();
    zenom->controlVarWindow->show();
}

//==============================================================================
// Zenom::cbLogVarWindow
//==============================================================================
void ZenomWindow::cbLogVarWindow( Widget *w, void *userData )
{
    userData = userData;
    ZenomWindow *zenom = (ZenomWindow*)w->window();
    zenom->logVarWindow->show();
}

//==============================================================================
// Zenom::cbLoadConfigFile
//==============================================================================
void ZenomWindow::cbLoadConfigFile( Widget *w, void *userData )
{
    userData = userData;
    ZenomWindow *zenom = (ZenomWindow*)w->window();
    zenom->loadConfigFile();
}

//==============================================================================
// Zenom::ReloadConfigFile
//==============================================================================
void ZenomWindow::cb_ReloadConfigFile( Widget *w, void *userData )
{
    userData = userData;
    w = w;
    //TODO
}

//==============================================================================
// Zenom::cbWatchSelectWindow
//==============================================================================
void ZenomWindow::cbWatchSelectWindow( Widget *w, void *userData )
{
    userData = userData;
    ZenomWindow *zenom = (ZenomWindow*)w->window();
    zenom->selectWatch->show();
}

//==============================================================================
// Zenom::SaveFile
//==============================================================================
void ZenomWindow::cbSaveFile( Widget *w, void *userData )
{
    userData = userData;
    w = w;
    ZenomWindow *zenom = (ZenomWindow*)w->window();
    //zenom->confGUI->setFileName("/home/casper/Desktop/testSaved.cfg");
    zenom->confGUI->resetXMLFile();

    zenom->confGUI->updateVariable(zenom->frequency, zenom->duration);
    zenom->confGUI->updateVariable(zenom->logVariableGUIArray);
    zenom->confGUI->updateVariable(zenom->controlVariableArray);


    // Main Window bilgileri dosyaya kaydedilir
    pugi::xml_node mainWindowNode = zenom->confGUI->appendChild("MAIN_WINDOW");
    mainWindowNode.append_attribute("X") = zenom->x();
    mainWindowNode.append_attribute("Y") = zenom->y();
    mainWindowNode.append_attribute("H") = zenom->h();
    mainWindowNode.append_attribute("W") = zenom->w();

    // Watch Window bilgisini dosyaya kaydedilir
    pugi::xml_node watchWindowsNode = zenom->confGUI->appendChild("WATCH_WINDOWS");
    zenom->selectWatch->save(watchWindowsNode);   

    zenom->plotWindowManager.save(zenom->confGUI->appendChild("PLOT_WINDOWS"));
    zenom->plotXYWindowManager.save(zenom->confGUI->appendChild("PLOT_XY_WINDOWS"));
    zenom->sceneWindowManager.save(zenom->confGUI->appendChild("SCENE_WINDOWS"));

    zenom->confGUI->saveToFile();

}


//==============================================================================
// Zenom::SaveAsFile
//==============================================================================
void ZenomWindow::cbSaveAsFile( Widget *w, void *userData )
{
    ZenomWindow *zenom = (ZenomWindow*)w->window();
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
             ZenomWindow::cbSaveFile( w, userData );
         }
     }
}

//==============================================================================
// Zenom::Help_Contents
//==============================================================================
void ZenomWindow::cb_Help_Contents( Widget *w, void *userData )
{
    userData = userData;
    w = w;
    //Zenom *zenom = (Zenom*)w->window();
}

//==============================================================================
// Zenom::Help_About
//==============================================================================
void ZenomWindow::cb_Help_About( Widget *w, void *userData )
{
    userData = userData;
    w = w;
    //Zenom *zenom = (Zenom*)w->window();
}


//==============================================================================
// Zenom::cbStartButton
//==============================================================================
void ZenomWindow::cbStartButton( Widget *w, void *userData )
{
    userData = userData;
    ZenomWindow *zenom = (ZenomWindow*)w->window();

    
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
void ZenomWindow::start()
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
        	/*
            messageHandler->stopThread();
            messageHandler->join();
            delete messageHandler;
            */
            
            unbindLogVarHeap();
            guiComQueueSender->sendUnbindMessage();
            cout << "GUI unbind mesaji gonderdi" << endl;

        }
        else
            firstRun = false;


        /*
        messageHandler = new MessageHandler(this);
        messageHandler->create("GUIMessageHandler");
        */

        // Control Base sinifina start basildi mesaji gonderilir.
        guiComQueueSender->sendStartMessage();
        cout << "GUI start mesaji gonderdi" << endl;

        guiComQueueReceiver->receiveBindMessage();
        cout << "GUI bind mesaji aldi" << endl;

        bindLogVarHeap();

        // 7Segmentler resetlenir.
        selectWatch->resetSevenSegments();

        // Segment guncelleyen thread calisir
        //messageHandler->start();

        fltk::add_timeout(1.0/20, ZenomWindow::cbUpdate, this);

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
void ZenomWindow::pause()
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
void ZenomWindow::cbStopButton( Widget *w, void *userData )
{
    userData = userData;
    ZenomWindow *zenom = (ZenomWindow*)w->window();

    zenom->stop();    

}

//==============================================================================
// Zenom::stop
//==============================================================================
void ZenomWindow::stop()
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
int ZenomWindow::bindLogVarHeap()
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
int ZenomWindow::unbindLogVarHeap()
{
    cout << "GUI unbind" << endl;
     for( int i = 0; i < logVariableGUIArray.getNumElements(); ++i)
        logVariableGUIArray.getElement(i)->unbindHeap();
     cout << "GUI unbindOk" << endl;
    return 0;
}

//==============================================================================
// Zenom::preparePaths
//==============================================================================
void ZenomWindow::printGUI(char* text, int errCode)
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
void ZenomWindow::printArrays()
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
int ZenomWindow::handle(int e)
{
    switch(e)
    {
        case HIDE:
            if(load)
            {
            	plotWindowManager.closeAllWindows();
            	plotXYWindowManager.closeAllWindows();
                sceneWindowManager.closeAllWindows();

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
void ZenomWindow::cbFreqDurUpdate( Widget *w, void *userData )
{
    userData = userData;
    ZenomWindow *zenom = (ZenomWindow*)w->window();
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
void ZenomWindow::openConfigurationWindows()
{
    /*
    cout << "Loading GUI information From Conf File" << endl;
    confGUI->loadFileGUI();
    cout << "GUI information loaded" << endl;
     */

    pugi::xml_node mainWindowNode = confGUI->getChild("MAIN_WINDOW");
    this->resize( mainWindowNode.attribute("X").as_int(),
            mainWindowNode.attribute("Y").as_int(),
            mainWindowNode.attribute("W").as_int(),
            mainWindowNode.attribute("H").as_int());
    layout();

    selectWatch->load(confGUI->getChild("WATCH_WINDOWS"));

    plotWindowManager.load(confGUI->getChild("PLOT_WINDOWS"));
    plotXYWindowManager.load(confGUI->getChild("PLOT_XY_WINDOWS"));
    sceneWindowManager.load(confGUI->getChild("SCENE_WINDOWS"));

    cout << "openConfigurationWindows function finished" << endl;
}
    
