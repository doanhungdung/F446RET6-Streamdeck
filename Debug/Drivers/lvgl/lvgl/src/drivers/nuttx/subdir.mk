################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_cache.c \
../Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_entry.c \
../Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_fbdev.c \
../Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_image_cache.c \
../Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_lcd.c \
../Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_libuv.c \
../Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_profiler.c \
../Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_touchscreen.c 

OBJS += \
./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_cache.o \
./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_entry.o \
./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_fbdev.o \
./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_image_cache.o \
./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_lcd.o \
./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_libuv.o \
./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_profiler.o \
./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_touchscreen.o 

C_DEPS += \
./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_cache.d \
./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_entry.d \
./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_fbdev.d \
./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_image_cache.d \
./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_lcd.d \
./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_libuv.d \
./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_profiler.d \
./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_touchscreen.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/lvgl/src/drivers/nuttx/%.o Drivers/lvgl/lvgl/src/drivers/nuttx/%.su Drivers/lvgl/lvgl/src/drivers/nuttx/%.cyclo: ../Drivers/lvgl/lvgl/src/drivers/nuttx/%.c Drivers/lvgl/lvgl/src/drivers/nuttx/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I"E:/STM32CubeIDE/F446RET6 Streamdeck/Drivers" -I"E:/STM32CubeIDE/F446RET6 Streamdeck/Drivers/lvgl" -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I"E:/STM32CubeIDE/F446RET6 Streamdeck/Drivers" -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-lvgl-2f-src-2f-drivers-2f-nuttx

clean-Drivers-2f-lvgl-2f-lvgl-2f-src-2f-drivers-2f-nuttx:
	-$(RM) ./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_cache.cyclo ./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_cache.d ./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_cache.o ./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_cache.su ./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_entry.cyclo ./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_entry.d ./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_entry.o ./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_entry.su ./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_fbdev.cyclo ./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_fbdev.d ./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_fbdev.o ./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_fbdev.su ./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_image_cache.cyclo ./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_image_cache.d ./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_image_cache.o ./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_image_cache.su ./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_lcd.cyclo ./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_lcd.d ./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_lcd.o ./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_lcd.su ./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_libuv.cyclo ./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_libuv.d ./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_libuv.o ./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_libuv.su ./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_profiler.cyclo ./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_profiler.d ./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_profiler.o ./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_profiler.su ./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_touchscreen.cyclo ./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_touchscreen.d ./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_touchscreen.o ./Drivers/lvgl/lvgl/src/drivers/nuttx/lv_nuttx_touchscreen.su

.PHONY: clean-Drivers-2f-lvgl-2f-lvgl-2f-src-2f-drivers-2f-nuttx

