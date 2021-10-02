################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:\Users\Hsuyaa\eclipse\cpp-2021-03\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.8.3\libraries\Wire\src\utility\twi.c 

C_DEPS += \
.\libraries\Wire\src\utility\twi.c.d 

LINK_OBJ += \
.\libraries\Wire\src\utility\twi.c.o 


# Each subdirectory must supply rules for building sources it contributes
libraries\Wire\src\utility\twi.c.o: C:\Users\Hsuyaa\eclipse\cpp-2021-03\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.8.3\libraries\Wire\src\utility\twi.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"C:\Users\Hsuyaa\eclipse\cpp-2021-03\eclipse\arduinoPlugin\packages\arduino\tools\avr-gcc\7.3.0-atmel3.6.1-arduino7/bin/avr-gcc" -c -g -Os -Wall -Wextra -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10812 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Users\Hsuyaa\eclipse\cpp-2021-03\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.8.3\cores\arduino" -I"C:\Users\Hsuyaa\eclipse\cpp-2021-03\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.8.3\variants\mega" -I"C:\Users\Hsuyaa\Documents\Arduino\libraries\TFT_HX8357-0.27" -I"C:\Users\Hsuyaa\eclipse\cpp-2021-03\eclipse\arduinoPlugin\libraries\SD\1.2.4\src" -I"C:\Users\Hsuyaa\eclipse\cpp-2021-03\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.8.3\libraries\SPI\src" -I"C:\Users\Hsuyaa\Documents\Arduino\libraries\TMRpcm-1.1.0" -I"C:\Users\Hsuyaa\Documents\Arduino\libraries\ArduinoSTL-master\src" -I"C:\Users\Hsuyaa\Documents\Arduino\libraries\ds3231-master" -I"C:\Users\Hsuyaa\eclipse\cpp-2021-03\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.8.3\libraries\Wire\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 "$<"   -o "$@"
	@echo 'Finished building: $<'
	@echo ' '


