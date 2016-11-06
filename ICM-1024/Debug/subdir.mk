################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ICM1024.c 

OBJS += \
./ICM1024.o 

C_DEPS += \
./ICM1024.d 


# Each subdirectory must supply rules for building sources it contributes
ICM1024.o: ../ICM1024.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -DWOLFSSL_SHA512 -DCYASSL_SHA512 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"ICM1024.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


