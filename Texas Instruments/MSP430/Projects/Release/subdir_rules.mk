################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
blink.obj: ../blink.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"D:/EngineeringSoftware/CCS/ccsv7/tools/compiler/ti-cgt-msp430_16.9.0.LTS/bin/cl430" -vmsp -O2 --use_hw_mpy=none --include_path="D:/EngineeringSoftware/CCS/ccsv7/ccs_base/msp430/include" --include_path="D:/EngineeringSoftware/CCS/ccsv7/tools/compiler/ti-cgt-msp430_16.9.0.LTS/include" --advice:power=all --define=__MSP430G2553__ --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="blink.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


