################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/lvgl/examples/others/file_explorer/lv_example_file_explorer_1.c \
../Drivers/lvgl/lvgl/examples/others/file_explorer/lv_example_file_explorer_2.c \
../Drivers/lvgl/lvgl/examples/others/file_explorer/lv_example_file_explorer_3.c 

OBJS += \
./Drivers/lvgl/lvgl/examples/others/file_explorer/lv_example_file_explorer_1.o \
./Drivers/lvgl/lvgl/examples/others/file_explorer/lv_example_file_explorer_2.o \
./Drivers/lvgl/lvgl/examples/others/file_explorer/lv_example_file_explorer_3.o 

C_DEPS += \
./Drivers/lvgl/lvgl/examples/others/file_explorer/lv_example_file_explorer_1.d \
./Drivers/lvgl/lvgl/examples/others/file_explorer/lv_example_file_explorer_2.d \
./Drivers/lvgl/lvgl/examples/others/file_explorer/lv_example_file_explorer_3.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/lvgl/examples/others/file_explorer/%.o Drivers/lvgl/lvgl/examples/others/file_explorer/%.su Drivers/lvgl/lvgl/examples/others/file_explorer/%.cyclo: ../Drivers/lvgl/lvgl/examples/others/file_explorer/%.c Drivers/lvgl/lvgl/examples/others/file_explorer/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I"E:/STM32CubeIDE/F446RET6 Streamdeck/Drivers" -I"E:/STM32CubeIDE/F446RET6 Streamdeck/Drivers/lvgl" -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I"E:/STM32CubeIDE/F446RET6 Streamdeck/Drivers" -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-lvgl-2f-examples-2f-others-2f-file_explorer

clean-Drivers-2f-lvgl-2f-lvgl-2f-examples-2f-others-2f-file_explorer:
	-$(RM) ./Drivers/lvgl/lvgl/examples/others/file_explorer/lv_example_file_explorer_1.cyclo ./Drivers/lvgl/lvgl/examples/others/file_explorer/lv_example_file_explorer_1.d ./Drivers/lvgl/lvgl/examples/others/file_explorer/lv_example_file_explorer_1.o ./Drivers/lvgl/lvgl/examples/others/file_explorer/lv_example_file_explorer_1.su ./Drivers/lvgl/lvgl/examples/others/file_explorer/lv_example_file_explorer_2.cyclo ./Drivers/lvgl/lvgl/examples/others/file_explorer/lv_example_file_explorer_2.d ./Drivers/lvgl/lvgl/examples/others/file_explorer/lv_example_file_explorer_2.o ./Drivers/lvgl/lvgl/examples/others/file_explorer/lv_example_file_explorer_2.su ./Drivers/lvgl/lvgl/examples/others/file_explorer/lv_example_file_explorer_3.cyclo ./Drivers/lvgl/lvgl/examples/others/file_explorer/lv_example_file_explorer_3.d ./Drivers/lvgl/lvgl/examples/others/file_explorer/lv_example_file_explorer_3.o ./Drivers/lvgl/lvgl/examples/others/file_explorer/lv_example_file_explorer_3.su

.PHONY: clean-Drivers-2f-lvgl-2f-lvgl-2f-examples-2f-others-2f-file_explorer

