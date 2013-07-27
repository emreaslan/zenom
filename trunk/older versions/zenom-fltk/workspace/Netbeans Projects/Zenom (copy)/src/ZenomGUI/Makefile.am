lib_LIBRARIES = libZenomGUI.a


SCENEPATH = ../../include/ZenomGUI/Scene

SCENE_HS = $(SCENEPATH)/utils.h \
$(SCENEPATH)/Camera.h \
$(SCENEPATH)/Vector3D.h \
$(SCENEPATH)/VectorRotater.h \
$(SCENEPATH)/Scene.h \
$(SCENEPATH)/SceneWindow.h \
$(SCENEPATH)/vrmlparserstructs.h \
$(SCENEPATH)/ZAppearance.h \
$(SCENEPATH)/ZBox.h \
$(SCENEPATH)/ZColorNode.h \
$(SCENEPATH)/ZCone.h \
$(SCENEPATH)/ZCoordinate.h \
$(SCENEPATH)/ZCylinder.h \
$(SCENEPATH)/ZDirectionalLight.h \
$(SCENEPATH)/ZElevationGrid.h \
$(SCENEPATH)/ZGeometry.h \
$(SCENEPATH)/ZGroup.h \
$(SCENEPATH)/ZIndexedFaceSet.h \
$(SCENEPATH)/ZIndexedLineSet.h \
$(SCENEPATH)/ZMaterial.h \
$(SCENEPATH)/ZNavigationInfo.h \
$(SCENEPATH)/ZNormal.h \
$(SCENEPATH)/ZNotSupportedNode.h \
$(SCENEPATH)/ZParameter.h \
$(SCENEPATH)/ZPointLight.h \
$(SCENEPATH)/ZPointSet.h \
$(SCENEPATH)/ZShape.h \
$(SCENEPATH)/ZTransform.h \
$(SCENEPATH)/ZViewpoint.h \
$(SCENEPATH)/ZVrmlNode.h



ZENOMGUIPATH = ../../include/ZenomGUI

ZENOMGUI_HS = $(ZENOMGUIPATH)/controlVarWindow.h \
$(ZENOMGUIPATH)/TextDisplayWidget.h \
$(ZENOMGUIPATH)/GlPlotWindow.h \
$(ZENOMGUIPATH)/GlPlotWindowBase.h \
$(ZENOMGUIPATH)/GlPlotXYWindow.h \
$(ZENOMGUIPATH)/Line.h \
$(ZENOMGUIPATH)/LineBase.h \
$(ZENOMGUIPATH)/LineXY.h \
$(ZENOMGUIPATH)/logVarWindow.h \
$(ZENOMGUIPATH)/PlotBaseWindow.h \
$(ZENOMGUIPATH)/PlotRectangle.h \
$(ZENOMGUIPATH)/PlotSelectedItem.h \
$(ZENOMGUIPATH)/PlotWindow.h \
$(ZENOMGUIPATH)/PlotXYWindow.h \
$(ZENOMGUIPATH)/SevenSegment.h \
$(ZENOMGUIPATH)/WatchSelectWindow.h \
$(ZENOMGUIPATH)/WatchWindow.h \
$(ZENOMGUIPATH)/ZButton.h \
$(ZENOMGUIPATH)/zenom.h 

SceneHSdir = $(includedir)/ZenomGUI/Scene
SceneHS_HEADERS = $(SCENE_HS)

ZenomGUIHSdir = $(includedir)/ZenomGUI
ZenomGUIHS_HEADERS = $(ZENOMGUI_HS) 

SCENESOURCEPATH = ./Scene

