//==============================================================================
// Config.cpp    - Config file read and write operations
//
// Author        :
// Version       : 1.0.00 (Agustos 2009)
// Compatibility : XENOMAI, GCC
//==============================================================================


#include "Config.h"

Array<LogVariable*>* Utils::mLogVars = NULL;
Array<LogVariableGUI*>* Utils::mLogVarsGUI = NULL;
Array<ControlVariable*> *Utils::mControlVars = NULL;



//==============================================================================
// Config::Config
//==============================================================================
Config::Config(const char* name,bool pIsConfig )
{
    fileName = NULL;
    isGUI = pIsConfig ;
    setFileName( name );
    
    if (!pIsConfig)
    {
        if (!mConfigXML.load_file(fileName))
        {
            cout << "XML Load Error" << endl;
            cout << "Simulation terminated!" << endl;
            exit(-1);
        }
    }
}

// Config::~Config
//==============================================================================
Config::~Config( )
{

}




//==============================================================================
// Config::saveToFile
//==============================================================================
bool Config::saveToFile()
{
    mConfigXML.save_file(fileName);

    return true;
}


//==============================================================================
// Config::setFileName
//==============================================================================
bool Config::setFileName(const char* name)
{
    char *tempFileName = new char[LINELENGTH];
    strcpy (tempFileName , name) ;

    for (int i = 1; i < LINELENGTH; ++i)
	if ( tempFileName[i] == '\000' )
	    break;
	else if (tempFileName[i] == '.')
	{
	    tempFileName[i] = '\000';
	    break;
	}
    delete fileName;
    fileName = new char[strlen(tempFileName) + 4];
    sprintf(fileName,"%s%s", tempFileName,".xml");
    delete tempFileName;
    return true;
}



//==============================================================================
// Config::updateVariable
//==============================================================================
void Config::updateVariable(const double frequency,const double duration)
{
    pugi::xml_node ControlBase = mConfigXML.child("CONTROL_BASE");
    pugi::xml_node frequencyXML = ControlBase.append_child("Frequency");
    frequencyXML.append_attribute("name") = "Frequency";
    frequencyXML.append_attribute("value") = (int)frequency;
    pugi::xml_node descrF = frequencyXML.append_child("description");
    descrF.append_child(pugi::node_pcdata).set_value("Benzetim Calisma Frekansi");

    pugi::xml_node durationXML = ControlBase.append_child("Duration");
    durationXML.append_attribute("name") = "Duration";
    durationXML.append_attribute("value") = (int)duration;
    pugi::xml_node descrD = durationXML.append_child("description");
    descrD.append_child(pugi::node_pcdata).set_value("Benzetim Calisma Suresi");
}



//==============================================================================
// Config::updateVariable
//==============================================================================
void Config::updateVariable(Array<ControlVariable*>& source)
{
    pugi::xml_node controlVariables = mConfigXML.child(CONFIGXMLCONTROL);
    for (int i = 0; i < source.getNumElements() ; ++i )
    {
        pugi::xml_node controlVarXML = controlVariables.append_child("Control_Variable");
        controlVarXML.append_attribute("name") = source[i]->getName();
        controlVarXML.append_attribute("Rows") = source[i]->getRows();
        controlVarXML.append_attribute("Columns") = source[i]->getCols();
        for (int j = 0 ; j < source[i]->getSize() ; ++j)
        {
            pugi::xml_node valueXML = controlVarXML.append_child("Value");
            valueXML.append_attribute("value") = source[i]->getElement(j);
        }
    }
}

//==============================================================================
// Config::setValueGUI
//==============================================================================
void Config::setValueGUI(Array<ControlVariable*>& dest)
{
    pugi::xml_node controlVariables = mConfigXML.child(CONFIGXMLCONTROL);
    ControlVariable *controlVarPtr;

    for (pugi::xml_node controlVar = controlVariables.first_child(); controlVar; controlVar = controlVar.next_sibling())
    {
        int rows = controlVar.attribute("Rows").as_int();
        int columns = controlVar.attribute("Columns").as_int();
        double *newControlVariableValues = new double[rows*columns];
        int i = 0;
        for ( pugi::xml_node valueNode = controlVar.first_child(); valueNode; valueNode = valueNode.next_sibling(), ++i )
            newControlVariableValues[i] = valueNode.attribute("value").as_double();
        controlVarPtr = new ControlVariable(newControlVariableValues, controlVar.attribute("name").value(), "", rows, columns);
        dest.appendElement(controlVarPtr);
    }
}

