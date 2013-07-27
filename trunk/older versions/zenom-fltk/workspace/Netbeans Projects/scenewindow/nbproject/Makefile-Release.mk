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
CND_CONF=Release
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/LogVariableGUI.o \
	${OBJECTDIR}/ZBox.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/Camera.o \
	${OBJECTDIR}/ZGeometry.o \
	${OBJECTDIR}/Scene.o \
	${OBJECTDIR}/ZNotSupportedNode.o \
	${OBJECTDIR}/ZButton.o \
	${OBJECTDIR}/ZMaterial.o \
	${OBJECTDIR}/Vector3D.o \
	${OBJECTDIR}/ZDirectionalLight.o \
	${OBJECTDIR}/ZVrmlNode.o \
	${OBJECTDIR}/ZIndexedLineSet.o \
	${OBJECTDIR}/SceneWindow.o \
	${OBJECTDIR}/ZViewpoint.o \
	${OBJECTDIR}/ZCoordinate.o \
	${OBJECTDIR}/VectorRotater.o \
	${OBJECTDIR}/ZColorNode.o \
	${OBJECTDIR}/Variable.o \
	${OBJECTDIR}/ZPointSet.o \
	${OBJECTDIR}/ZSpotLight.o \
	${OBJECTDIR}/ZSphere.o \
	${OBJECTDIR}/ZCone.o \
	${OBJECTDIR}/ZAppearance.o \
	${OBJECTDIR}/ZCylinder.o \
	${OBJECTDIR}/utils.o \
	${OBJECTDIR}/LogVariableBase.o \
	${OBJECTDIR}/ZIndexedFaceSet.o \
	${OBJECTDIR}/ZNormal.o \
	${OBJECTDIR}/ZShape.o \
	${OBJECTDIR}/ZPointLight.o \
	${OBJECTDIR}/ZNavigationInfo.o \
	${OBJECTDIR}/LogVariable.o \
	${OBJECTDIR}/ZGroup.o \
	${OBJECTDIR}/ZTransform.o \
	${OBJECTDIR}/ZElevationGrid.o


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
LDLIBSOPTIONS=-L/usr/lib64/ -L/usr/xenomai/lib -L/home/CuneyT/Desktop/son/husnuk/Zenom\ \(copy\)/include/XenoTools -lopenvrml -lfltk2 -lfltk2_gl -lfltk2_glut -lfltk2_images -lpthread_rt -lnative -lXenoTools

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-Release.mk dist/Release/GNU-Linux-x86/scenewindow

dist/Release/GNU-Linux-x86/scenewindow: ${OBJECTFILES}
	${MKDIR} -p dist/Release/GNU-Linux-x86
	${LINK.cc} -lX11 -lXi -lXinerama -lXcursor -lXft -lXext -lglut -lopenvrml -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/scenewindow ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/LogVariableGUI.o: LogVariableGUI.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/LogVariableGUI.o LogVariableGUI.cpp

${OBJECTDIR}/ZBox.o: ZBox.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/ZBox.o ZBox.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/Camera.o: Camera.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/Camera.o Camera.cpp

${OBJECTDIR}/ZGeometry.o: ZGeometry.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/ZGeometry.o ZGeometry.cpp

${OBJECTDIR}/Scene.o: Scene.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/Scene.o Scene.cpp

${OBJECTDIR}/ZNotSupportedNode.o: ZNotSupportedNode.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/ZNotSupportedNode.o ZNotSupportedNode.cpp

${OBJECTDIR}/ZButton.o: ZButton.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/ZButton.o ZButton.cpp

${OBJECTDIR}/ZMaterial.o: ZMaterial.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/ZMaterial.o ZMaterial.cpp

${OBJECTDIR}/Vector3D.o: Vector3D.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/Vector3D.o Vector3D.cpp

${OBJECTDIR}/ZDirectionalLight.o: ZDirectionalLight.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/ZDirectionalLight.o ZDirectionalLight.cpp

${OBJECTDIR}/ZVrmlNode.o: ZVrmlNode.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/ZVrmlNode.o ZVrmlNode.cpp

${OBJECTDIR}/ZIndexedLineSet.o: ZIndexedLineSet.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/ZIndexedLineSet.o ZIndexedLineSet.cpp

${OBJECTDIR}/SceneWindow.o: SceneWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/SceneWindow.o SceneWindow.cpp

${OBJECTDIR}/ZViewpoint.o: ZViewpoint.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/ZViewpoint.o ZViewpoint.cpp

${OBJECTDIR}/ZCoordinate.o: ZCoordinate.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/ZCoordinate.o ZCoordinate.cpp

${OBJECTDIR}/VectorRotater.o: VectorRotater.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/VectorRotater.o VectorRotater.cpp

${OBJECTDIR}/ZColorNode.o: ZColorNode.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/ZColorNode.o ZColorNode.cpp

${OBJECTDIR}/Variable.o: Variable.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/Variable.o Variable.cpp

${OBJECTDIR}/ZPointSet.o: ZPointSet.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/ZPointSet.o ZPointSet.cpp

${OBJECTDIR}/ZSpotLight.o: ZSpotLight.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/ZSpotLight.o ZSpotLight.cpp

${OBJECTDIR}/ZSphere.o: ZSphere.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/ZSphere.o ZSphere.cpp

${OBJECTDIR}/ZCone.o: ZCone.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/ZCone.o ZCone.cpp

${OBJECTDIR}/ZAppearance.o: ZAppearance.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/ZAppearance.o ZAppearance.cpp

${OBJECTDIR}/ZCylinder.o: ZCylinder.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/ZCylinder.o ZCylinder.cpp

${OBJECTDIR}/utils.o: utils.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/utils.o utils.cpp

${OBJECTDIR}/LogVariableBase.o: LogVariableBase.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/LogVariableBase.o LogVariableBase.cpp

${OBJECTDIR}/ZIndexedFaceSet.o: ZIndexedFaceSet.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/ZIndexedFaceSet.o ZIndexedFaceSet.cpp

${OBJECTDIR}/ZNormal.o: ZNormal.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/ZNormal.o ZNormal.cpp

${OBJECTDIR}/ZShape.o: ZShape.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/ZShape.o ZShape.cpp

${OBJECTDIR}/ZPointLight.o: ZPointLight.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/ZPointLight.o ZPointLight.cpp

${OBJECTDIR}/ZNavigationInfo.o: ZNavigationInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/ZNavigationInfo.o ZNavigationInfo.cpp

${OBJECTDIR}/LogVariable.o: LogVariable.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/LogVariable.o LogVariable.cpp

${OBJECTDIR}/ZGroup.o: ZGroup.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/ZGroup.o ZGroup.cpp

${OBJECTDIR}/ZTransform.o: ZTransform.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/ZTransform.o ZTransform.cpp

${OBJECTDIR}/ZElevationGrid.o: ZElevationGrid.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/usr/include/openvrml/ -I../../Desktop/fltk-2.0.x-r6970 -I/usr/xenomai/include -I../../Desktop/Zenom/include/XenoTools/native -I../../Desktop/Zenom/include/XenoTools/posix -MMD -MP -MF $@.d -o ${OBJECTDIR}/ZElevationGrid.o ZElevationGrid.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release
	${RM} dist/Release/GNU-Linux-x86/scenewindow

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
