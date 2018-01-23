################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AIPlayer.cpp \
../src/Board.cpp \
../src/DummyPlayer.cpp \
../src/Game.cpp \
../src/GameLogic.cpp \
../src/HumanPlayer.cpp \
../src/InputTest.cpp \
../src/Player.cpp \
../src/Point.cpp \
../src/RemoteGameLogic.cpp \
../src/RemotePlayer.cpp \
../src/main.cpp 

OBJS += \
./src/AIPlayer.o \
./src/Board.o \
./src/DummyPlayer.o \
./src/Game.o \
./src/GameLogic.o \
./src/HumanPlayer.o \
./src/InputTest.o \
./src/Player.o \
./src/Point.o \
./src/RemoteGameLogic.o \
./src/RemotePlayer.o \
./src/main.o 

CPP_DEPS += \
./src/AIPlayer.d \
./src/Board.d \
./src/DummyPlayer.d \
./src/Game.d \
./src/GameLogic.d \
./src/HumanPlayer.d \
./src/InputTest.d \
./src/Player.d \
./src/Point.d \
./src/RemoteGameLogic.d \
./src/RemotePlayer.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


