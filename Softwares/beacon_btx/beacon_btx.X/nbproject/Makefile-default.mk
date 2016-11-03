#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/beacon_btx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/beacon_btx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1360937237/beacon_btx.o ${OBJECTDIR}/_ext/1360937237/oscillator.o ${OBJECTDIR}/_ext/1360937237/drum_control.o ${OBJECTDIR}/_ext/1360937237/power_modulation.o ${OBJECTDIR}/_ext/1502898876/cc2500.o ${OBJECTDIR}/_ext/1360937237/rf_master.o ${OBJECTDIR}/_ext/1952603297/igrecan.o ${OBJECTDIR}/_ext/1952603297/igrecan_pl.o ${OBJECTDIR}/_ext/1360937237/can.o ${OBJECTDIR}/_ext/911561563/beacon_com.o ${OBJECTDIR}/_ext/1360937237/led.o ${OBJECTDIR}/_ext/1025385228/scheduler.o ${OBJECTDIR}/_ext/971770598/watchdog.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1360937237/beacon_btx.o.d ${OBJECTDIR}/_ext/1360937237/oscillator.o.d ${OBJECTDIR}/_ext/1360937237/drum_control.o.d ${OBJECTDIR}/_ext/1360937237/power_modulation.o.d ${OBJECTDIR}/_ext/1502898876/cc2500.o.d ${OBJECTDIR}/_ext/1360937237/rf_master.o.d ${OBJECTDIR}/_ext/1952603297/igrecan.o.d ${OBJECTDIR}/_ext/1952603297/igrecan_pl.o.d ${OBJECTDIR}/_ext/1360937237/can.o.d ${OBJECTDIR}/_ext/911561563/beacon_com.o.d ${OBJECTDIR}/_ext/1360937237/led.o.d ${OBJECTDIR}/_ext/1025385228/scheduler.o.d ${OBJECTDIR}/_ext/971770598/watchdog.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1360937237/beacon_btx.o ${OBJECTDIR}/_ext/1360937237/oscillator.o ${OBJECTDIR}/_ext/1360937237/drum_control.o ${OBJECTDIR}/_ext/1360937237/power_modulation.o ${OBJECTDIR}/_ext/1502898876/cc2500.o ${OBJECTDIR}/_ext/1360937237/rf_master.o ${OBJECTDIR}/_ext/1952603297/igrecan.o ${OBJECTDIR}/_ext/1952603297/igrecan_pl.o ${OBJECTDIR}/_ext/1360937237/can.o ${OBJECTDIR}/_ext/911561563/beacon_com.o ${OBJECTDIR}/_ext/1360937237/led.o ${OBJECTDIR}/_ext/1025385228/scheduler.o ${OBJECTDIR}/_ext/971770598/watchdog.o


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/beacon_btx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/_ext/1360937237/beacon_btx.o: ../src/beacon_btx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/beacon_btx.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/beacon_btx.o.ok ${OBJECTDIR}/_ext/1360937237/beacon_btx.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/beacon_btx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -I"../../common/scheduler/src" -I"../../common/robot_system/src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/beacon_btx.o.d" -o ${OBJECTDIR}/_ext/1360937237/beacon_btx.o ../src/beacon_btx.c    
	
${OBJECTDIR}/_ext/1360937237/oscillator.o: ../src/oscillator.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/oscillator.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/oscillator.o.ok ${OBJECTDIR}/_ext/1360937237/oscillator.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/oscillator.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -I"../../common/scheduler/src" -I"../../common/robot_system/src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/oscillator.o.d" -o ${OBJECTDIR}/_ext/1360937237/oscillator.o ../src/oscillator.c    
	
${OBJECTDIR}/_ext/1360937237/drum_control.o: ../src/drum_control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drum_control.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drum_control.o.ok ${OBJECTDIR}/_ext/1360937237/drum_control.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/drum_control.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -I"../../common/scheduler/src" -I"../../common/robot_system/src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/drum_control.o.d" -o ${OBJECTDIR}/_ext/1360937237/drum_control.o ../src/drum_control.c    
	
