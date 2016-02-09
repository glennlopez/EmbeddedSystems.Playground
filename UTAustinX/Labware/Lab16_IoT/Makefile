#******************************************************************************
#
# Makefile - Rules for building the CC3000 Basic WiFi Application.
#
# Copyright (c) 2014 Texas Instruments Incorporated.  All rights reserved.
# TI Information - Selective Disclosure
#
#******************************************************************************

#
# Defines the part type that this project uses.
#
PART=TM4C123GH6PM

#
# The base directory for TivaWare.
#
ROOT=../../../..

#
# Include the common make definitions.
#
include ${ROOT}/makedefs

#
# Where to find source files that do not live in this directory.
#
VPATH=../cc3100
VPATH+=../drivers
VPATH+=../cc3100/platform/ek-tm4c123gxl
VPATH+=../cc3100/simplelink/include
VPATH+=../cc3100/simplelink/source
VPATH+=../../../../utils
VPATH+=../../../../utils

#
# Where to find header files that do not live in the source directory.
#
IPATH=..
IPATH+=../
IPATH+=../../../..
IPATH+=../cc3100
IPATH+=../cc3100/platform/ek-tm4c123gxl
IPATH+=../cc3100/simplelink/include
IPATH+=../cc3100/simplelink/source

#
# The default rule, which causes the CC3000 Basic WiFi Application to be built.
#
all: ${COMPILER}
all: ${COMPILER}/cc31000_starter.axf
##### INTERNAL BEGIN #####
all_comp:
	@for i in `grep COMPILER= ${ROOT}/makedefs | awk -F= '{print $$2}'`; \
	 do                                                                  \
	     ${MAKE} COMPILER=$${i};                                            \
	 done

#
# A rule to regenerate the Makefile if config.in has changed.
#
Makefile: config.in
	@perl ${ROOT}/scripts/buildproj.pl -s -f config.in
##### INTERNAL END #####

#
# The rule to clean out all the build products.
#
clean:
	@rm -rf ${COMPILER} ${wildcard *~}
##### INTERNAL BEGIN #####
	@rm -rf settings ${wildcard *.Bak} ${wildcard *.dep}
clean_comp:
	@for i in `grep COMPILER= ${ROOT}/makedefs | awk -F= '{print $$2}'`; \
	 do                                                                  \
	     ${MAKE} COMPILER=$${i} clean;                                      \
	 done

#
# Cleans out everything, including the Makefile.  Should return this directory
# to fresh from subversion status.
#
realclean:: clean
	@rm -rf ccs codered ewarm gcc rvmdk sourcerygxx ccstempws
	@rm -f ${wildcard *.Uv2} ${wildcard *.Opt}
	@rm -f ${wildcard *.uvopt} ${wildcard *.uvproj}
	@rm -f ${wildcard *.ew?} ${wildcard *.xcl}
	@rm -f ${wildcard *.sgxx}
	@rm -f ccs_proj_args.txt
	@rm -f cc31000_starter_ccs.cmd
	@rm -f cc31000_starter_codered.ld
	@rm -f cc31000_starter.ld
	@rm -f cc31000_starter_sourcerygxx.ld
	@rm -f ${wildcard *-rom.ld}
	@rm -f cc31000_starter.icf
	@rm -f cc31000_starter.sct
	@rm -f ${wildcard *.xml}
	@rm -f ${wildcard startup_*}
	@rm -f readme.txt
	@rm -f Makefile cr_project.xml
##### INTERNAL END #####

#
# The rule to create the target directory.
#
${COMPILER}:
	@mkdir -p ${COMPILER}

