//==============================================================================
// Config.cpp    - Config file read and write operations
//
// Author        : 
// Version       : 1.0.00 (Agustos 2009)
// Compatibility : XENOMAI, GCC
//==============================================================================


#include "Config.h"

//==============================================================================
// Config::Config
//==============================================================================
Config::Config(const char* name,bool GUI )
{
    arrayGUI = new Array < Array< xenomPair< char* , char* > > * > ;
    arrayVec[ GENERAL ] = &(this->generalArray);
    arrayVec[ LOG ] = &(this->logArray);
    arrayVec[ CONTROL ] = &(this->controlArray);
    fileName = NULL;
   
    isGUI = GUI ;
    

    setFileName( name );  

    bool check = true;

    check = loadFile();

    if( !check )
        cout << "Dosya okuma hatasi" << endl;
    
}

// Config::~Config
//==============================================================================
Config::~Config( )
{
    //resetArrays();
    guiConfigFileStorage.deleteAllElements();

    delete arrayGUI;
}

//==============================================================================
// Config::loadFile
//==============================================================================
bool Config::loadFile()
{
    xenomPair< char* , char* > newValue; 
        
    char textLine[LINELENGTH];
    
    int vecIndex = -1;
    
    ifstream inputFile;

    inputFile.open(fileName, ios::in );

    if ( ! inputFile.is_open() )
    {
        cout << "Dosya Acilamadi" << endl;
        return false;
    }
    else
    {
        inputFile.getline( textLine ,LINELENGTH );
        if ( strcmp( CONFIGFILEBEGIN , textLine ) != 0 )
            return false;
                        
        while(! inputFile.eof() )
        {
            inputFile.getline( textLine ,LINELENGTH );
                    
            if( (textLine[0] == ' ') || (textLine[0] == '\000') || (textLine[0] == '\t') )
                continue;
            
            if( strcmp( CONFIGFILEGENERAL ,textLine) == 0 )
            {
                vecIndex = GENERAL;
                continue;
            
            }
            else if (strcmp( CONFIGFILELOG ,textLine) == 0)
            {
                vecIndex = LOG;
                continue;
            }
            else if (strcmp( CONFIGFILECONTROL ,textLine) == 0)
            {
                vecIndex = CONTROL;
                continue;
            }
            else if ( strcmp( CONFIGFILEGUIBEGIN ,textLine) == 0 )
                break;
            
            
            newValue.first = new char[NAMELENGTH];
            newValue.second = new char[LINELENGTH];

            int counter;
            for ( counter = 0 ;counter < NAMELENGTH ; ++counter)
            {
                if ( textLine[counter] == ' ' )
                {
                    newValue.first[counter] = '\0';
                    break;
                }
                else
                    newValue.first[counter] = textLine[counter] ;

            }
            counter++;

            strcpy ( newValue.second , &(textLine[counter]) );
          
            if(vecIndex != -1 )
                arrayVec[vecIndex]->appendElement(newValue);
        }
    } 
    
    inputFile.close();
    return true;
}



