# makfile configuration
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/ 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c
AR              = msp430-elf-ar

all:wakedemo.elf


#additional rules for files
toy.elf: ${COMMON_OBJECTS} main.o wdt_handler.o stateMachines.o led.o buzzer.o buzzerStateMachines.o assyStates.o drawing.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd -lp2sw -lCircle -lShape

load: toy.elf
	msp430loader.sh $^

clean:
	 rm -f *.o *.elf
