################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Entities/Entity.cpp 

CPP_DEPS += \
./Entities/Entity.d 

OBJS += \
./Entities/Entity.o 


# Each subdirectory must supply rules for building sources it contributes
Entities/%.o: ../Entities/%.cpp Entities/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Entities

clean-Entities:
	-$(RM) ./Entities/Entity.d ./Entities/Entity.o

.PHONY: clean-Entities

