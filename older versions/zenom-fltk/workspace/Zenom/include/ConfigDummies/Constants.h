/* 
 * File:   Constants.h
 * Author: RobotLab
 *
 * Created on August 14, 2009, 3:43 PM
 */

#ifndef _CONSTANTS_H
#define	_CONSTANTS_H

//////////////////////////
// ControlBase sabitleri
#define HELPCOMMAND "--help"
#define GUICOMMAND "--gui"
#define CFGCOMMAND "--cfg"
#define ONESECOND (1000000000)
// ControlBase sabitleri
//////////////////////////

//////////////////////////
// guiMessenger sabitleri
#define QUEUESTART "--start"
#define QUEUESTOP "--stops"
#define QUEUEPAUSE "--pause"
#define QUEUEUNBIND "--unbind"
#define QUEUEBIND "--bind"
#define QUEUEACTIVE "--active"
// guiMessenge sabitleri
//////////////////////////




//////////////////////////
// Config.h sabitleri
enum variableTypes { GENERAL, LOG , CONTROL , GUI };
enum loggingTypes { TIMED , EVENTTRIGGED , NOLOGGING };
enum stateTypes { START , STOP , PAUSE };

#define CONFIGFILEEXTENSION ".xml"

#define CONFIGXMLLOG "LOG_VARIABLES"
#define CONFIGXMLGENERAL "GENERAL"
#define CONFIGXMLCONTROL "CONTROL_VARIABLES"

#define LINELENGTH 255
#define NAMELENGTH 80
#define MAXARRAYSIZE 80


#define CONFIGGUINAME "<Name>"
// Config.h Sabitleri
///////////////////////////



#endif	/* _CONSTANTS_H */

