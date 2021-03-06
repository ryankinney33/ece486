TARGET=stm32FIR

OBJS  = $(TARGET).o ece486_fir.o ece486_biquad.o

INSTALLDIR = /usr/local/stmdev/


ARCH = STM32L476xx

CC=arm-none-eabi-gcc
LD=arm-none-eabi-ld
AS=arm-none-eabi-as
OBJCOPY=arm-none-eabi-objcopy

FIRDIR = ../FIR
IIRDIR = ../IIR
INCDIRS = -I$(INSTALLDIR)/include -I. -I$(FIRDIR) -I$(IIRDIR)
LIBDIRS = -L$(INSTALLDIR)/lib

LIBS=  -lece486_$(ARCH) -l$(ARCH) -lcmsis_dsp_$(ARCH)

LINKSCRIPT = $(INSTALLDIR)/lib/$(ARCH)_FLASH.ld

CFLAGS = -mcpu=cortex-m4 -mthumb -O3 -Wall  \
         -fomit-frame-pointer -fno-strict-aliasing -fdata-sections \
         -include stm32l4xx_hal_conf.h -DARM_MATH_CM4 -D$(ARCH) \
         -mfpu=fpv4-sp-d16 -mfloat-abi=softfp $(INCDIRS) \
         -fsingle-precision-constant -ffunction-sections

LDFLAGS = -u _printf_float \
	  -Wl,-T$(LINKSCRIPT) \
	  -static \
          -Wl,--gc-sections $(LIBDIRS)
.PHONY : all flash clean debug

all: $(TARGET) $(TARGET).bin

debug : CFLAGS += -DDEBUG -g -Og
debug : LDFLAGS += -Wl,-Map,$(TARGET).map

debug : all

$(TARGET): $(OBJS)
	$(CC)  -o $(TARGET) $(CFLAGS) $(LDFLAGS) $(OBJS) $(LIBS)

$(TARGET).bin: $(TARGET)
	$(OBJCOPY) -Obinary $(TARGET) $(TARGET).bin

flash: $(TARGET).bin
	st-flash write $(TARGET).bin 0x08000000

ece486_fir.o:
	$(CC)  -c -o ece486_fir.o $(FIRDIR)/ece486_fir.c -I$(FIRDIR) $(CFLAGS) $(LDFLAGS) $(LIBS)

ece486_biquad.o:
	$(CC)  -c -o ece486_biquad.o $(IIRDIR)/ece486_biquad.c -I$(IIRDIR) $(CFLAGS) $(LDFLAGS) $(LIBS)

clean:
	rm -f $(OBJS) stm32FIR stm32IIR *.bin *.map *.o
