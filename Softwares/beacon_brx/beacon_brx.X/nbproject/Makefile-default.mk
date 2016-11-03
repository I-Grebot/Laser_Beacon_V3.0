#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/beacon_brx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/beacon_brx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1360937237/beacon_brx.o ${OBJECTDIR}/_ext/1360937237/oscillator.o ${OBJECTDIR}/_ext/1502898876/cc2500.o ${OBJECTDIR}/_ext/1360937237/photo_detect.o ${OBJECTDIR}/_ext/1360937237/led.o ${OBJECTDIR}/_ext/911561563/beacon_com.o ${OBJECTDIR}/_ext/1360937237/distance_matcher.o ${OBJECTDIR}/_ext/1360937237/distance_lut.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1360937237/beacon_brx.o.d ${OBJECTDIR}/_ext/1360937237/oscillator.o.d ${OBJECTDIR}/_ext/1502898876/cc2500.o.d ${OBJECTDIR}/_ext/1360937237/photo_detect.o.d ${OBJECTDIR}/_ext/1360937237/led.o.d ${OBJECTDIR}/_ext/911561563/beacon_com.o.d ${OBJECTDIR}/_ext/1360937237/distance_matcher.o.d ${OBJECTDIR}/_ext/1360937237/distance_lut.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1360937237/beacon_brx.o ${OBJECTDIR}/_ext/1360937237/oscillator.o ${OBJECTDIR}/_ext/1502898876/cc2500.o ${OBJECTDIR}/_ext/1360937237/photo_detect.o ${OBJECTDIR}/_ext/1360937237/led.o ${OBJECTDIR}/_ext/911561563/beacon_com.o ${OBJECTDIR}/_ext/1360937237/distance_matcher.o ${OBJECTDIR}/_ext/1360937237/distance_lut.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/beacon_brx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ128MC804
MP_LINKER_FILE_OPTION=,-Tp33FJ128MC804.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1360937237/beacon_brx.o: ../src/beacon_brx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/beacon_brx.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/beacon_brx.o.ok ${OBJECTDIR}/_ext/1360937237/beacon_brx.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/beacon_brx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/beacon_brx.o.d" -o ${OBJECTDIR}/_ext/1360937237/beacon_brx.o ../src/beacon_brx.c    
	
${OBJECTDIR}/_ext/1360937237/oscillator.o: ../src/oscillator.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/oscillator.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/oscillator.o.ok ${OBJECTDIR}/_ext/1360937237/oscillator.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/oscillator.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/oscillator.o.d" -o ${OBJECTDIR}/_ext/1360937237/oscillator.o ../src/oscillator.c    
	
${OBJECTDIR}/_ext/1502898876/cc2500.o: ../../common/cc2500/src/cc2500.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1502898876 
	@${RM} ${OBJECTDIR}/_ext/1502898876/cc2500.o.d 
	@${RM} ${OBJECTDIR}/_ext/1502898876/cc2500.o.ok ${OBJECTDIR}/_ext/1502898876/cc2500.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1502898876/cc2500.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -MMD -MF "${OBJECTDIR}/_ext/1502898876/cc2500.o.d" -o ${OBJECTDIR}/_ext/1502898876/cc2500.o ../../common/cc2500/src/cc2500.c    
	
${OBJECTDIR}/_ext/1360937237/photo_detect.o: ../src/photo_detect.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/photo_detect.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/photo_detect.o.ok ${OBJECTDIR}/_ext/1360937237/photo_detect.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/photo_detect.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/photo_detect.o.d" -o ${OBJECTDIR}/_ext/1360937237/photo_detect.o ../src/photo_detect.c    
	
${OBJECTDIR}/_ext/1360937237/led.o: ../src/led.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/led.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/led.o.ok ${OBJECTDIR}/_ext/1360937237/led.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/led.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/led.o.d" -o ${OBJECTDIR}/_ext/1360937237/led.o ../src/led.c    
	
${OBJECTDIR}/_ext/911561563/beacon_com.o: ../../common/beacon_system/src/beacon_com.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/911561563 
	@${RM} ${OBJECTDIR}/_ext/911561563/beacon_com.o.d 
	@${RM} ${OBJECTDIR}/_ext/911561563/beacon_com.o.ok ${OBJECTDIR}/_ext/911561563/beacon_com.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/911561563/beacon_com.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -MMD -MF "${OBJECTDIR}/_ext/911561563/beacon_com.o.d" -o ${OBJECTDIR}/_ext/911561563/beacon_com.o ../../common/beacon_system/src/beacon_com.c    
	
