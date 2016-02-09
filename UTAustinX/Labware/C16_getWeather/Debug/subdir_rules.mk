################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
LED.obj: ../LED.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/inc" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/utils" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/platform/ek-tm4c123gxl" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/CC3100/simplelink/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/simplelink/source" -g --c99 --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="LED.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Nokia5110.obj: ../Nokia5110.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/inc" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/utils" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/platform/ek-tm4c123gxl" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/CC3100/simplelink/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/simplelink/source" -g --c99 --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Nokia5110.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

board.obj: D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/CC3100/platform/ek-tm4c123gxl/board.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/inc" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/utils" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/platform/ek-tm4c123gxl" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/CC3100/simplelink/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/simplelink/source" -g --c99 --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="board.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

device.obj: D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/CC3100/simplelink/source/device.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/inc" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/utils" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/platform/ek-tm4c123gxl" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/CC3100/simplelink/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/simplelink/source" -g --c99 --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="device.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

driver.obj: D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/CC3100/simplelink/source/driver.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/inc" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/utils" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/platform/ek-tm4c123gxl" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/CC3100/simplelink/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/simplelink/source" -g --c99 --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="driver.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

flowcont.obj: D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/CC3100/simplelink/source/flowcont.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/inc" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/utils" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/platform/ek-tm4c123gxl" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/CC3100/simplelink/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/simplelink/source" -g --c99 --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="flowcont.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

fs.obj: D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/CC3100/simplelink/source/fs.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/inc" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/utils" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/platform/ek-tm4c123gxl" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/CC3100/simplelink/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/simplelink/source" -g --c99 --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="fs.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/inc" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/utils" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/platform/ek-tm4c123gxl" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/CC3100/simplelink/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/simplelink/source" -g --c99 --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

netapp.obj: D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/CC3100/simplelink/source/netapp.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/inc" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/utils" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/platform/ek-tm4c123gxl" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/CC3100/simplelink/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/simplelink/source" -g --c99 --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="netapp.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

netcfg.obj: D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/CC3100/simplelink/source/netcfg.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/inc" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/utils" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/platform/ek-tm4c123gxl" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/CC3100/simplelink/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/simplelink/source" -g --c99 --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="netcfg.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

nonos.obj: D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/CC3100/simplelink/source/nonos.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/inc" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/utils" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/platform/ek-tm4c123gxl" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/CC3100/simplelink/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/simplelink/source" -g --c99 --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="nonos.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

socket.obj: D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/CC3100/simplelink/source/socket.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/inc" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/utils" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/platform/ek-tm4c123gxl" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/CC3100/simplelink/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/simplelink/source" -g --c99 --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="socket.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

spawn.obj: D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/CC3100/simplelink/source/spawn.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/inc" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/utils" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/platform/ek-tm4c123gxl" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/CC3100/simplelink/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/simplelink/source" -g --c99 --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="spawn.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

spi.obj: D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/CC3100/platform/ek-tm4c123gxl/spi.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/inc" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/utils" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/platform/ek-tm4c123gxl" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/CC3100/simplelink/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/simplelink/source" -g --c99 --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="spi.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

startup_ccs.obj: ../startup_ccs.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/inc" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/utils" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/platform/ek-tm4c123gxl" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/CC3100/simplelink/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/simplelink/source" -g --c99 --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="startup_ccs.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uart.obj: D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/CC3100/platform/ek-tm4c123gxl/uart.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/inc" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/utils" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/platform/ek-tm4c123gxl" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/CC3100/simplelink/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/simplelink/source" -g --c99 --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="uart.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uartstdio.obj: D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/CC3100/platform/ek-tm4c123gxl/uartstdio.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/inc" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/utils" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/platform/ek-tm4c123gxl" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/CC3100/simplelink/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/simplelink/source" -g --c99 --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="uartstdio.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ustdlib.obj: D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/CC3100/platform/ek-tm4c123gxl/ustdlib.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/inc" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/utils" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/platform/ek-tm4c123gxl" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/CC3100/simplelink/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/simplelink/source" -g --c99 --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="ustdlib.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

wlan.obj: D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/CC3100/simplelink/source/wlan.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/inc" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/utils" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/platform/ek-tm4c123gxl" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/CC3100/simplelink/include" --include_path="D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123/cc3100/simplelink/source" -g --c99 --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="wlan.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


