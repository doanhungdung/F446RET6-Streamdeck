################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_buf_vglite.c \
../Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite.c \
../Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_arc.c \
../Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_border.c \
../Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_fill.c \
../Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_img.c \
../Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_label.c \
../Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_layer.c \
../Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_line.c \
../Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_triangle.c \
../Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_vglite_buf.c \
../Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_vglite_matrix.c \
../Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_vglite_path.c \
../Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_vglite_utils.c 

OBJS += \
./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_buf_vglite.o \
./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite.o \
./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_arc.o \
./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_border.o \
./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_fill.o \
./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_img.o \
./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_label.o \
./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_layer.o \
./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_line.o \
./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_triangle.o \
./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_vglite_buf.o \
./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_vglite_matrix.o \
./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_vglite_path.o \
./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_vglite_utils.o 

C_DEPS += \
./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_buf_vglite.d \
./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite.d \
./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_arc.d \
./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_border.d \
./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_fill.d \
./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_img.d \
./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_label.d \
./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_layer.d \
./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_line.d \
./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_triangle.d \
./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_vglite_buf.d \
./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_vglite_matrix.d \
./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_vglite_path.d \
./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_vglite_utils.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/lvgl/src/draw/nxp/vglite/%.o Drivers/lvgl/lvgl/src/draw/nxp/vglite/%.su Drivers/lvgl/lvgl/src/draw/nxp/vglite/%.cyclo: ../Drivers/lvgl/lvgl/src/draw/nxp/vglite/%.c Drivers/lvgl/lvgl/src/draw/nxp/vglite/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I"E:/STM32CubeIDE/F446RET6 Streamdeck/Drivers" -I"E:/STM32CubeIDE/F446RET6 Streamdeck/Drivers/lvgl" -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I"E:/STM32CubeIDE/F446RET6 Streamdeck/Drivers" -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-lvgl-2f-src-2f-draw-2f-nxp-2f-vglite

clean-Drivers-2f-lvgl-2f-lvgl-2f-src-2f-draw-2f-nxp-2f-vglite:
	-$(RM) ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_buf_vglite.cyclo ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_buf_vglite.d ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_buf_vglite.o ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_buf_vglite.su ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite.cyclo ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite.d ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite.o ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite.su ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_arc.cyclo ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_arc.d ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_arc.o ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_arc.su ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_border.cyclo ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_border.d ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_border.o ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_border.su ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_fill.cyclo ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_fill.d ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_fill.o ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_fill.su ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_img.cyclo ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_img.d ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_img.o ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_img.su ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_label.cyclo ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_label.d ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_label.o ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_label.su ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_layer.cyclo ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_layer.d ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_layer.o ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_layer.su ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_line.cyclo ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_line.d ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_line.o ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_line.su ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_triangle.cyclo ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_triangle.d ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_triangle.o ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_triangle.su ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_vglite_buf.cyclo ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_vglite_buf.d ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_vglite_buf.o ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_vglite_buf.su ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_vglite_matrix.cyclo ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_vglite_matrix.d ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_vglite_matrix.o ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_vglite_matrix.su ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_vglite_path.cyclo ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_vglite_path.d ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_vglite_path.o ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_vglite_path.su ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_vglite_utils.cyclo ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_vglite_utils.d ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_vglite_utils.o ./Drivers/lvgl/lvgl/src/draw/nxp/vglite/lv_vglite_utils.su

.PHONY: clean-Drivers-2f-lvgl-2f-lvgl-2f-src-2f-draw-2f-nxp-2f-vglite

