#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1413408311/ZCoordinate.o \
	${OBJECTDIR}/_ext/1413408311/ZNormal.o \
	${OBJECTDIR}/_ext/783283226/WatchSelectWindow.o \
	${OBJECTDIR}/_ext/1413408311/SceneWindow.o \
	${OBJECTDIR}/_ext/2016048053/guiMessenger.o \
	${OBJECTDIR}/_ext/1413408311/ZPointLight.o \
	${OBJECTDIR}/_ext/2016048053/Variable.o \
	${OBJECTDIR}/_ext/1413408311/ZElevationGrid.o \
	${OBJECTDIR}/_ext/1413408311/ZSphere.o \
	${OBJECTDIR}/_ext/1413408311/ZShape.o \
	${OBJECTDIR}/_ext/783283226/ControlVarWindow.o \
	${OBJECTDIR}/_ext/783283226/Line.o \
	${OBJECTDIR}/_ext/783283226/PlotBaseWindow.o \
	${OBJECTDIR}/_ext/2016048053/LogVariableBase.o \
	${OBJECTDIR}/_ext/1413408311/Vector3D.o \
	${OBJECTDIR}/_ext/1413408311/ZIndexedFaceSet.o \
	${OBJECTDIR}/_ext/1413408311/ZBox.o \
	${OBJECTDIR}/_ext/1413408311/ZCylinder.o \
	${OBJECTDIR}/_ext/1413408311/ZDirectionalLight.o \
	${OBJECTDIR}/_ext/783283226/GlPlotXYWindow.o \
	${OBJECTDIR}/_ext/2016048053/LogVariable.o \
	${OBJECTDIR}/_ext/783283226/ZButton.o \
	${OBJECTDIR}/_ext/2016048053/LogVariableGUI.o \
	${OBJECTDIR}/_ext/1413408311/ZVrmlNode.o \
	${OBJECTDIR}/_ext/1413408311/ZViewpoint.o \
	${OBJECTDIR}/_ext/1413408311/ZColorNode.o \
	${OBJECTDIR}/_ext/783283226/logVarWindow.o \
	${OBJECTDIR}/_ext/1413408311/ZNotSupportedNode.o \
	${OBJECTDIR}/_ext/1413408311/utils.o \
	${OBJECTDIR}/_ext/233333389/ZenomGUI.o \
	${OBJECTDIR}/_ext/783283226/PlotXYWindow.o \
	${OBJECTDIR}/_ext/783283226/GlPlotWindow.o \
	${OBJECTDIR}/_ext/1413408311/ZTransform.o \
	${OBJECTDIR}/_ext/1413408311/ZNavigationInfo.o \
	${OBJECTDIR}/_ext/783283226/WatchWindow.o \
	${OBJECTDIR}/_ext/783283226/zenom.o \
	${OBJECTDIR}/_ext/783283226/GlPlotWindowBase.o \
	${OBJECTDIR}/_ext/1413408311/ZAppearance.o \
	${OBJECTDIR}/_ext/783283226/messageHandler.o \
	${OBJECTDIR}/_ext/783283226/PlotSelectedItem.o \
	${OBJECTDIR}/_ext/783283226/LineBase.o \
	${OBJECTDIR}/_ext/783283226/PlotRectangle.o \
	${OBJECTDIR}/_ext/1413408311/ZMaterial.o \
	${OBJECTDIR}/_ext/1413408311/ZGroup.o \
	${OBJECTDIR}/_ext/783283226/WatchWindowUpdater.o \
	${OBJECTDIR}/_ext/2016048053/Config.o \
	${OBJECTDIR}/_ext/1413408311/ZGeometry.o \
	${OBJECTDIR}/_ext/783283226/PlotWindow.o \
	${OBJECTDIR}/_ext/1413408311/ZCone.o \
	${OBJECTDIR}/_ext/783283226/SevenSegment.o \
	${OBJECTDIR}/_ext/1413408311/ZPointSet.o \
	${OBJECTDIR}/_ext/1413408311/Camera.o \
	${OBJECTDIR}/_ext/1413408311/VectorRotater.o \
	${OBJECTDIR}/_ext/1413408311/ZIndexedLineSet.o \
	${OBJECTDIR}/_ext/783283226/LineXY.o \
	${OBJECTDIR}/_ext/2016048053/ControlVariable.o \
	${OBJECTDIR}/_ext/783283226/TextDisplayWidget.o \
	${OBJECTDIR}/_ext/1413408311/ZSpotLight.o \
	${OBJECTDIR}/_ext/1413408311/Scene.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-DBOOST_SPIRIT_THREADSAFE -DBOOST_SPIRIT_CLOSURE_LIMIT=6 -DPHOENIX_LIMIT=6
