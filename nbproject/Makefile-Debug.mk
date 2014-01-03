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
CC=clang
CCC=clang++
CXX=clang++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=Clang-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/display/Window.o \
	${OBJECTDIR}/src/graphics/Pixel.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/positioning/Particle.o \
	${OBJECTDIR}/src/positioning/Point.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=$(sdl2-config --cflags --libs) -O3
CXXFLAGS=$(sdl2-config --cflags --libs) -O3

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/particlesystem

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/particlesystem: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/particlesystem ${OBJECTFILES} ${LDLIBSOPTIONS} -lSDL2

${OBJECTDIR}/src/display/Window.o: src/display/Window.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/display
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/display/Window.o src/display/Window.cpp

${OBJECTDIR}/src/graphics/Pixel.o: src/graphics/Pixel.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/graphics
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/graphics/Pixel.o src/graphics/Pixel.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/positioning/Particle.o: src/positioning/Particle.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/positioning
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/positioning/Particle.o src/positioning/Particle.cpp

${OBJECTDIR}/src/positioning/Point.o: src/positioning/Point.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/positioning
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/positioning/Point.o src/positioning/Point.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/particlesystem

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