//==============================================================================
// Config::loadFileGUI
//==============================================================================
bool Config::loadFileGUI()
{
    char textLine[LINELENGTH];

    ifstream inputFile;

    inputFile.open(fileName, std::ios::in );

    Array <char*> textVec;
    char *line;

    if ( ! inputFile.is_open() )
        return false;
    else
    {
        do
            inputFile.getline( textLine ,LINELENGTH );
        while ( strcmp( CONFIGFILEGUIBEGIN , textLine ) != 0 );

        int GUIWindowIndex = NONE;

        while(! inputFile.eof() )
        {
            inputFile.getline( textLine ,LINELENGTH );
            //cout << textLine << endl;

            if( (textLine[0] == ' ') || (textLine[0] == '\000') || (textLine[0] == '\t') )
                continue;

            if(strcmp( CONFIGFILEMAINWINDOWBEGIN ,textLine) == 0)
            {
                GUIWindowIndex = MAINWINDOW;
                continue;
            }
            else if(strcmp( CONFIGFILEPLOTBEGIN ,textLine) == 0)
            {
                GUIWindowIndex = PLOTWINDOW;
                continue;
            }
            else if(strcmp( CONFIGFILEPLOTEND ,textLine) == 0)
            {
                GUIWindowIndex = PLOTWINDOWEND;
            }
            else if (strcmp( CONFIGFILEPLOTXYBEGIN ,textLine) == 0)
            {
                GUIWindowIndex = PLOTXYWINDOW;
                continue;
            }
            else if (strcmp( CONFIGFILEPLOTXYEND ,textLine) == 0)
            {
                GUIWindowIndex = PLOTXYWINDOWEND;
            }
            else if (strcmp( CONFIGFILEWATCHBEGIN ,textLine) == 0)
            {
                GUIWindowIndex = WATCHWINDOW;
                continue;
            }
            else if( strcmp( CONFIGFILESCENEBEGIN ,textLine) == 0)
            {
                GUIWindowIndex = SCENEWINDOW;
                continue;
            }
            else if (strcmp( CONFIGFILESCENEEND ,textLine) == 0)
            {
                GUIWindowIndex = SCENEWINDOWEND;
            }

            switch(GUIWindowIndex)
            {
                case MAINWINDOW:
                    readMainWindowLine(textLine);
                    break;
                case PLOTWINDOW:
                    line = new char[LINELENGTH];
                    strcpy(line, textLine);
                    textVec.appendElement(line);
                    break;
                case PLOTWINDOWEND:
                    readPlotLine(textVec);
                    textVec.removeAllElements();
                    break;
                case PLOTXYWINDOW:
                    line = new char[LINELENGTH];
                    strcpy(line, textLine);
                    textVec.appendElement(line);
                    break;
                case PLOTXYWINDOWEND:
                    readPlotXYLine(textVec);
                    textVec.removeAllElements();
                    break;
                case WATCHWINDOW:
                    readWatchLine(textLine);
                    break;
                case SCENEWINDOW:
                    line = new char[LINELENGTH];
                    strcpy(line, textLine);
                    textVec.appendElement(line);
                    break;
                case SCENEWINDOWEND:
                    readSceneLine(textVec);
                    textVec.removeAllElements();
                    break;
                default:
                    break;
            }

        }
         
    }

    inputFile.close();

    for(int i = 0; i< sceneWindowsVec.getNumElements(); ++i)
    {
        cout << "Config VrmlFiles" << endl;
        for(int j = 0 ; j < sceneWindowsVec.getElement(i).vrmlFiles.getNumElements() ; ++j)
            cout << sceneWindowsVec.getElement(i).vrmlFiles.getElement(j) << endl;
        cout << "/VrmlFiles" << endl;

        cout << "paths" << endl;
        for(int j = 0 ; j < sceneWindowsVec.getElement(i).bindedVariable.getNumElements() ; ++j)
        {
            cout << sceneWindowsVec.getElement(i).bindedVariable.getElement(j).path << " ";
            cout << sceneWindowsVec.getElement(i).bindedVariable.getElement(j).logVariable->getName() << " ";
            cout << sceneWindowsVec.getElement(i).bindedVariable.getElement(j).index << endl;
        }
        cout << "Config /paths" << endl;
    }
    return true;
}



//==============================================================================
// Config::charToValue
//==============================================================================
bool Config::charToValue(char *values,double* dest)
{
    char temp[80];
    int indexText = 0;
    int indexDest = 0;
    
    for (int counter = 0 ; counter < LINELENGTH ; counter++ )
    {
        if ( values[counter] == ' ' ||  values[counter] == '\000' )
        {
            temp[indexText] = '\000';
            dest[indexDest] =  atof( temp );

            if (values[counter] == '\000')
                    break;

            
            indexDest++;
            indexText = 0;
        }
        else
        {
            temp[indexText] = values[counter];
            indexText++;
        }
    }
    
    return true;
}