${OBJECTDIR}/_ext/1360937237/distance_matcher.o: ../src/distance_matcher.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/distance_matcher.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/distance_matcher.o.ok ${OBJECTDIR}/_ext/1360937237/distance_matcher.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/distance_matcher.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/distance_matcher.o.d" -o ${OBJECTDIR}/_ext/1360937237/distance_matcher.o ../src/distance_matcher.c    
	
${OBJECTDIR}/_ext/1360937237/distance_lut.o: ../src/distance_lut.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/distance_lut.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/distance_lut.o.ok ${OBJECTDIR}/_ext/1360937237/distance_lut.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/distance_lut.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/distance_lut.o.d" -o ${OBJECTDIR}/_ext/1360937237/distance_lut.o ../src/distance_lut.c    
	
else
${OBJECTDIR}/_ext/1360937237/beacon_brx.o: ../src/beacon_brx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/beacon_brx.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/beacon_brx.o.ok ${OBJECTDIR}/_ext/1360937237/beacon_brx.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/beacon_brx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/beacon_brx.o.d" -o ${OBJECTDIR}/_ext/1360937237/beacon_brx.o ../src/beacon_brx.c    
	
${OBJECTDIR}/_ext/1360937237/oscillator.o: ../src/oscillator.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/oscillator.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/oscillator.o.ok ${OBJECTDIR}/_ext/1360937237/oscillator.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/oscillator.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/oscillator.o.d" -o ${OBJECTDIR}/_ext/1360937237/oscillator.o ../src/oscillator.c    
	
${OBJECTDIR}/_ext/1502898876/cc2500.o: ../../common/cc2500/src/cc2500.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1502898876 
	@${RM} ${OBJECTDIR}/_ext/1502898876/cc2500.o.d 
	@${RM} ${OBJECTDIR}/_ext/1502898876/cc2500.o.ok ${OBJECTDIR}/_ext/1502898876/cc2500.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1502898876/cc2500.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -MMD -MF "${OBJECTDIR}/_ext/1502898876/cc2500.o.d" -o ${OBJECTDIR}/_ext/1502898876/cc2500.o ../../common/cc2500/src/cc2500.c    
	
${OBJECTDIR}/_ext/1360937237/photo_detect.o: ../src/photo_detect.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/photo_detect.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/photo_detect.o.ok ${OBJECTDIR}/_ext/1360937237/photo_detect.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/photo_detect.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/photo_detect.o.d" -o ${OBJECTDIR}/_ext/1360937237/photo_detect.o ../src/photo_detect.c    
	
${OBJECTDIR}/_ext/1360937237/led.o: ../src/led.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/led.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/led.o.ok ${OBJECTDIR}/_ext/1360937237/led.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/led.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/led.o.d" -o ${OBJECTDIR}/_ext/1360937237/led.o ../src/led.c    
	
${OBJECTDIR}/_ext/911561563/beacon_com.o: ../../common/beacon_system/src/beacon_com.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/911561563 
	@${RM} ${OBJECTDIR}/_ext/911561563/beacon_com.o.d 
	@${RM} ${OBJECTDIR}/_ext/911561563/beacon_com.o.ok ${OBJECTDIR}/_ext/911561563/beacon_com.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/911561563/beacon_com.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -MMD -MF "${OBJECTDIR}/_ext/911561563/beacon_com.o.d" -o ${OBJECTDIR}/_ext/911561563/beacon_com.o ../../common/beacon_system/src/beacon_com.c    
	
${OBJECTDIR}/_ext/1360937237/distance_matcher.o: ../src/distance_matcher.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/distance_matcher.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/distance_matcher.o.ok ${OBJECTDIR}/_ext/1360937237/distance_matcher.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/distance_matcher.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/distance_matcher.o.d" -o ${OBJECTDIR}/_ext/1360937237/distance_matcher.o ../src/distance_matcher.c    
	
${OBJECTDIR}/_ext/1360937237/distance_lut.o: ../src/distance_lut.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/distance_lut.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/distance_lut.o.ok ${OBJECTDIR}/_ext/1360937237/distance_lut.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/distance_lut.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/distance_lut.o.d" -o ${OBJECTDIR}/_ext/1360937237/distance_lut.o ../src/distance_lut.c    
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/beacon_brx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -o dist/${CND_CONF}/${IMAGE_TYPE}/beacon_brx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1
else
dist/${CND_CONF}/${IMAGE_TYPE}/beacon_brx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/beacon_brx.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}\\pic30-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/beacon_brx.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -omf=elf
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