CXXFLAGS=-DBOOST_SPIRIT_THREADSAFE -DBOOST_SPIRIT_CLOSURE_LIMIT=6 -DPHOENIX_LIMIT=6

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/usr/local/Zenom/lib -L/usr/xenomai/lib -L../../Desktop/fltk-2.0.x-r6970/lib -L../Zenom\ \(copy\)/src/XenoTools -lXenoTools -lfltk2 -lfltk2_gl -lfltk2_glut -lnative -lpthread_rt -lrtdk

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-Debug.mk dist/Debug/GNU-Linux-x86/guiconfig

dist/Debug/GNU-Linux-x86/guiconfig: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-Linux-x86
	${LINK.cc} -lX11 -lXi -lXinerama -lXcursor -lXft -lXext -lglut -lopenvrml -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/guiconfig ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/1413408311/ZCoordinate.o: ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZCoordinate.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1413408311
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1413408311/ZCoordinate.o ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZCoordinate.cpp

${OBJECTDIR}/_ext/1413408311/ZNormal.o: ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZNormal.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1413408311
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1413408311/ZNormal.o ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZNormal.cpp

${OBJECTDIR}/_ext/783283226/WatchSelectWindow.o: ../Zenom\ \(copy\)/src/ZenomGUI/WatchSelectWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/783283226
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/783283226/WatchSelectWindow.o ../Zenom\ \(copy\)/src/ZenomGUI/WatchSelectWindow.cpp

${OBJECTDIR}/_ext/1413408311/SceneWindow.o: ../Zenom\ \(copy\)/src/ZenomGUI/Scene/SceneWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1413408311
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1413408311/SceneWindow.o ../Zenom\ \(copy\)/src/ZenomGUI/Scene/SceneWindow.cpp

${OBJECTDIR}/_ext/2016048053/guiMessenger.o: ../Zenom\ \(copy\)/src/Common/guiMessenger.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2016048053
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2016048053/guiMessenger.o ../Zenom\ \(copy\)/src/Common/guiMessenger.cpp

${OBJECTDIR}/_ext/1413408311/ZPointLight.o: ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZPointLight.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1413408311
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1413408311/ZPointLight.o ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZPointLight.cpp

${OBJECTDIR}/_ext/2016048053/Variable.o: ../Zenom\ \(copy\)/src/Common/Variable.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2016048053
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2016048053/Variable.o ../Zenom\ \(copy\)/src/Common/Variable.cpp

${OBJECTDIR}/_ext/1413408311/ZElevationGrid.o: ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZElevationGrid.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1413408311
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1413408311/ZElevationGrid.o ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZElevationGrid.cpp

${OBJECTDIR}/_ext/1413408311/ZSphere.o: ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZSphere.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1413408311
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1413408311/ZSphere.o ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZSphere.cpp

${OBJECTDIR}/_ext/1413408311/ZShape.o: ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1413408311
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1413408311/ZShape.o ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZShape.cpp

${OBJECTDIR}/_ext/783283226/ControlVarWindow.o: ../Zenom\ \(copy\)/src/ZenomGUI/ControlVarWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/783283226
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/783283226/ControlVarWindow.o ../Zenom\ \(copy\)/src/ZenomGUI/ControlVarWindow.cpp

${OBJECTDIR}/_ext/783283226/Line.o: ../Zenom\ \(copy\)/src/ZenomGUI/Line.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/783283226
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/783283226/Line.o ../Zenom\ \(copy\)/src/ZenomGUI/Line.cpp