//==============================================================================
// Config::saveToFile
//==============================================================================
bool Config::saveToFile()
{
    ofstream outputFile;
    
    outputFile.open(fileName, std::ios::out );
        
    if ( ! outputFile.is_open() )
        return false;
    else
    {
        outputFile << CONFIGFILEBEGIN << endl << endl;
        outputFile << CONFIGFILEGENERAL << endl ;
           
        
        for (int counter = 0 ; counter < generalArray.getNumElements() ; ++counter)
        {
            outputFile << generalArray.getElement(counter).first  <<" " 
            << generalArray.getElement(counter).second << endl;                  
        }
        
        outputFile << endl <<  CONFIGFILELOG << endl ;
        
        for (int counter = 0 ; counter < logArray.getNumElements() ; ++counter)
        {
            outputFile << logArray.getElement(counter).first << " "
            << logArray.getElement(counter).second << endl;
        }
                
        outputFile << endl << CONFIGFILECONTROL << endl ;
        
               
        for (int counter = 0 ; counter < controlArray.getNumElements() ; ++counter)
        {
            outputFile << controlArray.getElement(counter).first << " "
                    << controlArray.getElement(counter).second << endl ;
        }

        
        outputFile << endl << CONFIGFILEGUIBEGIN << endl;


        if ( isGUI )
            saveToFileGUI(outputFile);
        else
            printFileGUI(outputFile);        
    }
    
    outputFile.close();

    return true;    
}


//==============================================================================
// Config::setFileName
//==============================================================================
bool Config::setFileName(const char* name)
{
    if(fileName != NULL )
        delete fileName;
    
    this->fileName = new char[strlen(name) + 5];
    
    sprintf(fileName,"%s",name);//,CONFIGFILEEXTENSION);

    return true;
}


//==============================================================================
// Config::findVariable
//==============================================================================
char* Config::findVariable(const variableTypes section,const char *name)
{
       
    for (int counter = 0 ; counter < this->arrayVec[section]->getNumElements() ; ++counter )
    {
        if (strcmp( (arrayVec[section]->getElement(counter)).first , name ) == 0 )
            return (arrayVec[section]->getElement(counter)).second;
    }
    
    return NULL;
}

//==============================================================================
// Config::updateVariable
//==============================================================================
void Config::updateVariable(const double frequency,const double duration)
{
    sprintf( findVariable( GENERAL ,"Frequency"),"%.0f" , frequency );
    sprintf( findVariable( GENERAL ,"Duration"),"%.0f" ,  duration );
}
//==============================================================================
// Config::setValue
//==============================================================================
void Config::setValue(const variableTypes section, const char* name, double* dest)
{
    charToValue( findVariable( section , name ) , dest );
}


//==============================================================================
// Config::setValue
//==============================================================================
void Config::setValue(LogVariable* dest)
{
    char *find = findVariable( LOG , dest->getName() );
    double tempArray[ 6 ];

    if( find == NULL )
	return;

    charToValue( find , tempArray );

    // Dizinin elemanlari sira ile soyledir
    // 0 - Log tipi ( TIMED , EVENTTRIGGERED , NOLOGGING )
    // 1 - Frequency
    // 2 - Baslangic zamani
    // 3 - Duration
    dest->setFrequency( tempArray[1] );
    dest->setStartTime( tempArray[2] );
    dest->setDuration( tempArray[3] );
}

//==============================================================================
// Config::setValue
//==============================================================================
void Config::setValue(LogVariable& dest)
{
    this->setValue(&dest);
}

//==============================================================================
// Config::setValue
//==============================================================================
void Config::setValue(ControlVariable* dest)
{
    char *find = findVariable( CONTROL , dest->getName() );
    double tempArray[ MAXARRAYSIZE ];

    if( find == NULL )
	return;

    charToValue( find ,tempArray );

    for (int counter = 0 ; counter < dest->getSize() ; ++counter)
        (dest->getElementPtr())[ counter ] = tempArray[ counter + 2 ];
}

//==============================================================================
// Config::setValue
//==============================================================================
void Config::setValue(ControlVariable& dest)
{
    this->setValue( &dest );
}

