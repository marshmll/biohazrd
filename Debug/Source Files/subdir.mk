################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source\ Files/Game.cpp \
../Source\ Files/main.cpp 

CPP_DEPS += \
./Source\ Files/Game.d \
./Source\ Files/main.d 

OBJS += \
./Source\ Files/Game.o \
./Source\ Files/main.o 


# Each subdirectory must supply rules for building sources it contributes
Source\ Files/Game.o: ../Source\ Files/Game.cpp Source\ Files/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"Source Files/Game.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source\ Files/main.o: ../Source\ Files/main.cpp Source\ Files/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"Source Files/main.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Source-20-Files

clean-Source-20-Files:
	-$(RM) ./Source\ Files/Game.d ./Source\ Files/Game.o ./Source\ Files/main.d ./Source\ Files/main.o

.PHONY: clean-Source-20-Files

