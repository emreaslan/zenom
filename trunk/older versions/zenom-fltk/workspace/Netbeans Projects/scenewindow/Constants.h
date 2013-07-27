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

#define CONFIGFILEEXTENSION ".cfg"

#define CONFIGFILEBEGIN "<XENOM_FILE>"
#define CONFIGFILEGUIBEGIN "<GUI>"
#define CONFIGFILEPLOTBEGIN "<PLOT>"
#define CONFIGFILEPLOTEND "</PLOT>"
#define CONFIGFILEPLOTXYBEGIN "<PLOTXY>"
#define CONFIGFILEPLOTXYEND "</PLOTXY>"
#define CONFIGFILEWATCHBEGIN "<WATCH>"
#define CONFIGFILEMAINWINDOWBEGIN "<MAINWINDOW>"
#define CONFIGFILESCENEBEGIN "<SCENE>"
#define CONFIGFILESCENEEND "</SCENE>"

#define CONFIGFILELOG "<LOG_VARIABLES>"
#define CONFIGFILEGENERAL "<GENERAL>"
#define CONFIGFILECONTROL "<CONTROL_VARIABLES>"

#define LINELENGTH 255
#define NAMELENGTH 80
#define MAXARRAYSIZE 80


#define CONFIGGUINAME "<Name>"
// Config.h Sabitleri
///////////////////////////



#endif	/* _CONSTANTS_H */