${OBJECTDIR}/_ext/1360937237/power_modulation.o: ../src/power_modulation.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/power_modulation.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/power_modulation.o.ok ${OBJECTDIR}/_ext/1360937237/power_modulation.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/power_modulation.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -I"../../common/scheduler/src" -I"../../common/robot_system/src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/power_modulation.o.d" -o ${OBJECTDIR}/_ext/1360937237/power_modulation.o ../src/power_modulation.c    
	
${OBJECTDIR}/_ext/1502898876/cc2500.o: ../../common/cc2500/src/cc2500.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1502898876 
	@${RM} ${OBJECTDIR}/_ext/1502898876/cc2500.o.d 
	@${RM} ${OBJECTDIR}/_ext/1502898876/cc2500.o.ok ${OBJECTDIR}/_ext/1502898876/cc2500.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1502898876/cc2500.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -I"../../common/scheduler/src" -I"../../common/robot_system/src" -MMD -MF "${OBJECTDIR}/_ext/1502898876/cc2500.o.d" -o ${OBJECTDIR}/_ext/1502898876/cc2500.o ../../common/cc2500/src/cc2500.c    
	
${OBJECTDIR}/_ext/1360937237/rf_master.o: ../src/rf_master.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/rf_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/rf_master.o.ok ${OBJECTDIR}/_ext/1360937237/rf_master.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/rf_master.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -I"../../common/scheduler/src" -I"../../common/robot_system/src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/rf_master.o.d" -o ${OBJECTDIR}/_ext/1360937237/rf_master.o ../src/rf_master.c    
	
${OBJECTDIR}/_ext/1952603297/igrecan.o: ../../common/can/src/igrecan.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1952603297 
	@${RM} ${OBJECTDIR}/_ext/1952603297/igrecan.o.d 
	@${RM} ${OBJECTDIR}/_ext/1952603297/igrecan.o.ok ${OBJECTDIR}/_ext/1952603297/igrecan.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1952603297/igrecan.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -I"../../common/scheduler/src" -I"../../common/robot_system/src" -MMD -MF "${OBJECTDIR}/_ext/1952603297/igrecan.o.d" -o ${OBJECTDIR}/_ext/1952603297/igrecan.o ../../common/can/src/igrecan.c    
	
${OBJECTDIR}/_ext/1952603297/igrecan_pl.o: ../../common/can/src/igrecan_pl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1952603297 
	@${RM} ${OBJECTDIR}/_ext/1952603297/igrecan_pl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1952603297/igrecan_pl.o.ok ${OBJECTDIR}/_ext/1952603297/igrecan_pl.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1952603297/igrecan_pl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -I"../../common/scheduler/src" -I"../../common/robot_system/src" -MMD -MF "${OBJECTDIR}/_ext/1952603297/igrecan_pl.o.d" -o ${OBJECTDIR}/_ext/1952603297/igrecan_pl.o ../../common/can/src/igrecan_pl.c    
	
${OBJECTDIR}/_ext/1360937237/can.o: ../src/can.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can.o.ok ${OBJECTDIR}/_ext/1360937237/can.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/can.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -I"../../common/scheduler/src" -I"../../common/robot_system/src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/can.o.d" -o ${OBJECTDIR}/_ext/1360937237/can.o ../src/can.c    
	
${OBJECTDIR}/_ext/911561563/beacon_com.o: ../../common/beacon_system/src/beacon_com.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/911561563 
	@${RM} ${OBJECTDIR}/_ext/911561563/beacon_com.o.d 
	@${RM} ${OBJECTDIR}/_ext/911561563/beacon_com.o.ok ${OBJECTDIR}/_ext/911561563/beacon_com.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/911561563/beacon_com.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -I"../../common/scheduler/src" -I"../../common/robot_system/src" -MMD -MF "${OBJECTDIR}/_ext/911561563/beacon_com.o.d" -o ${OBJECTDIR}/_ext/911561563/beacon_com.o ../../common/beacon_system/src/beacon_com.c    
	
${OBJECTDIR}/_ext/1360937237/led.o: ../src/led.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/led.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/led.o.ok ${OBJECTDIR}/_ext/1360937237/led.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/led.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -I"../../common/scheduler/src" -I"../../common/robot_system/src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/led.o.d" -o ${OBJECTDIR}/_ext/1360937237/led.o ../src/led.c    
	
