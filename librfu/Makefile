include $(DEVKITARM)/base_tools
export CPP := $(PREFIX)cpp
export AR := $(PREFIX)ar
export AS := $(PREFIX)as

ifeq ($(OS),Windows_NT)
EXE := .exe
else
EXE :=
endif

CC1 := ../agbcc
CFLAGS := -mthumb-interwork -O2

CPPFLAGS := -I ../ginclude -I ../agbcc_src/libc/include -nostdinc -undef
ASFLAGS := -mcpu=arm7tdmi
ARFLAGS := rc

C_SRCS := librfu_rfu.c librfu_stwi.c
C_OBJS := $(C_SRCS:%.c=%.o)

ASM_SRCS := librfu_intr.s librfu.s
ASM_OBJS := $(ASM_SRCS:%.s=%.o)

ALL_OBJS := $(C_OBJS) $(ASM_OBJS)

LIB := librfu.a

.PHONY: all clean $(LIB)

all: $(LIB)

clean:
	rm -f $(LIB) $(C_SRCS:%.c=%.i) $(C_SRCS:%.c=%.s) $(ALL_OBJS)

$(LIB): $(ALL_OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(C_OBJS): %.o: %.c
	@$(CPP) $(CPPFLAGS) $< -o $*.i
	@$(CC1) $(CFLAGS) -o $*.s $*.i
	@echo -e ".text\n\t.align\t2, 0\n" >> $*.s
	$(AS) $(ASFLAGS) -o $@ $*.s

$(ASM_OBJS): %.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<