SCENE_SOURCES = $(SCENESOURCEPATH)/utils.cpp \
$(SCENESOURCEPATH)/Camera.cpp \
$(SCENESOURCEPATH)/Vector3D.cpp \
$(SCENESOURCEPATH)/VectorRotater.cpp \
$(SCENESOURCEPATH)/Scene.cpp \
$(SCENESOURCEPATH)/SceneWindow.cpp \
$(SCENESOURCEPATH)/ZAppearance.cpp \
$(SCENESOURCEPATH)/ZBox.cpp \
$(SCENESOURCEPATH)/ZColorNode.cpp \
$(SCENESOURCEPATH)/ZCone.cpp \
$(SCENESOURCEPATH)/ZCoordinate.cpp \
$(SCENESOURCEPATH)/ZCylinder.cpp \
$(SCENESOURCEPATH)/ZDirectionalLight.cpp \
$(SCENESOURCEPATH)/ZElevationGrid.cpp \
$(SCENESOURCEPATH)/ZGeometry.cpp \
$(SCENESOURCEPATH)/ZGroup.cpp \
$(SCENESOURCEPATH)/ZIndexedFaceSet.cpp \
$(SCENESOURCEPATH)/ZIndexedLineSet.cpp \
$(SCENESOURCEPATH)/ZMaterial.cpp \
$(SCENESOURCEPATH)/ZNavigationInfo.cpp \
$(SCENESOURCEPATH)/ZNormal.cpp \
$(SCENESOURCEPATH)/ZNotSupportedNode.cpp \
$(SCENESOURCEPATH)/ZPointLight.cpp \
$(SCENESOURCEPATH)/ZPointSet.cpp \
$(SCENESOURCEPATH)/ZShape.cpp \
$(SCENESOURCEPATH)/ZSphere.cpp \
$(SCENESOURCEPATH)/ZSpotLight.cpp \
$(SCENESOURCEPATH)/ZTransform.cpp \
$(SCENESOURCEPATH)/ZViewpoint.cpp \
$(SCENESOURCEPATH)/ZVrmlNode.cpp


ZENOMGUI_SOURCES = TextDisplayWidget.cpp ControlVarWindow.cpp GlPlotWindow.cpp GlPlotWindowBase.cpp GlPlotXYWindow.cpp Line.cpp LineBase.cpp LineXY.cpp logVarWindow.cpp messageHandler.cpp PlotBaseWindow.cpp PlotRectangle.cpp PlotSelectedItem.cpp PlotWindow.cpp PlotXYWindow.cpp SevenSegment.cpp WatchSelectWindow.cpp WatchWindow.cpp WatchWindowUpdater.cpp ZButton.cpp zenom.cpp

COMMON_SOURCES = ../Common/Config.cpp ../Common/ControlVariable.cpp  ../Common/LogVariable.cpp ../Common/LogVariableBase.cpp ../Common/../Common/LogVariableGUI.cpp ../Common/Variable.cpp ../Common/guiMessenger.cpp

libZenomGUI_a_SOURCES = $(SCENE_SOURCES) $(ZENOMGUI_SOURCES) $(COMMON_SOURCES) 

ZenomGUISourcedir = ${prefix}/src/ZenomGUI
ZenomGUISource_HEADERS = $(ZENOMGUI_SOURCES)

SceneSourcedir = ${prefix}/src/ZenomGUI/Scene
SceneSource_HEADERS = $(SCENE_SOURCES)


XENOMAI_CFLAGS = -I /usr/xenomai/include -D_GNU_SOURCE -D_REENTRANT -Wall -pipe -D__XENO__ -I /usr/xenomai/include -I /usr/xenomai/include/posix -D_GNU_SOURCE -D_REENTRANT -Wall -pipe -D__XENO__

OPENVRML_FLAG = -I /usr/include/openvrml/ -DBOOST_SPIRIT_THREADSAFE -DBOOST_SPIRIT_CLOSURE_LIMIT=6 -DPHOENIX_LIMIT=6

RTNET_FLAG = -I /usr/local/rtnet/include
SCENE_FLAG = -I ../../include/ZenomGUI/Scene
ZENOMGUI_FLAG = -I ../../include/ZenomGUI
COMMON_FLAG= -I ../../include/Common
QMATH_FLAG = -I ../../include/QMath
NATIVE_INCLUDE_FLAG = -I ../../include/XenoTools/native
POSIX_INCLUDE_FLAG = -I ../../include/XenoTools/posix
FLTK_INCLUDE_FLAG = -I/usr/local/include
FLTK_FLAGS = -L/usr/local/lib -lfltk2 -lX11 -lXi -lXinerama -lXcursor -lXft -lXext -lfltk2_gl -lfltk2_glut
OPENVRML_LIB_FLAG = -L/usr/lib64 -lopenvrml


ZENOMGUILIB_FLAGS = $(NATIVE_INCLUDE_FLAG) $(POSIX_INCLUDE_FLAG) $(COMMON_FLAG) $(QMATH_FLAG) $(XENOMAI_CFLAGS) $(ZENOMGUI_FLAG) $(RTNET_FLAG) $(FLTK_FLAGS) $(FLTK_INCLUDE_FLAG) $(SCENE_FLAG) $(OPENVRML_FLAG) 
 
libZenomGUI_a_INCLUDES = $(ZENOMGUILIB_FLAGS) 
INCLUDES =  $(ZENOMGUILIB_FLAGS)
LIBS = $(OPENVRML_LIB_FLAG)

