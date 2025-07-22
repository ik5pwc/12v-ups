################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/lc@civinini.home/.local/bin/Sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.8.6/libraries/SPI/src/SPI.cpp 

LINK_OBJ += \
./libraries/SPI/src/SPI.cpp.o 

CPP_DEPS += \
./libraries/SPI/src/SPI.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/SPI/src/SPI.cpp.o: /home/lc@civinini.home/.local/bin/Sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.8.6/libraries/SPI/src/SPI.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/lc@civinini.home/.local/bin/Sloeber/arduinoPlugin/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10812 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR   -I"/home/lc@civinini.home/.local/bin/Sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.8.6/cores/arduino" -I"/home/lc@civinini.home/.local/bin/Sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.8.6/variants/standard" -I"/home/lc@civinini.home/.local/bin/Sloeber/arduinoPlugin/libraries/Ethernet/2.0.2/src" -I"/home/lc@civinini.home/.local/bin/Sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.8.6/libraries/SPI/src" -I"/home/lc@civinini.home/.local/bin/Sloeber/arduinoPlugin/libraries/LiquidCrystal/1.0.7/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 "$<" -o "$@"
	@echo 'Finished building: $<'
	@echo ' '


