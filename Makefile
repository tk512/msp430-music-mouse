CC = msp430-gcc
CFLAGS = -Os -Wall -g -mmcu=msp430x2012

BIN = music-mouse.elf
OBJS = main.o music.o

all: music-mouse

music-mouse: $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(BIN) $(OBJS)