${OBJECTDIR}/_ext/783283226/PlotBaseWindow.o: ../Zenom\ \(copy\)/src/ZenomGUI/PlotBaseWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/783283226
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/783283226/PlotBaseWindow.o ../Zenom\ \(copy\)/src/ZenomGUI/PlotBaseWindow.cpp

${OBJECTDIR}/_ext/2016048053/LogVariableBase.o: ../Zenom\ \(copy\)/src/Common/LogVariableBase.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2016048053
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2016048053/LogVariableBase.o ../Zenom\ \(copy\)/src/Common/LogVariableBase.cpp

${OBJECTDIR}/_ext/1413408311/Vector3D.o: ../Zenom\ \(copy\)/src/ZenomGUI/Scene/Vector3D.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1413408311
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1413408311/Vector3D.o ../Zenom\ \(copy\)/src/ZenomGUI/Scene/Vector3D.cpp

${OBJECTDIR}/_ext/1413408311/ZIndexedFaceSet.o: ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZIndexedFaceSet.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1413408311
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1413408311/ZIndexedFaceSet.o ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZIndexedFaceSet.cpp

${OBJECTDIR}/_ext/1413408311/ZBox.o: ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1413408311
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1413408311/ZBox.o ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZBox.cpp

${OBJECTDIR}/_ext/1413408311/ZCylinder.o: ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZCylinder.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1413408311
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1413408311/ZCylinder.o ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZCylinder.cpp

${OBJECTDIR}/_ext/1413408311/ZDirectionalLight.o: ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZDirectionalLight.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1413408311
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1413408311/ZDirectionalLight.o ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZDirectionalLight.cpp

${OBJECTDIR}/_ext/783283226/GlPlotXYWindow.o: ../Zenom\ \(copy\)/src/ZenomGUI/GlPlotXYWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/783283226
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/783283226/GlPlotXYWindow.o ../Zenom\ \(copy\)/src/ZenomGUI/GlPlotXYWindow.cpp

${OBJECTDIR}/_ext/2016048053/LogVariable.o: ../Zenom\ \(copy\)/src/Common/LogVariable.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2016048053
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2016048053/LogVariable.o ../Zenom\ \(copy\)/src/Common/LogVariable.cpp

${OBJECTDIR}/_ext/783283226/ZButton.o: ../Zenom\ \(copy\)/src/ZenomGUI/ZButton.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/783283226
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/783283226/ZButton.o ../Zenom\ \(copy\)/src/ZenomGUI/ZButton.cpp

${OBJECTDIR}/_ext/2016048053/LogVariableGUI.o: ../Zenom\ \(copy\)/src/Common/LogVariableGUI.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2016048053
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2016048053/LogVariableGUI.o ../Zenom\ \(copy\)/src/Common/LogVariableGUI.cpp

${OBJECTDIR}/_ext/1413408311/ZVrmlNode.o: ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZVrmlNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1413408311
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1413408311/ZVrmlNode.o ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZVrmlNode.cpp

${OBJECTDIR}/_ext/1413408311/ZViewpoint.o: ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZViewpoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1413408311
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1413408311/ZViewpoint.o ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZViewpoint.cpp

${OBJECTDIR}/_ext/1413408311/ZColorNode.o: ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZColorNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1413408311
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1413408311/ZColorNode.o ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZColorNode.cpp

${OBJECTDIR}/_ext/783283226/logVarWindow.o: ../Zenom\ \(copy\)/src/ZenomGUI/logVarWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/783283226
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/783283226/logVarWindow.o ../Zenom\ \(copy\)/src/ZenomGUI/logVarWindow.cpp

${OBJECTDIR}/_ext/1413408311/ZNotSupportedNode.o: ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZNotSupportedNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1413408311
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1413408311/ZNotSupportedNode.o ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZNotSupportedNode.cpp

${OBJECTDIR}/_ext/1413408311/utils.o: ../Zenom\ \(copy\)/src/ZenomGUI/Scene/utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1413408311
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1413408311/utils.o ../Zenom\ \(copy\)/src/ZenomGUI/Scene/utils.cpp