#
# Rules for building the CC3000 Basic WiFi Application.
#
${COMPILER}/cc31000_starter.axf: ${COMPILER}/board.o
${COMPILER}/cc31000_starter.axf: ${COMPILER}/cmdline.o
${COMPILER}/cc31000_starter.axf: ${COMPILER}/device.o
${COMPILER}/cc31000_starter.axf: ${COMPILER}/driver.o
${COMPILER}/cc31000_starter.axf: ${COMPILER}/flowcont.o
${COMPILER}/cc31000_starter.axf: ${COMPILER}/fs.o
${COMPILER}/cc31000_starter.axf: ${COMPILER}/netapp.o
${COMPILER}/cc31000_starter.axf: ${COMPILER}/netcfg.o
${COMPILER}/cc31000_starter.axf: ${COMPILER}/nonos.o
${COMPILER}/cc31000_starter.axf: ${COMPILER}/socket.o
${COMPILER}/cc31000_starter.axf: ${COMPILER}/spawn.o
${COMPILER}/cc31000_starter.axf: ${COMPILER}/spi.o
${COMPILER}/cc31000_starter.axf: ${COMPILER}/starter.o
${COMPILER}/cc31000_starter.axf: ${COMPILER}/startup_${COMPILER}.o
${COMPILER}/cc31000_starter.axf: ${COMPILER}/uart.o
${COMPILER}/cc31000_starter.axf: ${COMPILER}/uartstdio.o
${COMPILER}/cc31000_starter.axf: ${COMPILER}/ustdlib.o
${COMPILER}/cc31000_starter.axf: ${COMPILER}/wlan.o
${COMPILER}/cc31000_starter.axf: ${ROOT}/driverlib/${COMPILER}/libdriver.a
##### INTERNAL BEGIN #####
ifeq (${COMPILER}, ccs)
${COMPILER}/cc31000_starter.axf: cc31000_starter_ccs.cmd
endif
SCATTERccs_cc31000_starter=cc31000_starter_ccs.cmd
ifeq (${COMPILER}, codered)
${COMPILER}/cc31000_starter.axf: cc31000_starter_codered.ld
endif
SCATTERcodered_cc31000_starter=cc31000_starter_codered.ld
ifeq (${COMPILER}, ewarm)
${COMPILER}/cc31000_starter.axf: cc31000_starter.icf
endif
SCATTERewarm_cc31000_starter=cc31000_starter.icf
ifeq (${COMPILER}, gcc)
##### INTERNAL END #####
${COMPILER}/cc31000_starter.axf: cc31000_starter.ld
##### INTERNAL BEGIN #####
endif
##### INTERNAL END #####
SCATTERgcc_cc31000_starter=cc31000_starter.ld
##### INTERNAL BEGIN #####
ifeq (${COMPILER}, rvmdk)
${COMPILER}/cc31000_starter.axf: cc31000_starter.sct
endif
SCATTERrvmdk_cc31000_starter=cc31000_starter.sct
ifeq (${COMPILER}, sourcerygxx)
${COMPILER}/cc31000_starter.axf: cc31000_starter_sourcerygxx.ld
endif
SCATTERsourcerygxx_cc31000_starter=lm4f120h5qr-rom.ld -T cc31000_starter_sourcerygxx.ld
##### INTERNAL END #####
ENTRY_cc31000_starter=ResetISR
##### INTERNAL BEGIN #####
CFLAGSccs=-D_POSIX_SOURCE -DUART_BUFFERED -DTARGET_IS_TM4C123_RB1
##### INTERNAL END #####
##### INTERNAL BEGIN #####
CFLAGScodered=-D_POSIX_SOURCE -DUART_BUFFERED -DTARGET_IS_TM4C123_RB1
##### INTERNAL END #####
##### INTERNAL BEGIN #####
CFLAGSewarm=-D_POSIX_SOURCE -DUART_BUFFERED -DTARGET_IS_TM4C123_RB1
##### INTERNAL END #####
CFLAGSgcc=-D_POSIX_SOURCE -DUART_BUFFERED -DTARGET_IS_TM4C123_RB1
##### INTERNAL BEGIN #####
CFLAGSrvmdk=-D_POSIX_SOURCE -DUART_BUFFERED -DTARGET_IS_TM4C123_RB1
##### INTERNAL END #####
##### INTERNAL BEGIN #####
CFLAGSsourcerygxx=-D_POSIX_SOURCE -DUART_BUFFERED -DTARGET_IS_TM4C123_RB1
##### INTERNAL END #####

#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
##### INTERNAL BEGIN #####
ifneq (${MAKECMDGOALS},realclean)
##### INTERNAL END #####
-include ${wildcard ${COMPILER}/*.d} __dummy__
##### INTERNAL BEGIN #####
endif
##### INTERNAL END #####
endif
