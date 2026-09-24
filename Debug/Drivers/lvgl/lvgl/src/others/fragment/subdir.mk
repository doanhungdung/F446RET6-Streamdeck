################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/lvgl/src/others/fragment/lv_fragment.c \
../Drivers/lvgl/lvgl/src/others/fragment/lv_fragment_manager.c 

OBJS += \
./Drivers/lvgl/lvgl/src/others/fragment/lv_fragment.o \
./Drivers/lvgl/lvgl/src/others/fragment/lv_fragment_manager.o 

C_DEPS += \
./Drivers/lvgl/lvgl/src/others/fragment/lv_fragment.d \
./Drivers/lvgl/lvgl/src/others/fragment/lv_fragment_manager.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/lvgl/src/others/fragment/%.o Drivers/lvgl/lvgl/src/others/fragment/%.su Drivers/lvgl/lvgl/src/others/fragment/%.cyclo: ../Drivers/lvgl/lvgl/src/others/fragment/%.c Drivers/lvgl/lvgl/src/others/fragment/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I"E:/STM32CubeIDE/F446RET6 Streamdeck/Drivers" -I"E:/STM32CubeIDE/F446RET6 Streamdeck/Drivers/lvgl" -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I"E:/STM32CubeIDE/F446RET6 Streamdeck/Drivers" -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-lvgl-2f-src-2f-others-2f-fragment

clean-Drivers-2f-lvgl-2f-lvgl-2f-src-2f-others-2f-fragment:
	-$(RM) ./Drivers/lvgl/lvgl/src/others/fragment/lv_fragment.cyclo ./Drivers/lvgl/lvgl/src/others/fragment/lv_fragment.d ./Drivers/lvgl/lvgl/src/others/fragment/lv_fragment.o ./Drivers/lvgl/lvgl/src/others/fragment/lv_fragment.su ./Drivers/lvgl/lvgl/src/others/fragment/lv_fragment_manager.cyclo ./Drivers/lvgl/lvgl/src/others/fragment/lv_fragment_manager.d ./Drivers/lvgl/lvgl/src/others/fragment/lv_fragment_manager.o ./Drivers/lvgl/lvgl/src/others/fragment/lv_fragment_manager.su

.PHONY: clean-Drivers-2f-lvgl-2f-lvgl-2f-src-2f-others-2f-fragment