//==============================================================================
// Config::updateVariable
//==============================================================================
void Config::updateVariable(ControlVariable &source)
{
    char *valuePtr = this->findVariable( CONTROL , source.getName() );
    char tempChar[ NAMELENGTH ];

    string tempText = "";

    sprintf(tempChar ,"%d %d", source.getRows() , source.getCols() );
    
    cout << source.getRows() << " " << source.getCols() << endl;
    
    tempText += tempChar;

    
    for (int counter = 0 ; counter < source.getSize() ; ++counter )
    {
        sprintf(tempChar ," %.2f",source.getElement(counter));        
        tempText += tempChar;
    }
    
    if(valuePtr != NULL )
        strcpy (valuePtr , tempText.c_str() );
    else
    {
        char *tempName = new char[NAMELENGTH];
        char *tempValues = new char[LINELENGTH];

        strcpy (tempName,source.getName());
        strcpy (tempValues , tempText.c_str() );

        xenomPair< char* , char* > *tempPair = new xenomPair< char* , char* >;

        tempPair->first = tempName;
        tempPair->second = tempValues;

        controlArray.appendElement(*tempPair);

    }
    
}



//==============================================================================
// Config::updateVariable
//==============================================================================
void Config::updateVariable(LogVariable &source)
{
    char *valuePtr = this->findVariable( LOG , source.getName() );

    if(valuePtr != NULL)
    {
        sprintf(valuePtr , "%.0f %.0f %.0f %.0f %.0f %.0f",(double)TIMED,
                source.getFrequency(),source.getStartTime(),source.getDuration(),
                (double)source.getRows(),(double)source.getCols());
    }
    else
    {
        char *tempName = new char[NAMELENGTH];
        char *tempValues = new char[LINELENGTH];

        strcpy (tempName,source.getName());
        sprintf(tempValues , "%.0f %.0f %.0f %.0f %.0f %.0f",(double)TIMED,
                source.getFrequency(),source.getStartTime(),source.getDuration(),
                (double)source.getRows(),(double)source.getCols());

        xenomPair< char* , char* > *tempPair = new xenomPair< char* , char* >;

        tempPair->first = tempName;
        tempPair->second = tempValues;

        logArray.appendElement(*tempPair);
    }
}


//==============================================================================
// Config::updateVariable
//==============================================================================
void Config::updateVariable(Array<ControlVariable*>& source)
{
    for (int counter = 0 ; counter < source.getNumElements() ; ++counter )
        this->updateVariable( *(source.getElement(counter)) );
}

//==============================================================================
// Config::updateVariable
//==============================================================================
void Config::updateVariable(Array<LogVariable*>& source)
{
    for (int counter = 0 ; counter < source.getNumElements() ; ++counter )
        this->updateVariable( *(source.getElement(counter)) );
}


//==============================================================================
// Config::setValue
//==============================================================================
void Config::setValue(Array<LogVariable*>& dest)
{
     for (int counter = 0 ; counter < dest.getNumElements() ; ++counter )
         this->setValue( dest.getElement( counter ) );
}

//==============================================================================
// Config::setValue
//==============================================================================
void Config::setValue(Array<ControlVariable*>& dest)
{
     for (int counter = 0 ; counter < dest.getNumElements() ; ++counter )
         this->setValue( dest.getElement( counter ) );
}


//==============================================================================
// Config::setValueGUI
//==============================================================================
void Config::setValueGUI(Array<ControlVariable*>& dest)
{
    
    char tempName [ MAXARRAYSIZE ];
    double tempDoubleArray [ MAXARRAYSIZE ];
    ControlVariable *tempPtr;
    for (int counter = 0 ; counter < this->controlArray.getNumElements() ; ++counter )
    {
        strcpy(tempName,controlArray.getElement(counter).first );
        
        this->charToValue(controlArray.getElement(counter).second , tempDoubleArray);

        double *newControlVariableValues = new double[ (int)(tempDoubleArray[0]) * (int)(tempDoubleArray[1]) ];

        for(int counter = 0 ; counter < int(tempDoubleArray[0] * tempDoubleArray[1] ) ; ++counter )
            newControlVariableValues[counter] = tempDoubleArray[counter+2];

        tempPtr = new ControlVariable( newControlVariableValues ,tempName , "" , (int)(tempDoubleArray[0]),(int)(tempDoubleArray[1]) );

        dest.appendElement(tempPtr);
    }
}


