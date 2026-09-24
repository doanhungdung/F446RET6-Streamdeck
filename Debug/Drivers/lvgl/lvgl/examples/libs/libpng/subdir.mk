################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/lvgl/examples/libs/libpng/img_png_demo.c \
../Drivers/lvgl/lvgl/examples/libs/libpng/lv_example_libpng_1.c 

OBJS += \
./Drivers/lvgl/lvgl/examples/libs/libpng/img_png_demo.o \
./Drivers/lvgl/lvgl/examples/libs/libpng/lv_example_libpng_1.o 

C_DEPS += \
./Drivers/lvgl/lvgl/examples/libs/libpng/img_png_demo.d \
./Drivers/lvgl/lvgl/examples/libs/libpng/lv_example_libpng_1.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/lvgl/examples/libs/libpng/%.o Drivers/lvgl/lvgl/examples/libs/libpng/%.su Drivers/lvgl/lvgl/examples/libs/libpng/%.cyclo: ../Drivers/lvgl/lvgl/examples/libs/libpng/%.c Drivers/lvgl/lvgl/examples/libs/libpng/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I"E:/STM32CubeIDE/F446RET6 Streamdeck/Drivers" -I"E:/STM32CubeIDE/F446RET6 Streamdeck/Drivers/lvgl" -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I"E:/STM32CubeIDE/F446RET6 Streamdeck/Drivers" -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-lvgl-2f-examples-2f-libs-2f-libpng

clean-Drivers-2f-lvgl-2f-lvgl-2f-examples-2f-libs-2f-libpng:
	-$(RM) ./Drivers/lvgl/lvgl/examples/libs/libpng/img_png_demo.cyclo ./Drivers/lvgl/lvgl/examples/libs/libpng/img_png_demo.d ./Drivers/lvgl/lvgl/examples/libs/libpng/img_png_demo.o ./Drivers/lvgl/lvgl/examples/libs/libpng/img_png_demo.su ./Drivers/lvgl/lvgl/examples/libs/libpng/lv_example_libpng_1.cyclo ./Drivers/lvgl/lvgl/examples/libs/libpng/lv_example_libpng_1.d ./Drivers/lvgl/lvgl/examples/libs/libpng/lv_example_libpng_1.o ./Drivers/lvgl/lvgl/examples/libs/libpng/lv_example_libpng_1.su

.PHONY: clean-Drivers-2f-lvgl-2f-lvgl-2f-examples-2f-libs-2f-libpng