${OBJECTDIR}/_ext/233333389/ZenomGUI.o: ../Zenom\ \(copy\)/src/ZenomGUIBin/ZenomGUI.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/233333389
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/233333389/ZenomGUI.o ../Zenom\ \(copy\)/src/ZenomGUIBin/ZenomGUI.cpp

${OBJECTDIR}/_ext/783283226/PlotXYWindow.o: ../Zenom\ \(copy\)/src/ZenomGUI/PlotXYWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/783283226
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/783283226/PlotXYWindow.o ../Zenom\ \(copy\)/src/ZenomGUI/PlotXYWindow.cpp

${OBJECTDIR}/_ext/783283226/GlPlotWindow.o: ../Zenom\ \(copy\)/src/ZenomGUI/GlPlotWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/783283226
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/783283226/GlPlotWindow.o ../Zenom\ \(copy\)/src/ZenomGUI/GlPlotWindow.cpp

${OBJECTDIR}/_ext/1413408311/ZTransform.o: ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZTransform.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1413408311
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1413408311/ZTransform.o ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZTransform.cpp

${OBJECTDIR}/_ext/1413408311/ZNavigationInfo.o: ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZNavigationInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1413408311
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1413408311/ZNavigationInfo.o ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZNavigationInfo.cpp

${OBJECTDIR}/_ext/783283226/WatchWindow.o: ../Zenom\ \(copy\)/src/ZenomGUI/WatchWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/783283226
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/783283226/WatchWindow.o ../Zenom\ \(copy\)/src/ZenomGUI/WatchWindow.cpp

${OBJECTDIR}/_ext/783283226/zenom.o: ../Zenom\ \(copy\)/src/ZenomGUI/zenom.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/783283226
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/783283226/zenom.o ../Zenom\ \(copy\)/src/ZenomGUI/zenom.cpp

${OBJECTDIR}/_ext/783283226/GlPlotWindowBase.o: ../Zenom\ \(copy\)/src/ZenomGUI/GlPlotWindowBase.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/783283226
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/783283226/GlPlotWindowBase.o ../Zenom\ \(copy\)/src/ZenomGUI/GlPlotWindowBase.cpp

${OBJECTDIR}/_ext/1413408311/ZAppearance.o: ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZAppearance.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1413408311
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1413408311/ZAppearance.o ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZAppearance.cpp

${OBJECTDIR}/_ext/783283226/messageHandler.o: ../Zenom\ \(copy\)/src/ZenomGUI/messageHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/783283226
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/783283226/messageHandler.o ../Zenom\ \(copy\)/src/ZenomGUI/messageHandler.cpp

${OBJECTDIR}/_ext/783283226/PlotSelectedItem.o: ../Zenom\ \(copy\)/src/ZenomGUI/PlotSelectedItem.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/783283226
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/783283226/PlotSelectedItem.o ../Zenom\ \(copy\)/src/ZenomGUI/PlotSelectedItem.cpp

${OBJECTDIR}/_ext/783283226/LineBase.o: ../Zenom\ \(copy\)/src/ZenomGUI/LineBase.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/783283226
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/783283226/LineBase.o ../Zenom\ \(copy\)/src/ZenomGUI/LineBase.cpp

${OBJECTDIR}/_ext/783283226/PlotRectangle.o: ../Zenom\ \(copy\)/src/ZenomGUI/PlotRectangle.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/783283226
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/783283226/PlotRectangle.o ../Zenom\ \(copy\)/src/ZenomGUI/PlotRectangle.cpp

${OBJECTDIR}/_ext/1413408311/ZMaterial.o: ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZMaterial.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1413408311
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1413408311/ZMaterial.o ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZMaterial.cpp

${OBJECTDIR}/_ext/1413408311/ZGroup.o: ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZGroup.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1413408311
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1413408311/ZGroup.o ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZGroup.cpp

${OBJECTDIR}/_ext/783283226/WatchWindowUpdater.o: ../Zenom\ \(copy\)/src/ZenomGUI/WatchWindowUpdater.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/783283226
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/783283226/WatchWindowUpdater.o ../Zenom\ \(copy\)/src/ZenomGUI/WatchWindowUpdater.cpp