//==============================================================================
// Config::setValueGUI
//==============================================================================
void Config::setValueGUI(Array<LogVariableGUI*>& dest)
{
    
    char tempName [ MAXARRAYSIZE ];
    double tempDoubleArray [ MAXARRAYSIZE ];
    LogVariableGUI *tempPtr;
    for (int counter = 0 ; counter < this->logArray.getNumElements() ; ++counter )
    {
        strcpy(tempName,logArray.getElement(counter).first );

        this->charToValue(logArray.getElement(counter).second , tempDoubleArray);

        double *newLogVariableValues = new double[(int)(tempDoubleArray[4]) * (int)(tempDoubleArray[5]) ];


        tempPtr = new LogVariableGUI( newLogVariableValues ,tempName , "" , (int)(tempDoubleArray[4]),(int)(tempDoubleArray[5]) );
        tempPtr->setFrequency(tempDoubleArray[1]);
        tempPtr->setStartTime(tempDoubleArray[2]);
        tempPtr->setDuration(tempDoubleArray[3]);

        dest.appendElement(tempPtr);
    }
    logVariableGUIArray = &dest;
}

void Config::resetArrays(){

    for(int counter = 0; counter < 3 ; ++counter )
        for(int counter2 = 0; counter2 < arrayVec[counter]->getNumElements() ;++counter2)
        {
            delete arrayVec[counter]->getElement(counter2).first;
            delete arrayVec[counter]->getElement(counter2).second;
        }
   
    for(int counter = 0; counter < this->arrayGUI->getNumElements() ; ++counter )
        for(int counter2 = 0; counter2 < arrayGUI->getElement(counter)->getNumElements() ;++counter2)
        {
            delete arrayGUI->getElement(counter)->getElement(counter2).first;
            delete arrayGUI->getElement(counter)->getElement(counter2).second;
        }

    logArray.removeAllElements();
    controlArray.removeAllElements();

}


//==============================================================================
// Config::updateMainWindow
//==============================================================================
void Config::updateMainWindow(MainWindowConfig &mainWin)
{
    mainWindow = mainWin;
}


//==============================================================================
// Config::updatePlotXYWindows
//==============================================================================
void Config::updatePlotXYWindows(Array<PlotXYConfig>& plotXYWindows)
{
    plotXYWindowsVec = plotXYWindows;
}

//==============================================================================
// Config::updatePlotWindows
//==============================================================================
void Config::updatePlotWindows(Array<PlotConfig>& plotWindows)
{
    plotWindowsVec = plotWindows;
}

//==============================================================================
// Config::updateWatchWindows
//==============================================================================
void Config::updateWatchWindows(Array<WatchConfig>& watchWindows)
{
    watchWindowsVec = watchWindows;
}

//==============================================================================
// Config::updateSceneWindows
//==============================================================================
void Config::updateSceneWindows(Array<SceneWindowConfig>& sceneWindows)
{
    sceneWindowsVec = sceneWindows;
}


//==============================================================================
// Config::readMainWindowLine
//==============================================================================
void Config::readMainWindowLine(char *textLine)
{
    sscanf(textLine,"%d%d%d%d",&(mainWindow.x),
                            &(mainWindow.y),&(mainWindow.w),
                            &(mainWindow.h));
}


