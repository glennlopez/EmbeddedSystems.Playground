################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4

ORDERED_OBJS += \
"./LED.obj" \
"./Nokia5110.obj" \
"./board.obj" \
"./device.obj" \
"./driver.obj" \
"./flowcont.obj" \
"./fs.obj" \
"./main.obj" \
"./netapp.obj" \
"./netcfg.obj" \
"./nonos.obj" \
"./socket.obj" \
"./spawn.obj" \
"./spi.obj" \
"./startup_ccs.obj" \
"./uart.obj" \
"./uartstdio.obj" \
"./ustdlib.obj" \
"./wlan.obj" \
"../tm4c123gh6pm.cmd" \
$(GEN_CMDS__FLAG) \
-l"libc.a" \
-l"D:/Dropbox/ArmBook/LaunchPad/ValvanoWareTM4C123\driverlib\ccs\Debug\driverlib.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
CC3100GetWeather_4C123.out \

EXE_OUTPUTS__QUOTED += \
"CC3100GetWeather_4C123.out" \

BIN_OUTPUTS += \
CC3100GetWeather_4C123.hex \

BIN_OUTPUTS__QUOTED += \
"CC3100GetWeather_4C123.hex" \


# All Target
all: CC3100GetWeather_4C123.out

# Tool invocations
CC3100GetWeather_4C123.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linker'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -g --c99 --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --display_error_number --diag_warning=225 --diag_wrap=off -z -m"CC3100GetWeather_4C123.map" --heap_size=0 --stack_size=1024 -i"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/lib" -i"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/include" --reread_libs --warn_sections --display_error_number --diag_wrap=off --xml_link_info="CC3100GetWeather_4C123_linkInfo.xml" --rom_model -o "CC3100GetWeather_4C123.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

CC3100GetWeather_4C123.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: ARM Hex Utility'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/bin/armhex"  -o "CC3100GetWeather_4C123.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "LED.pp" "Nokia5110.pp" "board.pp" "device.pp" "driver.pp" "flowcont.pp" "fs.pp" "main.pp" "netapp.pp" "netcfg.pp" "nonos.pp" "socket.pp" "spawn.pp" "spi.pp" "startup_ccs.pp" "uart.pp" "uartstdio.pp" "ustdlib.pp" "wlan.pp" 
	-$(RM) "LED.obj" "Nokia5110.obj" "board.obj" "device.obj" "driver.obj" "flowcont.obj" "fs.obj" "main.obj" "netapp.obj" "netcfg.obj" "nonos.obj" "socket.obj" "spawn.obj" "spi.obj" "startup_ccs.obj" "uart.obj" "uartstdio.obj" "ustdlib.obj" "wlan.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

