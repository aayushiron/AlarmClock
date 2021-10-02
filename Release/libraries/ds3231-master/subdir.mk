################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:\Users\Hsuyaa\Documents\Arduino\libraries\ds3231-master\ds3231.cpp 

LINK_OBJ += \
.\libraries\ds3231-master\ds3231.cpp.o 

CPP_DEPS += \
.\libraries\ds3231-master\ds3231.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
libraries\ds3231-master\ds3231.cpp.o: C:\Users\Hsuyaa\Documents\Arduino\libraries\ds3231-master\ds3231.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Users\Hsuyaa\eclipse\cpp-2021-03\eclipse\arduinoPlugin\packages\arduino\tools\avr-gcc\7.3.0-atmel3.6.1-arduino7/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10812 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Users\Hsuyaa\eclipse\cpp-2021-03\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.8.3\cores\arduino" -I"C:\Users\Hsuyaa\eclipse\cpp-2021-03\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.8.3\variants\mega" -I"C:\Users\Hsuyaa\Documents\Arduino\libraries\TFT_HX8357-0.27" -I"C:\Users\Hsuyaa\eclipse\cpp-2021-03\eclipse\arduinoPlugin\libraries\SD\1.2.4\src" -I"C:\Users\Hsuyaa\eclipse\cpp-2021-03\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.8.3\libraries\SPI\src" -I"C:\Users\Hsuyaa\Documents\Arduino\libraries\TMRpcm-1.1.0" -I"C:\Users\Hsuyaa\Documents\Arduino\libraries\ArduinoSTL-master\src" -I"C:\Users\Hsuyaa\Documents\Arduino\libraries\ds3231-master" -I"C:\Users\Hsuyaa\eclipse\cpp-2021-03\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.8.3\libraries\Wire\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"   -o "$@"
	@echo 'Finished building: $<'
	@echo ' '