${OBJECTDIR}/_ext/1025385228/scheduler.o: ../../common/scheduler/src/scheduler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1025385228 
	@${RM} ${OBJECTDIR}/_ext/1025385228/scheduler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1025385228/scheduler.o.ok ${OBJECTDIR}/_ext/1025385228/scheduler.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1025385228/scheduler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -I"../../common/scheduler/src" -I"../../common/robot_system/src" -MMD -MF "${OBJECTDIR}/_ext/1025385228/scheduler.o.d" -o ${OBJECTDIR}/_ext/1025385228/scheduler.o ../../common/scheduler/src/scheduler.c    
	
${OBJECTDIR}/_ext/971770598/watchdog.o: ../../common/watchdog/src/watchdog.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/971770598 
	@${RM} ${OBJECTDIR}/_ext/971770598/watchdog.o.d 
	@${RM} ${OBJECTDIR}/_ext/971770598/watchdog.o.ok ${OBJECTDIR}/_ext/971770598/watchdog.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/971770598/watchdog.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -I"../../common/scheduler/src" -I"../../common/robot_system/src" -MMD -MF "${OBJECTDIR}/_ext/971770598/watchdog.o.d" -o ${OBJECTDIR}/_ext/971770598/watchdog.o ../../common/watchdog/src/watchdog.c    
	
else
${OBJECTDIR}/_ext/1360937237/beacon_btx.o: ../src/beacon_btx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/beacon_btx.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/beacon_btx.o.ok ${OBJECTDIR}/_ext/1360937237/beacon_btx.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/beacon_btx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -I"../../common/scheduler/src" -I"../../common/robot_system/src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/beacon_btx.o.d" -o ${OBJECTDIR}/_ext/1360937237/beacon_btx.o ../src/beacon_btx.c    
	
${OBJECTDIR}/_ext/1360937237/oscillator.o: ../src/oscillator.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/oscillator.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/oscillator.o.ok ${OBJECTDIR}/_ext/1360937237/oscillator.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/oscillator.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -I"../../common/scheduler/src" -I"../../common/robot_system/src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/oscillator.o.d" -o ${OBJECTDIR}/_ext/1360937237/oscillator.o ../src/oscillator.c    
	
${OBJECTDIR}/_ext/1360937237/drum_control.o: ../src/drum_control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drum_control.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/drum_control.o.ok ${OBJECTDIR}/_ext/1360937237/drum_control.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/drum_control.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -I"../../common/scheduler/src" -I"../../common/robot_system/src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/drum_control.o.d" -o ${OBJECTDIR}/_ext/1360937237/drum_control.o ../src/drum_control.c    
	
${OBJECTDIR}/_ext/1360937237/power_modulation.o: ../src/power_modulation.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/power_modulation.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/power_modulation.o.ok ${OBJECTDIR}/_ext/1360937237/power_modulation.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/power_modulation.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -I"../../common/scheduler/src" -I"../../common/robot_system/src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/power_modulation.o.d" -o ${OBJECTDIR}/_ext/1360937237/power_modulation.o ../src/power_modulation.c    
	
${OBJECTDIR}/_ext/1502898876/cc2500.o: ../../common/cc2500/src/cc2500.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1502898876 
	@${RM} ${OBJECTDIR}/_ext/1502898876/cc2500.o.d 
	@${RM} ${OBJECTDIR}/_ext/1502898876/cc2500.o.ok ${OBJECTDIR}/_ext/1502898876/cc2500.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1502898876/cc2500.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -I"../../common/scheduler/src" -I"../../common/robot_system/src" -MMD -MF "${OBJECTDIR}/_ext/1502898876/cc2500.o.d" -o ${OBJECTDIR}/_ext/1502898876/cc2500.o ../../common/cc2500/src/cc2500.c    
	
${OBJECTDIR}/_ext/1360937237/rf_master.o: ../src/rf_master.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/rf_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/rf_master.o.ok ${OBJECTDIR}/_ext/1360937237/rf_master.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/rf_master.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -I"../../common/scheduler/src" -I"../../common/robot_system/src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/rf_master.o.d" -o ${OBJECTDIR}/_ext/1360937237/rf_master.o ../src/rf_master.c    
	
