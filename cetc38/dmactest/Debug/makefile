################################################################################
# 自动生成的文件。不要编辑！
################################################################################

-include ../makefile.init

RM := "E:\ECS\ECS\ide\\\utils\\rm" -f

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# 所有目标
all: dmactest.out

# 工具调用
dmactest.out: $(OBJS) $(LDS_SRCS)
	@echo '正在构建目标： $@'
	@echo '正在调用： Linker'
	"E:\ECS\ECS\ide\\..\hxdsp1042\hxcc\bin\binutils\eld.exe" $(OBJS) -Map xxxmap --cref --no-whole-archive -T$(LDS_SRCS) -o "dmactest.out"
	@echo '已结束构建目标： $@'
	@echo ' '

# 其他目标
clean:
	-$(RM) $(OBJS)$(ASM_DEPS)$(C_DEPS)$(EXECUTABLES)$(S_UPPER_DEPS) dmactest.out
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
