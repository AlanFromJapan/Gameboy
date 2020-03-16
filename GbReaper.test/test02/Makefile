# ROM name
ROM_NAME = test02.gb

# Binaries
CC	= $(GBDKDIR)bin/lcc
FLASHER = /home/alan/Git/Gameboy/ems-flasher

# Files
ROM_FILE = $(ROM_NAME)
OBJ_FILES = main.o \
	my_lib01.o \
	Map_02.o 

all: $(ROM_FILE)

$(ROM_FILE): $(OBJ_FILES)
	$(CC) -o $@ $^

%.o : %.c
	$(CC) -c -o $@ $<


clean:
	rm *.o

cleaner: clean
	rm *.gb

flash:
	sudo $(FLASHER)/ems-flasher --bank 1 --verbose --write $(ROM_NAME)
