################################################################################
# �Զ����ɵ��ļ�����Ҫ�༭��
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
	@echo '���ڹ����ļ��� $<'
	@echo '���ڵ��ã� Compiler'
	"E:\ECS\ECS\ide\\..\hxdsp1042\hxcc\bin\occ" -c -g -O0 -keep -MMD -MP -MF"dmactest.d" -MT"dmactest.d" -o "$@" "$<"
	@echo '�ѽ��������� $<'
	@echo ' '

%.out: ./%.o
	@echo '���ڹ����ļ��� $<'
	@echo '���ڵ��ã� Linker'
	"E:\ECS\ECS\ide\\..\hxdsp1042\hxcc\bin\binutils\eld.exe" "$<" -Map xxxmap --cref --no-whole-archive -T../linker.lds -o "$@"
	@echo '�ѽ��������� $<'
	@echo ' '


