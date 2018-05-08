################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/draw_gl.cpp \
../src/init_gl.cpp \
../src/main.cpp 

OBJS += \
./src/draw_gl.o \
./src/init_gl.o \
./src/main.o 

CPP_DEPS += \
./src/draw_gl.d \
./src/init_gl.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/kar/Documents/c++/eclipse/opengl2_triangle/3rd-party/include -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


