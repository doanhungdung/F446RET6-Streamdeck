################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/src/drivers/sdl/lv_sdl_keyboard.c \
../Drivers/lvgl/src/drivers/sdl/lv_sdl_mouse.c \
../Drivers/lvgl/src/drivers/sdl/lv_sdl_mousewheel.c \
../Drivers/lvgl/src/drivers/sdl/lv_sdl_window.c 

OBJS += \
./Drivers/lvgl/src/drivers/sdl/lv_sdl_keyboard.o \
./Drivers/lvgl/src/drivers/sdl/lv_sdl_mouse.o \
./Drivers/lvgl/src/drivers/sdl/lv_sdl_mousewheel.o \
./Drivers/lvgl/src/drivers/sdl/lv_sdl_window.o 

C_DEPS += \
./Drivers/lvgl/src/drivers/sdl/lv_sdl_keyboard.d \
./Drivers/lvgl/src/drivers/sdl/lv_sdl_mouse.d \
./Drivers/lvgl/src/drivers/sdl/lv_sdl_mousewheel.d \
./Drivers/lvgl/src/drivers/sdl/lv_sdl_window.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/src/drivers/sdl/%.o Drivers/lvgl/src/drivers/sdl/%.su Drivers/lvgl/src/drivers/sdl/%.cyclo: ../Drivers/lvgl/src/drivers/sdl/%.c Drivers/lvgl/src/drivers/sdl/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I"E:/STM32CubeIDE/F446RET6 Streamdeck/Drivers" -I"E:/STM32CubeIDE/F446RET6 Streamdeck/Drivers/lvgl/src/drivers/display/st7789" -I"E:/STM32CubeIDE/F446RET6 Streamdeck/Drivers/lvgl" -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I"E:/STM32CubeIDE/F446RET6 Streamdeck/Drivers" -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-src-2f-drivers-2f-sdl

clean-Drivers-2f-lvgl-2f-src-2f-drivers-2f-sdl:
	-$(RM) ./Drivers/lvgl/src/drivers/sdl/lv_sdl_keyboard.cyclo ./Drivers/lvgl/src/drivers/sdl/lv_sdl_keyboard.d ./Drivers/lvgl/src/drivers/sdl/lv_sdl_keyboard.o ./Drivers/lvgl/src/drivers/sdl/lv_sdl_keyboard.su ./Drivers/lvgl/src/drivers/sdl/lv_sdl_mouse.cyclo ./Drivers/lvgl/src/drivers/sdl/lv_sdl_mouse.d ./Drivers/lvgl/src/drivers/sdl/lv_sdl_mouse.o ./Drivers/lvgl/src/drivers/sdl/lv_sdl_mouse.su ./Drivers/lvgl/src/drivers/sdl/lv_sdl_mousewheel.cyclo ./Drivers/lvgl/src/drivers/sdl/lv_sdl_mousewheel.d ./Drivers/lvgl/src/drivers/sdl/lv_sdl_mousewheel.o ./Drivers/lvgl/src/drivers/sdl/lv_sdl_mousewheel.su ./Drivers/lvgl/src/drivers/sdl/lv_sdl_window.cyclo ./Drivers/lvgl/src/drivers/sdl/lv_sdl_window.d ./Drivers/lvgl/src/drivers/sdl/lv_sdl_window.o ./Drivers/lvgl/src/drivers/sdl/lv_sdl_window.su

.PHONY: clean-Drivers-2f-lvgl-2f-src-2f-drivers-2f-sdl