${OBJECTDIR}/_ext/1952603297/igrecan.o: ../../common/can/src/igrecan.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1952603297 
	@${RM} ${OBJECTDIR}/_ext/1952603297/igrecan.o.d 
	@${RM} ${OBJECTDIR}/_ext/1952603297/igrecan.o.ok ${OBJECTDIR}/_ext/1952603297/igrecan.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1952603297/igrecan.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -I"../../common/scheduler/src" -I"../../common/robot_system/src" -MMD -MF "${OBJECTDIR}/_ext/1952603297/igrecan.o.d" -o ${OBJECTDIR}/_ext/1952603297/igrecan.o ../../common/can/src/igrecan.c    
	
${OBJECTDIR}/_ext/1952603297/igrecan_pl.o: ../../common/can/src/igrecan_pl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1952603297 
	@${RM} ${OBJECTDIR}/_ext/1952603297/igrecan_pl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1952603297/igrecan_pl.o.ok ${OBJECTDIR}/_ext/1952603297/igrecan_pl.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1952603297/igrecan_pl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -I"../../common/scheduler/src" -I"../../common/robot_system/src" -MMD -MF "${OBJECTDIR}/_ext/1952603297/igrecan_pl.o.d" -o ${OBJECTDIR}/_ext/1952603297/igrecan_pl.o ../../common/can/src/igrecan_pl.c    
	
${OBJECTDIR}/_ext/1360937237/can.o: ../src/can.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/can.o.ok ${OBJECTDIR}/_ext/1360937237/can.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/can.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -I"../../common/scheduler/src" -I"../../common/robot_system/src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/can.o.d" -o ${OBJECTDIR}/_ext/1360937237/can.o ../src/can.c    
	
${OBJECTDIR}/_ext/911561563/beacon_com.o: ../../common/beacon_system/src/beacon_com.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/911561563 
	@${RM} ${OBJECTDIR}/_ext/911561563/beacon_com.o.d 
	@${RM} ${OBJECTDIR}/_ext/911561563/beacon_com.o.ok ${OBJECTDIR}/_ext/911561563/beacon_com.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/911561563/beacon_com.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -I"../../common/scheduler/src" -I"../../common/robot_system/src" -MMD -MF "${OBJECTDIR}/_ext/911561563/beacon_com.o.d" -o ${OBJECTDIR}/_ext/911561563/beacon_com.o ../../common/beacon_system/src/beacon_com.c    
	
${OBJECTDIR}/_ext/1360937237/led.o: ../src/led.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/led.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/led.o.ok ${OBJECTDIR}/_ext/1360937237/led.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/led.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -I"../../common/scheduler/src" -I"../../common/robot_system/src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/led.o.d" -o ${OBJECTDIR}/_ext/1360937237/led.o ../src/led.c    
	
${OBJECTDIR}/_ext/1025385228/scheduler.o: ../../common/scheduler/src/scheduler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1025385228 
	@${RM} ${OBJECTDIR}/_ext/1025385228/scheduler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1025385228/scheduler.o.ok ${OBJECTDIR}/_ext/1025385228/scheduler.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1025385228/scheduler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -I"../../common/scheduler/src" -I"../../common/robot_system/src" -MMD -MF "${OBJECTDIR}/_ext/1025385228/scheduler.o.d" -o ${OBJECTDIR}/_ext/1025385228/scheduler.o ../../common/scheduler/src/scheduler.c    
	
${OBJECTDIR}/_ext/971770598/watchdog.o: ../../common/watchdog/src/watchdog.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/971770598 
	@${RM} ${OBJECTDIR}/_ext/971770598/watchdog.o.d 
	@${RM} ${OBJECTDIR}/_ext/971770598/watchdog.o.ok ${OBJECTDIR}/_ext/971770598/watchdog.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/971770598/watchdog.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../common/can/src" -I"../../common/cc2500/src" -I"../../common/beacon_system/src" -I"../../common/scheduler/src" -I"../../common/robot_system/src" -MMD -MF "${OBJECTDIR}/_ext/971770598/watchdog.o.d" -o ${OBJECTDIR}/_ext/971770598/watchdog.o ../../common/watchdog/src/watchdog.c    
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/beacon_btx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -o dist/${CND_CONF}/${IMAGE_TYPE}/beacon_btx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1
else
dist/${CND_CONF}/${IMAGE_TYPE}/beacon_btx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/beacon_btx.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}\\pic30-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/beacon_btx.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -omf=elf
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
