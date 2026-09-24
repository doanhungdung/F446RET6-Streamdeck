################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/lvgl/src/libs/lz4/lz4.c 

OBJS += \
./Drivers/lvgl/lvgl/src/libs/lz4/lz4.o 

C_DEPS += \
./Drivers/lvgl/lvgl/src/libs/lz4/lz4.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/lvgl/src/libs/lz4/%.o Drivers/lvgl/lvgl/src/libs/lz4/%.su Drivers/lvgl/lvgl/src/libs/lz4/%.cyclo: ../Drivers/lvgl/lvgl/src/libs/lz4/%.c Drivers/lvgl/lvgl/src/libs/lz4/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I"E:/STM32CubeIDE/F446RET6 Streamdeck/Drivers" -I"E:/STM32CubeIDE/F446RET6 Streamdeck/Drivers/lvgl" -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I"E:/STM32CubeIDE/F446RET6 Streamdeck/Drivers" -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-lvgl-2f-src-2f-libs-2f-lz4

clean-Drivers-2f-lvgl-2f-lvgl-2f-src-2f-libs-2f-lz4:
	-$(RM) ./Drivers/lvgl/lvgl/src/libs/lz4/lz4.cyclo ./Drivers/lvgl/lvgl/src/libs/lz4/lz4.d ./Drivers/lvgl/lvgl/src/libs/lz4/lz4.o ./Drivers/lvgl/lvgl/src/libs/lz4/lz4.su

.PHONY: clean-Drivers-2f-lvgl-2f-lvgl-2f-src-2f-libs-2f-lz4

