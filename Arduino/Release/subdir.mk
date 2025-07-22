################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../io.cpp \
../lcd.cpp \
../network.cpp \
../sloeber.ino.cpp 

LINK_OBJ += \
./io.cpp.o \
./lcd.cpp.o \
./network.cpp.o \
./sloeber.ino.cpp.o 

CPP_DEPS += \
./io.cpp.d \
./lcd.cpp.d \
./network.cpp.d \
./sloeber.ino.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
io.cpp.o: ../io.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/lc@civinini.home/.local/bin/Sloeber/arduinoPlugin/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10812 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR   -I"/home/lc@civinini.home/.local/bin/Sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.8.6/cores/arduino" -I"/home/lc@civinini.home/.local/bin/Sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.8.6/variants/standard" -I"/home/lc@civinini.home/.local/bin/Sloeber/arduinoPlugin/libraries/Ethernet/2.0.2/src" -I"/home/lc@civinini.home/.local/bin/Sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.8.6/libraries/SPI/src" -I"/home/lc@civinini.home/.local/bin/Sloeber/arduinoPlugin/libraries/LiquidCrystal/1.0.7/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 "$<" -o "$@"
	@echo 'Finished building: $<'
	@echo ' '

lcd.cpp.o: ../lcd.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/lc@civinini.home/.local/bin/Sloeber/arduinoPlugin/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10812 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR   -I"/home/lc@civinini.home/.local/bin/Sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.8.6/cores/arduino" -I"/home/lc@civinini.home/.local/bin/Sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.8.6/variants/standard" -I"/home/lc@civinini.home/.local/bin/Sloeber/arduinoPlugin/libraries/Ethernet/2.0.2/src" -I"/home/lc@civinini.home/.local/bin/Sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.8.6/libraries/SPI/src" -I"/home/lc@civinini.home/.local/bin/Sloeber/arduinoPlugin/libraries/LiquidCrystal/1.0.7/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 "$<" -o "$@"
	@echo 'Finished building: $<'
	@echo ' '

network.cpp.o: ../network.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/lc@civinini.home/.local/bin/Sloeber/arduinoPlugin/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10812 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR   -I"/home/lc@civinini.home/.local/bin/Sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.8.6/cores/arduino" -I"/home/lc@civinini.home/.local/bin/Sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.8.6/variants/standard" -I"/home/lc@civinini.home/.local/bin/Sloeber/arduinoPlugin/libraries/Ethernet/2.0.2/src" -I"/home/lc@civinini.home/.local/bin/Sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.8.6/libraries/SPI/src" -I"/home/lc@civinini.home/.local/bin/Sloeber/arduinoPlugin/libraries/LiquidCrystal/1.0.7/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 "$<" -o "$@"
	@echo 'Finished building: $<'
	@echo ' '

sloeber.ino.cpp.o: ../sloeber.ino.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/lc@civinini.home/.local/bin/Sloeber/arduinoPlugin/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10812 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR   -I"/home/lc@civinini.home/.local/bin/Sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.8.6/cores/arduino" -I"/home/lc@civinini.home/.local/bin/Sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.8.6/variants/standard" -I"/home/lc@civinini.home/.local/bin/Sloeber/arduinoPlugin/libraries/Ethernet/2.0.2/src" -I"/home/lc@civinini.home/.local/bin/Sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.8.6/libraries/SPI/src" -I"/home/lc@civinini.home/.local/bin/Sloeber/arduinoPlugin/libraries/LiquidCrystal/1.0.7/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 "$<" -o "$@"

	@echo 'Finished building: $<'
	@echo ' '


