################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/src/widgets/tileview/lv_tileview.c 

OBJS += \
./Drivers/lvgl/src/widgets/tileview/lv_tileview.o 

C_DEPS += \
./Drivers/lvgl/src/widgets/tileview/lv_tileview.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/src/widgets/tileview/%.o Drivers/lvgl/src/widgets/tileview/%.su Drivers/lvgl/src/widgets/tileview/%.cyclo: ../Drivers/lvgl/src/widgets/tileview/%.c Drivers/lvgl/src/widgets/tileview/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I"E:/STM32CubeIDE/F446RET6 Streamdeck/Drivers" -I"E:/STM32CubeIDE/F446RET6 Streamdeck/Drivers/lvgl/src/drivers/display/st7789" -I"E:/STM32CubeIDE/F446RET6 Streamdeck/Drivers/lvgl" -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I"E:/STM32CubeIDE/F446RET6 Streamdeck/Drivers" -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-src-2f-widgets-2f-tileview

clean-Drivers-2f-lvgl-2f-src-2f-widgets-2f-tileview:
	-$(RM) ./Drivers/lvgl/src/widgets/tileview/lv_tileview.cyclo ./Drivers/lvgl/src/widgets/tileview/lv_tileview.d ./Drivers/lvgl/src/widgets/tileview/lv_tileview.o ./Drivers/lvgl/src/widgets/tileview/lv_tileview.su

.PHONY: clean-Drivers-2f-lvgl-2f-src-2f-widgets-2f-tileview

