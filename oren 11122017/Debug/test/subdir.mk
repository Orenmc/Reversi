################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/gtest_main.cpp \
../test/test_Board.cpp \
../test/test_GameLogic.cpp \
../test/test_Point.cpp 

OBJS += \
./test/gtest_main.o \
./test/test_Board.o \
./test/test_GameLogic.o \
./test/test_Point.o 

CPP_DEPS += \
./test/gtest_main.d \
./test/test_Board.d \
./test/test_GameLogic.d \
./test/test_Point.d 


# Each subdirectory must supply rules for building sources it contributes
test/%.o: ../test/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/oren/Desktop/c++/workspace/ex2/gtest_src" -I"/home/oren/Desktop/c++/workspace/ex2/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