//==============================================================================
// Config::updateVariable
//==============================================================================
void Config::updateVariable(Array<LogVariable*>& source)
{
    pugi::xml_node logVariables = mConfigXML.child(CONFIGXMLLOG);
    for (int i = 0; i < source.getNumElements() ; ++i )
    {
        pugi::xml_node logVar = logVariables.append_child("Log_Variable");
        logVar.append_attribute("name") = source[i]->getName();
        logVar.append_attribute("LogType") = TIMED;
        logVar.append_attribute("Frequency") = source[i]->getFrequency();
        logVar.append_attribute("StartTime") = source[i]->getStartTime();
        logVar.append_attribute("Duration") = source[i]->getDuration();
        logVar.append_attribute("Rows") = source[i]->getRows();
	logVar.append_attribute("Columns") = source[i]->getCols();
    }
}

void Config::updateVariable(Array<LogVariableGUI*>& source)
{
    pugi::xml_node logVariables = mConfigXML.child(CONFIGXMLLOG);
    for (int i = 0; i < source.getNumElements() ; ++i )
    {
        pugi::xml_node logVar = logVariables.append_child("Log_Variable");
        logVar.append_attribute("name") = source[i]->getName();
        logVar.append_attribute("LogType") = TIMED;
        logVar.append_attribute("Frequency") = source[i]->getFrequency();
        logVar.append_attribute("StartTime") = source[i]->getStartTime();
        logVar.append_attribute("Duration") = source[i]->getDuration();
        logVar.append_attribute("Rows") = source[i]->getRows();
	logVar.append_attribute("Columns") = source[i]->getCols();
    }
}




//==============================================================================
// Config::setValueGUI
//==============================================================================
void Config::setValueGUI(Array<LogVariableGUI*>& dest)
{
     pugi::xml_node logVariables = mConfigXML.child(CONFIGXMLLOG);

     LogVariableGUI *newLogVarPtr;
     for (pugi::xml_node logVarNode = logVariables.first_child(); logVarNode; logVarNode = logVarNode.next_sibling())
     {
         int rows = logVarNode.attribute("Rows").as_int();
         int columns = logVarNode.attribute("Columns").as_int();
         double *newLogVariableValues = new double[rows * columns];
         newLogVarPtr = new LogVariableGUI( newLogVariableValues , logVarNode.attribute("name").value() , "" , rows, columns);
         newLogVarPtr->setFrequency( logVarNode.attribute("Frequency").as_double());
         newLogVarPtr->setStartTime( logVarNode.attribute("StartTime").as_double());
         newLogVarPtr->setDuration( logVarNode.attribute("Duration").as_double());
         dest.appendElement(newLogVarPtr);
     }
}

//==============================================================================
// Config::setValue
//==============================================================================
void Config::setValue(Array<LogVariable*>& dest)
{
     pugi::xml_node logVariables = mConfigXML.child(CONFIGXMLLOG);
     LogVariable *logVarPtr;
     for (pugi::xml_node logVarNode = logVariables.first_child(); logVarNode; logVarNode = logVarNode.next_sibling())
     {
         logVarPtr = Utils::findLogVariable(logVarNode.attribute("name").value());
         if (!logVarPtr)
             continue;
         logVarPtr->setFrequency( logVarNode.attribute("Frequency").as_double());
         logVarPtr->setStartTime( logVarNode.attribute("StartTime").as_double());
         logVarPtr->setDuration( logVarNode.attribute("Duration").as_double());
     }
}


//==============================================================================
// Config::setValue
//==============================================================================
void Config::setValue(Array<ControlVariable*>& dest)
{

    pugi::xml_node controlVariables = mConfigXML.child(CONFIGXMLCONTROL);
    ControlVariable *controlVarPtr;

    for (pugi::xml_node controlVar = controlVariables.first_child(); controlVar; controlVar = controlVar.next_sibling())
    {
        controlVarPtr = Utils::findControlVariable( controlVar.attribute("name").value());
        if (!controlVarPtr)
            continue;
        int i = 0;
        for ( pugi::xml_node valueNode = controlVar.first_child(); valueNode; valueNode = valueNode.next_sibling(), ++i )
            controlVarPtr->getElementPtr()[i] = valueNode.attribute("value").as_double();
    }

}



int Config::getFrequency()
{
    return mConfigXML.child("CONTROL_BASE").child("Frequency").attribute("value").as_int();
}

int Config::getDuration()
{
    return mConfigXML.child("CONTROL_BASE").child("Duration").attribute("value").as_int();
}


pugi::xml_node Config::appendChild(const char* pChildName)
{
    return mConfigXML.append_child(pChildName);
}


void Config::resetXMLFile(bool pIsConfig)
{
    if( pIsConfig)
    {
        mConfigXML.remove_child("CONTROL_BASE");
        mConfigXML.remove_child(CONFIGXMLCONTROL);
        mConfigXML.remove_child(CONFIGXMLLOG);
    }
    else
        mConfigXML.reset();

    mConfigXML.append_child("CONTROL_BASE");
    mConfigXML.append_child(CONFIGXMLLOG);
    mConfigXML.append_child(CONFIGXMLCONTROL);
}


pugi::xml_node Config::getChild(const char* pChildName)
{
    return mConfigXML.child(pChildName);
}
