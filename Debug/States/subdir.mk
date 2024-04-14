################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../States/GameState.cpp \
../States/State.cpp 

CPP_DEPS += \
./States/GameState.d \
./States/State.d 

OBJS += \
./States/GameState.o \
./States/State.o 


# Each subdirectory must supply rules for building sources it contributes
States/%.o: ../States/%.cpp States/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-States

clean-States:
	-$(RM) ./States/GameState.d ./States/GameState.o ./States/State.d ./States/State.o

.PHONY: clean-States

