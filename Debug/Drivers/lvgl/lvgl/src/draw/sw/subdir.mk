################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw.c \
../Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_arc.c \
../Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_border.c \
../Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_box_shadow.c \
../Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_fill.c \
../Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_gradient.c \
../Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_img.c \
../Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_letter.c \
../Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_line.c \
../Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_mask.c \
../Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_mask_rect.c \
../Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_transform.c \
../Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_triangle.c \
../Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_vector.c 

OBJS += \
./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw.o \
./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_arc.o \
./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_border.o \
./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_box_shadow.o \
./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_fill.o \
./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_gradient.o \
./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_img.o \
./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_letter.o \
./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_line.o \
./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_mask.o \
./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_mask_rect.o \
./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_transform.o \
./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_triangle.o \
./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_vector.o 

C_DEPS += \
./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw.d \
./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_arc.d \
./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_border.d \
./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_box_shadow.d \
./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_fill.d \
./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_gradient.d \
./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_img.d \
./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_letter.d \
./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_line.d \
./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_mask.d \
./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_mask_rect.d \
./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_transform.d \
./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_triangle.d \
./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_vector.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/lvgl/src/draw/sw/%.o Drivers/lvgl/lvgl/src/draw/sw/%.su Drivers/lvgl/lvgl/src/draw/sw/%.cyclo: ../Drivers/lvgl/lvgl/src/draw/sw/%.c Drivers/lvgl/lvgl/src/draw/sw/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I"E:/STM32CubeIDE/F446RET6 Streamdeck/Drivers" -I"E:/STM32CubeIDE/F446RET6 Streamdeck/Drivers/lvgl" -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I"E:/STM32CubeIDE/F446RET6 Streamdeck/Drivers" -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-lvgl-2f-src-2f-draw-2f-sw

clean-Drivers-2f-lvgl-2f-lvgl-2f-src-2f-draw-2f-sw:
	-$(RM) ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw.cyclo ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw.d ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw.o ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw.su ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_arc.cyclo ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_arc.d ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_arc.o ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_arc.su ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_border.cyclo ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_border.d ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_border.o ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_border.su ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_box_shadow.cyclo ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_box_shadow.d ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_box_shadow.o ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_box_shadow.su ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_fill.cyclo ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_fill.d ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_fill.o ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_fill.su ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_gradient.cyclo ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_gradient.d ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_gradient.o ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_gradient.su ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_img.cyclo ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_img.d ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_img.o ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_img.su ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_letter.cyclo ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_letter.d ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_letter.o ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_letter.su ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_line.cyclo ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_line.d ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_line.o ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_line.su ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_mask.cyclo ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_mask.d ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_mask.o ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_mask.su ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_mask_rect.cyclo ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_mask_rect.d ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_mask_rect.o ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_mask_rect.su ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_transform.cyclo ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_transform.d ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_transform.o ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_transform.su ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_triangle.cyclo ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_triangle.d ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_triangle.o ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_triangle.su ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_vector.cyclo ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_vector.d ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_vector.o ./Drivers/lvgl/lvgl/src/draw/sw/lv_draw_sw_vector.su

.PHONY: clean-Drivers-2f-lvgl-2f-lvgl-2f-src-2f-draw-2f-sw