${OBJECTDIR}/_ext/2016048053/Config.o: ../Zenom\ \(copy\)/src/Common/Config.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2016048053
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2016048053/Config.o ../Zenom\ \(copy\)/src/Common/Config.cpp

${OBJECTDIR}/_ext/1413408311/ZGeometry.o: ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZGeometry.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1413408311
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1413408311/ZGeometry.o ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZGeometry.cpp

${OBJECTDIR}/_ext/783283226/PlotWindow.o: ../Zenom\ \(copy\)/src/ZenomGUI/PlotWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/783283226
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/783283226/PlotWindow.o ../Zenom\ \(copy\)/src/ZenomGUI/PlotWindow.cpp

${OBJECTDIR}/_ext/1413408311/ZCone.o: ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZCone.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1413408311
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1413408311/ZCone.o ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZCone.cpp

${OBJECTDIR}/_ext/783283226/SevenSegment.o: ../Zenom\ \(copy\)/src/ZenomGUI/SevenSegment.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/783283226
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/783283226/SevenSegment.o ../Zenom\ \(copy\)/src/ZenomGUI/SevenSegment.cpp

${OBJECTDIR}/_ext/1413408311/ZPointSet.o: ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZPointSet.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1413408311
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1413408311/ZPointSet.o ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZPointSet.cpp

${OBJECTDIR}/_ext/1413408311/Camera.o: ../Zenom\ \(copy\)/src/ZenomGUI/Scene/Camera.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1413408311
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1413408311/Camera.o ../Zenom\ \(copy\)/src/ZenomGUI/Scene/Camera.cpp

${OBJECTDIR}/_ext/1413408311/VectorRotater.o: ../Zenom\ \(copy\)/src/ZenomGUI/Scene/VectorRotater.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1413408311
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1413408311/VectorRotater.o ../Zenom\ \(copy\)/src/ZenomGUI/Scene/VectorRotater.cpp

${OBJECTDIR}/_ext/1413408311/ZIndexedLineSet.o: ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZIndexedLineSet.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1413408311
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1413408311/ZIndexedLineSet.o ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZIndexedLineSet.cpp

${OBJECTDIR}/_ext/783283226/LineXY.o: ../Zenom\ \(copy\)/src/ZenomGUI/LineXY.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/783283226
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/783283226/LineXY.o ../Zenom\ \(copy\)/src/ZenomGUI/LineXY.cpp

${OBJECTDIR}/_ext/2016048053/ControlVariable.o: ../Zenom\ \(copy\)/src/Common/ControlVariable.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2016048053
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2016048053/ControlVariable.o ../Zenom\ \(copy\)/src/Common/ControlVariable.cpp

${OBJECTDIR}/_ext/783283226/TextDisplayWidget.o: ../Zenom\ \(copy\)/src/ZenomGUI/TextDisplayWidget.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/783283226
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/783283226/TextDisplayWidget.o ../Zenom\ \(copy\)/src/ZenomGUI/TextDisplayWidget.cpp

${OBJECTDIR}/_ext/1413408311/ZSpotLight.o: ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZSpotLight.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1413408311
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1413408311/ZSpotLight.o ../Zenom\ \(copy\)/src/ZenomGUI/Scene/ZSpotLight.cpp

${OBJECTDIR}/_ext/1413408311/Scene.o: ../Zenom\ \(copy\)/src/ZenomGUI/Scene/Scene.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1413408311
	${RM} $@.d
	$(COMPILE.cc) -g -I../Zenom\ \(copy\)/include/Common -I../Zenom\ \(copy\)/include/QMath -I../Zenom\ \(copy\)/include/ZenomGUI -I../Zenom\ \(copy\)/include/XenoTools/native -I../Zenom\ \(copy\)/include/XenoTools/posix -I/usr/xenomai/include -I../Zenom\ \(copy\)/include/ZenomGUI/Scene -I../Zenom\ \(copy\)/src/ZenomGUI/Scene -I/usr/include/openvrml -I../fltk-2.0.x-r6970 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1413408311/Scene.o ../Zenom\ \(copy\)/src/ZenomGUI/Scene/Scene.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-Linux-x86/guiconfig

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
