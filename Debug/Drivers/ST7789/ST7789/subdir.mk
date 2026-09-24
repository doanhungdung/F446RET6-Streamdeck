################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/ST7789/ST7789/fonts.c \
../Drivers/ST7789/ST7789/st7789.c 

OBJS += \
./Drivers/ST7789/ST7789/fonts.o \
./Drivers/ST7789/ST7789/st7789.o 

C_DEPS += \
./Drivers/ST7789/ST7789/fonts.d \
./Drivers/ST7789/ST7789/st7789.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/ST7789/ST7789/%.o Drivers/ST7789/ST7789/%.su Drivers/ST7789/ST7789/%.cyclo: ../Drivers/ST7789/ST7789/%.c Drivers/ST7789/ST7789/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"E:/STM32CubeIDE/TEST_WITH_LVGL/Drivers/lvgl" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-ST7789-2f-ST7789

clean-Drivers-2f-ST7789-2f-ST7789:
	-$(RM) ./Drivers/ST7789/ST7789/fonts.cyclo ./Drivers/ST7789/ST7789/fonts.d ./Drivers/ST7789/ST7789/fonts.o ./Drivers/ST7789/ST7789/fonts.su ./Drivers/ST7789/ST7789/st7789.cyclo ./Drivers/ST7789/ST7789/st7789.d ./Drivers/ST7789/ST7789/st7789.o ./Drivers/ST7789/ST7789/st7789.su

.PHONY: clean-Drivers-2f-ST7789-2f-ST7789

