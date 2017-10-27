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
CCC=c++
CXX=c++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
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
	${OBJECTDIR}/ArbreAbstrait.o \
	${OBJECTDIR}/Interpreteur.o \
	${OBJECTDIR}/Lecteur.o \
	${OBJECTDIR}/Symbole.o \
	${OBJECTDIR}/SymboleValue.o \
	${OBJECTDIR}/TableSymboles.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/progEcrire.o \
	${OBJECTDIR}/progLire.o \
	${OBJECTDIR}/progPour.o \
	${OBJECTDIR}/progRepeter.o \
	${OBJECTDIR}/progSelon.o \
	${OBJECTDIR}/progSi.o \
	${OBJECTDIR}/progTantQue.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/tests/testSiRiche.o \
	${TESTDIR}/tests/testSiRicheRunner.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/projetc-

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/projetc-: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/projetc- ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/ArbreAbstrait.o: ArbreAbstrait.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ArbreAbstrait.o ArbreAbstrait.cpp

${OBJECTDIR}/Interpreteur.o: Interpreteur.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Interpreteur.o Interpreteur.cpp

${OBJECTDIR}/Lecteur.o: Lecteur.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Lecteur.o Lecteur.cpp

${OBJECTDIR}/Symbole.o: Symbole.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Symbole.o Symbole.cpp

${OBJECTDIR}/SymboleValue.o: SymboleValue.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SymboleValue.o SymboleValue.cpp

${OBJECTDIR}/TableSymboles.o: TableSymboles.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TableSymboles.o TableSymboles.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/progEcrire.o: progEcrire.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/progEcrire.o progEcrire.cpp

${OBJECTDIR}/progLire.o: progLire.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/progLire.o progLire.cpp

${OBJECTDIR}/progPour.o: progPour.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/progPour.o progPour.cpp

${OBJECTDIR}/progRepeter.o: progRepeter.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/progRepeter.o progRepeter.cpp

${OBJECTDIR}/progSelon.o: progSelon.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/progSelon.o progSelon.cpp

${OBJECTDIR}/progSi.o: progSi.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/progSi.o progSi.cpp

${OBJECTDIR}/progTantQue.o: progTantQue.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/progTantQue.o progTantQue.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/testSiRiche.o ${TESTDIR}/tests/testSiRicheRunner.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS}   `cppunit-config --libs`   


${TESTDIR}/tests/testSiRiche.o: tests/testSiRiche.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/testSiRiche.o tests/testSiRiche.cpp


${TESTDIR}/tests/testSiRicheRunner.o: tests/testSiRicheRunner.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/testSiRicheRunner.o tests/testSiRicheRunner.cpp


${OBJECTDIR}/ArbreAbstrait_nomain.o: ${OBJECTDIR}/ArbreAbstrait.o ArbreAbstrait.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ArbreAbstrait.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ArbreAbstrait_nomain.o ArbreAbstrait.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ArbreAbstrait.o ${OBJECTDIR}/ArbreAbstrait_nomain.o;\
	fi

${OBJECTDIR}/Interpreteur_nomain.o: ${OBJECTDIR}/Interpreteur.o Interpreteur.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Interpreteur.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Interpreteur_nomain.o Interpreteur.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Interpreteur.o ${OBJECTDIR}/Interpreteur_nomain.o;\
	fi

${OBJECTDIR}/Lecteur_nomain.o: ${OBJECTDIR}/Lecteur.o Lecteur.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Lecteur.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Lecteur_nomain.o Lecteur.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Lecteur.o ${OBJECTDIR}/Lecteur_nomain.o;\
	fi

${OBJECTDIR}/Symbole_nomain.o: ${OBJECTDIR}/Symbole.o Symbole.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Symbole.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Symbole_nomain.o Symbole.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Symbole.o ${OBJECTDIR}/Symbole_nomain.o;\
	fi

${OBJECTDIR}/SymboleValue_nomain.o: ${OBJECTDIR}/SymboleValue.o SymboleValue.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/SymboleValue.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SymboleValue_nomain.o SymboleValue.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/SymboleValue.o ${OBJECTDIR}/SymboleValue_nomain.o;\
	fi

${OBJECTDIR}/TableSymboles_nomain.o: ${OBJECTDIR}/TableSymboles.o TableSymboles.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/TableSymboles.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TableSymboles_nomain.o TableSymboles.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/TableSymboles.o ${OBJECTDIR}/TableSymboles_nomain.o;\
	fi

${OBJECTDIR}/main_nomain.o: ${OBJECTDIR}/main.o main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main_nomain.o main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/main.o ${OBJECTDIR}/main_nomain.o;\
	fi

${OBJECTDIR}/progEcrire_nomain.o: ${OBJECTDIR}/progEcrire.o progEcrire.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/progEcrire.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/progEcrire_nomain.o progEcrire.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/progEcrire.o ${OBJECTDIR}/progEcrire_nomain.o;\
	fi

${OBJECTDIR}/progLire_nomain.o: ${OBJECTDIR}/progLire.o progLire.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/progLire.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/progLire_nomain.o progLire.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/progLire.o ${OBJECTDIR}/progLire_nomain.o;\
	fi

${OBJECTDIR}/progPour_nomain.o: ${OBJECTDIR}/progPour.o progPour.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/progPour.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/progPour_nomain.o progPour.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/progPour.o ${OBJECTDIR}/progPour_nomain.o;\
	fi

${OBJECTDIR}/progRepeter_nomain.o: ${OBJECTDIR}/progRepeter.o progRepeter.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/progRepeter.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/progRepeter_nomain.o progRepeter.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/progRepeter.o ${OBJECTDIR}/progRepeter_nomain.o;\
	fi

${OBJECTDIR}/progSelon_nomain.o: ${OBJECTDIR}/progSelon.o progSelon.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/progSelon.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/progSelon_nomain.o progSelon.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/progSelon.o ${OBJECTDIR}/progSelon_nomain.o;\
	fi

${OBJECTDIR}/progSi_nomain.o: ${OBJECTDIR}/progSi.o progSi.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/progSi.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/progSi_nomain.o progSi.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/progSi.o ${OBJECTDIR}/progSi_nomain.o;\
	fi

${OBJECTDIR}/progTantQue_nomain.o: ${OBJECTDIR}/progTantQue.o progTantQue.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/progTantQue.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/progTantQue_nomain.o progTantQue.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/progTantQue.o ${OBJECTDIR}/progTantQue_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
