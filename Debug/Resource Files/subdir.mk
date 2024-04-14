################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Resource\ Files/Button.cpp 

CPP_DEPS += \
./Resource\ Files/Button.d 

OBJS += \
./Resource\ Files/Button.o 


# Each subdirectory must supply rules for building sources it contributes
Resource\ Files/Button.o: ../Resource\ Files/Button.cpp Resource\ Files/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"Resource Files/Button.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Resource-20-Files

clean-Resource-20-Files:
	-$(RM) ./Resource\ Files/Button.d ./Resource\ Files/Button.o

.PHONY: clean-Resource-20-Files