//==============================================================================
// Config::readPlotLine
//==============================================================================
void Config::readPlotLine(Array<char *> & textVec)
{
    //cout << "PlotLine reader started" << endl;
    //for(int i = 0 ; i < textVec.getNumElements(); ++i  )
    //     cout << textVec.getElement(i) << endl;
    char variableName[LINELENGTH];
    int index,color;
    PlotConfig plotWin;
    int isScaled,isTranslated;
    sscanf(textVec.getElement(0),"%d%d%d%d%d%d", &(plotWin.x), &(plotWin.y),
           &(plotWin.w), &(plotWin.h), &isScaled, &isTranslated);

    LogVarLine logVarLine;

    for(int i = 1 ; i < textVec.getNumElements(); ++i  )
    {
        sscanf(textVec.getElement(i),"%s%d%d",variableName,&index,&color);
        //cout << "variableName" << variableName << endl;
        logVarLine.logVariable = findLogVariableGUI(string(variableName));
        //cout << "LogVariable Name : ";
        //cout << logVarLine.logVariable->getName();
        //cout << endl;
        logVarLine.index = index;
        logVarLine.color = color;
        if (logVarLine.logVariable != NULL)
            plotWin.line.appendElement(logVarLine);
    }
    
    if (isScaled == 1)
        plotWin.isAutoScale = true;
    else
        plotWin.isAutoScale = false;
    
    if (isTranslated == 1)
        plotWin.isAutoTranslate = true;
    else
        plotWin.isAutoTranslate = false;


    //cout << "New Plot Window Added plotwindowsVec from conf file" << endl;
    plotWindowsVec.appendElement(plotWin);
    return;
}

//==============================================================================
// Config::readPlotXYLine
//==============================================================================
void Config::readPlotXYLine(Array<char *> & textVec)
{
    char variableName[LINELENGTH];
    int color;
    PlotXYConfig plotXYWin;
    int isScaled;
    sscanf(textVec.getElement(0),"%d%d%d%d%d",&(plotXYWin.x),&(plotXYWin.y),
           &(plotXYWin.w),&(plotXYWin.h),&isScaled);


    LogVarLine logVarLine;

    for(int i = 1 ; i < textVec.getNumElements(); ++i  )
    {
        sscanf(textVec.getElement(i),"%s%d",variableName,&color);
        logVarLine.logVariable = findLogVariableGUI(string(variableName));
        logVarLine.index = NULL;
        logVarLine.color = color;
        if (logVarLine.logVariable != NULL)
            plotXYWin.line.appendElement(logVarLine);
    }

    if (isScaled == 1)
        plotXYWin.isAutoScale = true;
    else
        plotXYWin.isAutoScale = false;

    plotXYWindowsVec.appendElement(plotXYWin);
    return;
}


//==============================================================================
// Config::readWatchLine
//==============================================================================
void Config::readWatchLine(char *textLine)
{
     WatchConfig watchWin;
     char logVariableName[NAMELENGTH];
     sscanf(textLine,"%d%d%d%d%s%d%d%d",&(watchWin.x),&(watchWin.y),
           &(watchWin.w),&(watchWin.h),logVariableName,
             &(watchWin.backgroundColor),&(watchWin.sevenSegmentColor),
             &(watchWin.precision));

     string temp(logVariableName);

     watchWin.logVariable = findLogVariableGUI(temp);

     if ( watchWin.logVariable != NULL )
         watchWindowsVec.appendElement(watchWin);
     return;
}


//==============================================================================
// Config::readSceneLine
//==============================================================================
void Config::readSceneLine(Array<char *> & textVec)
{
    SceneWindowConfig sceneWin;
    sscanf(textVec.getElement(0), "%d%d%d%d", &(sceneWin.x), &(sceneWin.y),
            &(sceneWin.w), &(sceneWin.h) );

    int mode = 0;
    char *text;
    SceneBindVariableConfig bindVar;
    for(int i = 1 ; i < textVec.getNumElements(); ++i  )
    {
        if ( strcmp(textVec.getElement(i),"<VrmlFiles>") == 0 )
            mode = 1;
        else if ( strcmp(textVec.getElement(i),"</VrmlFiles>") == 0)
            mode = 0;
        else if ( strcmp(textVec.getElement(i),"<paths>") == 0)
            mode = 2;
        else if ( strcmp(textVec.getElement(i),"</paths>") == 0)
            mode = 0;

        if (mode == 1)
        {
            ++i;
            while( strcmp(textVec.getElement(i),"</VrmlFiles>") != 0)
            {
                sceneWin.vrmlFiles.appendElement(textVec.getElement(i));
                ++i;
            }

        }
        else if (mode == 2)
        {
            ++i;
            while ( strcmp(textVec.getElement(i),"</paths>") != 0 )
            {
                bindVar.path = textVec.getElement(i);
                char varName[LINELENGTH];
                int index;
                ++i;
                sscanf(textVec.getElement(i),"%s%d", varName, &index);
                string varNameStr(varName);
                bindVar.logVariable = this->findLogVariableGUI(varNameStr);
                bindVar.index = index;

                if (bindVar.logVariable != NULL)
                    sceneWin.bindedVariable.appendElement(bindVar);
                i++;
            }
        }
    }
    sceneWindowsVec.appendElement(sceneWin);
    return;
}


