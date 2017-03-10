################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./adc.obj" \
"./can.obj" \
"./comp.obj" \
"./cpu.obj" \
"./eeprom.obj" \
"./epi.obj" \
"./ethernet.obj" \
"./fan.obj" \
"./flash.obj" \
"./fpu.obj" \
"./gpio.obj" \
"./hibernate.obj" \
"./i2c.obj" \
"./i2s.obj" \
"./interrupt.obj" \
"./lpc.obj" \
"./mpu.obj" \
"./peci.obj" \
"./pwm.obj" \
"./qei.obj" \
"./ssi.obj" \
"./sysctl.obj" \
"./sysexc.obj" \
"./systick.obj" \
"./timer.obj" \
"./uart.obj" \
"./udma.obj" \
"./usb.obj" \
"./watchdog.obj" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LIB_OUTPUTS += \
driverlib-cm4f.lib \

LIB_OUTPUTS__QUOTED += \
"driverlib-cm4f.lib" \


# All Target
all: driverlib-cm4f.lib

# Tool invocations
driverlib-cm4f.lib: $(OBJS)
ifneq ($(strip $(ORDERED_OBJS)),)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Archiver'
	"D:/EngineeringSoftware/CCS/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armar" r "driverlib-cm4f.lib" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '
endif

# Other Targets
clean:
	-$(RM) $(LIB_OUTPUTS__QUOTED)
	-$(RM) "adc.obj" "can.obj" "comp.obj" "cpu.obj" "eeprom.obj" "epi.obj" "ethernet.obj" "fan.obj" "flash.obj" "fpu.obj" "gpio.obj" "hibernate.obj" "i2c.obj" "i2s.obj" "interrupt.obj" "lpc.obj" "mpu.obj" "peci.obj" "pwm.obj" "qei.obj" "ssi.obj" "sysctl.obj" "sysexc.obj" "systick.obj" "timer.obj" "uart.obj" "udma.obj" "usb.obj" "watchdog.obj" 
	-$(RM) "adc.d" "can.d" "comp.d" "cpu.d" "eeprom.d" "epi.d" "ethernet.d" "fan.d" "flash.d" "fpu.d" "gpio.d" "hibernate.d" "i2c.d" "i2s.d" "interrupt.d" "lpc.d" "mpu.d" "peci.d" "pwm.d" "qei.d" "ssi.d" "sysctl.d" "sysexc.d" "systick.d" "timer.d" "uart.d" "udma.d" "usb.d" "watchdog.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

