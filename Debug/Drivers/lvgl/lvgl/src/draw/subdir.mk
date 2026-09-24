################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/lvgl/src/draw/lv_draw.c \
../Drivers/lvgl/lvgl/src/draw/lv_draw_arc.c \
../Drivers/lvgl/lvgl/src/draw/lv_draw_buf.c \
../Drivers/lvgl/lvgl/src/draw/lv_draw_image.c \
../Drivers/lvgl/lvgl/src/draw/lv_draw_label.c \
../Drivers/lvgl/lvgl/src/draw/lv_draw_line.c \
../Drivers/lvgl/lvgl/src/draw/lv_draw_mask.c \
../Drivers/lvgl/lvgl/src/draw/lv_draw_rect.c \
../Drivers/lvgl/lvgl/src/draw/lv_draw_triangle.c \
../Drivers/lvgl/lvgl/src/draw/lv_draw_vector.c \
../Drivers/lvgl/lvgl/src/draw/lv_image_decoder.c 

OBJS += \
./Drivers/lvgl/lvgl/src/draw/lv_draw.o \
./Drivers/lvgl/lvgl/src/draw/lv_draw_arc.o \
./Drivers/lvgl/lvgl/src/draw/lv_draw_buf.o \
./Drivers/lvgl/lvgl/src/draw/lv_draw_image.o \
./Drivers/lvgl/lvgl/src/draw/lv_draw_label.o \
./Drivers/lvgl/lvgl/src/draw/lv_draw_line.o \
./Drivers/lvgl/lvgl/src/draw/lv_draw_mask.o \
./Drivers/lvgl/lvgl/src/draw/lv_draw_rect.o \
./Drivers/lvgl/lvgl/src/draw/lv_draw_triangle.o \
./Drivers/lvgl/lvgl/src/draw/lv_draw_vector.o \
./Drivers/lvgl/lvgl/src/draw/lv_image_decoder.o 

C_DEPS += \
./Drivers/lvgl/lvgl/src/draw/lv_draw.d \
./Drivers/lvgl/lvgl/src/draw/lv_draw_arc.d \
./Drivers/lvgl/lvgl/src/draw/lv_draw_buf.d \
./Drivers/lvgl/lvgl/src/draw/lv_draw_image.d \
./Drivers/lvgl/lvgl/src/draw/lv_draw_label.d \
./Drivers/lvgl/lvgl/src/draw/lv_draw_line.d \
./Drivers/lvgl/lvgl/src/draw/lv_draw_mask.d \
./Drivers/lvgl/lvgl/src/draw/lv_draw_rect.d \
./Drivers/lvgl/lvgl/src/draw/lv_draw_triangle.d \
./Drivers/lvgl/lvgl/src/draw/lv_draw_vector.d \
./Drivers/lvgl/lvgl/src/draw/lv_image_decoder.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/lvgl/src/draw/%.o Drivers/lvgl/lvgl/src/draw/%.su Drivers/lvgl/lvgl/src/draw/%.cyclo: ../Drivers/lvgl/lvgl/src/draw/%.c Drivers/lvgl/lvgl/src/draw/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I"E:/STM32CubeIDE/F446RET6 Streamdeck/Drivers" -I"E:/STM32CubeIDE/F446RET6 Streamdeck/Drivers/lvgl" -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I"E:/STM32CubeIDE/F446RET6 Streamdeck/Drivers" -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-lvgl-2f-src-2f-draw

clean-Drivers-2f-lvgl-2f-lvgl-2f-src-2f-draw:
	-$(RM) ./Drivers/lvgl/lvgl/src/draw/lv_draw.cyclo ./Drivers/lvgl/lvgl/src/draw/lv_draw.d ./Drivers/lvgl/lvgl/src/draw/lv_draw.o ./Drivers/lvgl/lvgl/src/draw/lv_draw.su ./Drivers/lvgl/lvgl/src/draw/lv_draw_arc.cyclo ./Drivers/lvgl/lvgl/src/draw/lv_draw_arc.d ./Drivers/lvgl/lvgl/src/draw/lv_draw_arc.o ./Drivers/lvgl/lvgl/src/draw/lv_draw_arc.su ./Drivers/lvgl/lvgl/src/draw/lv_draw_buf.cyclo ./Drivers/lvgl/lvgl/src/draw/lv_draw_buf.d ./Drivers/lvgl/lvgl/src/draw/lv_draw_buf.o ./Drivers/lvgl/lvgl/src/draw/lv_draw_buf.su ./Drivers/lvgl/lvgl/src/draw/lv_draw_image.cyclo ./Drivers/lvgl/lvgl/src/draw/lv_draw_image.d ./Drivers/lvgl/lvgl/src/draw/lv_draw_image.o ./Drivers/lvgl/lvgl/src/draw/lv_draw_image.su ./Drivers/lvgl/lvgl/src/draw/lv_draw_label.cyclo ./Drivers/lvgl/lvgl/src/draw/lv_draw_label.d ./Drivers/lvgl/lvgl/src/draw/lv_draw_label.o ./Drivers/lvgl/lvgl/src/draw/lv_draw_label.su ./Drivers/lvgl/lvgl/src/draw/lv_draw_line.cyclo ./Drivers/lvgl/lvgl/src/draw/lv_draw_line.d ./Drivers/lvgl/lvgl/src/draw/lv_draw_line.o ./Drivers/lvgl/lvgl/src/draw/lv_draw_line.su ./Drivers/lvgl/lvgl/src/draw/lv_draw_mask.cyclo ./Drivers/lvgl/lvgl/src/draw/lv_draw_mask.d ./Drivers/lvgl/lvgl/src/draw/lv_draw_mask.o ./Drivers/lvgl/lvgl/src/draw/lv_draw_mask.su ./Drivers/lvgl/lvgl/src/draw/lv_draw_rect.cyclo ./Drivers/lvgl/lvgl/src/draw/lv_draw_rect.d ./Drivers/lvgl/lvgl/src/draw/lv_draw_rect.o ./Drivers/lvgl/lvgl/src/draw/lv_draw_rect.su ./Drivers/lvgl/lvgl/src/draw/lv_draw_triangle.cyclo ./Drivers/lvgl/lvgl/src/draw/lv_draw_triangle.d ./Drivers/lvgl/lvgl/src/draw/lv_draw_triangle.o ./Drivers/lvgl/lvgl/src/draw/lv_draw_triangle.su ./Drivers/lvgl/lvgl/src/draw/lv_draw_vector.cyclo ./Drivers/lvgl/lvgl/src/draw/lv_draw_vector.d ./Drivers/lvgl/lvgl/src/draw/lv_draw_vector.o ./Drivers/lvgl/lvgl/src/draw/lv_draw_vector.su ./Drivers/lvgl/lvgl/src/draw/lv_image_decoder.cyclo ./Drivers/lvgl/lvgl/src/draw/lv_image_decoder.d ./Drivers/lvgl/lvgl/src/draw/lv_image_decoder.o ./Drivers/lvgl/lvgl/src/draw/lv_image_decoder.su

.PHONY: clean-Drivers-2f-lvgl-2f-lvgl-2f-src-2f-draw