//==============================================================================
// Config::saveToFile
//==============================================================================
bool Config::saveToFileGUI(ofstream &outputfile)
{
    outputfile << CONFIGFILEMAINWINDOWBEGIN << endl;
    outputfile << mainWindow.x << " "
            << mainWindow.y << " "
            << mainWindow.w << " "
            << mainWindow.h << endl;


    outputfile << endl << CONFIGFILEWATCHBEGIN << endl;
    for(int i = 0 ; i < watchWindowsVec.getNumElements(); ++i )
    {
        if (watchWindowsVec.getElement(i).logVariable != NULL)
            outputfile << watchWindowsVec.getElement(i).x << " "
                    << watchWindowsVec.getElement(i).y << " "
                    << watchWindowsVec.getElement(i).w << " "
                    << watchWindowsVec.getElement(i).h << " "
                    << watchWindowsVec.getElement(i).logVariable->getName() << " "
                    << watchWindowsVec.getElement(i).backgroundColor << " "
                    << watchWindowsVec.getElement(i).sevenSegmentColor << " "
                    << watchWindowsVec.getElement(i).precision << endl;
    }
    outputfile << endl;

    for(int i = 0 ; i < plotWindowsVec.getNumElements(); ++i )
    {
        int autoScaled,autoTranslated;
        if (plotWindowsVec.getElement(i).isAutoScale)
            autoScaled = true;
        else
            autoScaled = false;

        if (plotWindowsVec.getElement(i).isAutoTranslate)
            autoTranslated = true;
        else
            autoTranslated = false;


        outputfile << endl << CONFIGFILEPLOTBEGIN << endl;
        outputfile << plotWindowsVec.getElement(i).x << " "
                << plotWindowsVec.getElement(i).y << " "
                << plotWindowsVec.getElement(i).w << " "
                << plotWindowsVec.getElement(i).h << " "
                << autoScaled << " "
                << autoTranslated << endl;

        for(int j = 0; j < plotWindowsVec.getElement(i).line.getNumElements(); ++j)
            if (plotWindowsVec.getElement(i).line.getElement(j).logVariable != NULL)
                outputfile << plotWindowsVec.getElement(i).line.getElement(j).logVariable->getName() << " "
                    << plotWindowsVec.getElement(i).line.getElement(j).index << " "
                    << plotWindowsVec.getElement(i).line.getElement(j).color << endl;
        outputfile << CONFIGFILEPLOTEND << endl;

    }
    outputfile << endl;


    for(int i = 0 ; i < plotXYWindowsVec.getNumElements(); ++i )
    {
        outputfile << endl << CONFIGFILEPLOTXYBEGIN << endl;
        outputfile << plotXYWindowsVec.getElement(i).x << " "
                << plotXYWindowsVec.getElement(i).y << " "
                << plotXYWindowsVec.getElement(i).w << " "
                << plotXYWindowsVec.getElement(i).h << " "
                << plotWindowsVec.getElement(i).isAutoScale << endl;

         for(int j = 0; j < plotXYWindowsVec.getElement(i).line.getNumElements(); ++j)
             if (plotXYWindowsVec.getElement(i).line.getElement(j).logVariable != NULL)
                 outputfile << plotXYWindowsVec.getElement(i).line.getElement(j).logVariable->getName() << " "
                       << plotXYWindowsVec.getElement(i).line.getElement(j).index << " "
                       << plotXYWindowsVec.getElement(i).line.getElement(j).color << endl;
        outputfile << CONFIGFILEPLOTXYEND << endl;

    }
    outputfile << endl;

    for(int i = 0; i < sceneWindowsVec.getNumElements() ; ++i)
    {
        outputfile << endl << CONFIGFILESCENEBEGIN << endl;
        outputfile << sceneWindowsVec.getElement(i).x << " "
                << sceneWindowsVec.getElement(i).y << " "
                << sceneWindowsVec.getElement(i).w << " "
                << sceneWindowsVec.getElement(i).h << endl;

        outputfile << "<VrmlFiles>" << endl;
        for(int j = 0; j < sceneWindowsVec.getElement(i).vrmlFiles.getNumElements(); ++j)
            outputfile << sceneWindowsVec.getElement(i).vrmlFiles.getElement(j) << endl;

        outputfile << "</VrmlFiles>" << endl << endl;

        outputfile << "<paths>" << endl;
        for(int j = 0; j < sceneWindowsVec.getElement(i).bindedVariable.getNumElements(); ++j)
            if (sceneWindowsVec.getElement(i).bindedVariable.getElement(j).logVariable != NULL)
                outputfile << sceneWindowsVec.getElement(i).bindedVariable.getElement(j).path << endl
                        << sceneWindowsVec.getElement(i).bindedVariable.getElement(j).logVariable->getName() << " "
                        << sceneWindowsVec.getElement(i).bindedVariable.getElement(j).index << endl;
        outputfile << "</paths>" << endl << endl;

        outputfile << CONFIGFILESCENEEND << endl;
    }
    return true;
}


