################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LDS_SRCS += \
../linker.lds 

ASM_SRCS += \
../dmactest.asm 

OBJS += \
./dmactest.o 

ASM_DEPS += \
./dmactest.d 


# Each subdirectory must supply rules for building sources it contributes
dmactest.o: ../dmactest.asm
	@echo '正在构建文件： $<'
	@echo '正在调用： Compiler'
	"E:\ECS\ECS\ide\\..\hxdsp1042\hxcc\bin\occ" -c -g -O0 -keep -MMD -MP -MF"dmactest.d" -MT"dmactest.d" -o "$@" "$<"
	@echo '已结束构建： $<'
	@echo ' '

%.out: ./%.o
	@echo '正在构建文件： $<'
	@echo '正在调用： Linker'
	"E:\ECS\ECS\ide\\..\hxdsp1042\hxcc\bin\binutils\eld.exe" "$<" -Map xxxmap --cref --no-whole-archive -T../linker.lds -o "$@"
	@echo '已结束构建： $<'
	@echo ' '