//==============================================================================
// Config::findLogVariableGUI
//==============================================================================
LogVariableGUI* Config::findLogVariableGUI(string name)
{
    for(int i = 0; i < logVariableGUIArray->getNumElements() ; ++i)
        if( strcmp (logVariableGUIArray->getElement(i)->getName(), name.c_str()) == 0 )
            return logVariableGUIArray->getElement(i);
    return NULL;
}


//==============================================================================
// Config::clearWindowVecs
//==============================================================================
void Config::clearWindowVecs()
{
    plotWindowsVec.removeAllElements();

    plotXYWindowsVec.removeAllElements();

    watchWindowsVec.removeAllElements();

    sceneWindowsVec.removeAllElements();
}


//==============================================================================
// Config::getMainWindow
//=========================================================================
MainWindowConfig Config::getMainWindow()
{
    return mainWindow;
}

//==============================================================================
// Config::getWatchWindows
//==============================================================================
Array< WatchConfig>* Config::getWatchWindows()
{
    return &watchWindowsVec;
}


//==============================================================================
// Config::getPlotXYWindows
//==============================================================================
Array< PlotXYConfig >* Config::getPlotXYWindows()
{
    return &plotXYWindowsVec;
}

//==============================================================================
// Config::getPlotWindows
//==============================================================================
Array< PlotConfig >* Config::getPlotWindows()
{
    return &plotWindowsVec;
}

//==============================================================================
// Config::getSceneWindows
//==============================================================================
Array< SceneWindowConfig >* Config::getSceneWindows()
{
    return &sceneWindowsVec;
}


//==============================================================================
// Config::storeFileGUI
//==============================================================================
bool Config::storeFileGUI()
{
    char *textLine = new char[LINELENGTH];

    ifstream inputFile;

    inputFile.open(fileName, std::ios::in );

    guiConfigFileStorage.deleteAllElements();
    
    if ( ! inputFile.is_open() )
        return false;
    else
    {
        do
            inputFile.getline( textLine ,LINELENGTH );
        while ( strcmp( CONFIGFILEGUIBEGIN , textLine ) != 0 );

        delete[] textLine;

        while(! inputFile.eof() )
        {
            textLine = new char[LINELENGTH];
            inputFile.getline( textLine ,LINELENGTH );
            guiConfigFileStorage.appendElement(textLine);
        }
    }
    return true;
}

//==============================================================================
// Config::printFileGUI
//==============================================================================
bool Config::printFileGUI(ofstream &outputfile)
{
    outputfile << endl << CONFIGFILEGUIBEGIN << endl << endl;

    for(int i = 0; i < guiConfigFileStorage.getNumElements(); ++i)
        outputfile << guiConfigFileStorage.getElement(i) << endl;
}

