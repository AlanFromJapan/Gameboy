# ROM name
ROM_NAME = MysticSnake-n.gb

# Bins and libs
BIN = /home/alan/Git/gbdk-n/bin
OBJ_DIR=./obj
FLASHER = /home/alan/Git/Gameboy/ems-flasher


OBJ_FILES = $(OBJ_DIR)/Map_Intro.rel \
			$(OBJ_DIR)/Map_Room1.rel \
			$(OBJ_DIR)/my_lib01.rel \
			$(OBJ_DIR)/transitions.rel \
			$(OBJ_DIR)/main.rel

build: $(OBJ_FILES)
	$(BIN)/gbdk-n-link.sh $(OBJ_DIR)/*.rel  -o $(OBJ_DIR)/MysticSnake-n.ihx 
	$(BIN)/gbdk-n-make-rom.sh $(OBJ_DIR)/MysticSnake-n.ihx $(ROM_NAME)

$(OBJ_DIR)/%.rel : ./%.c
	mkdir -p $(OBJ_DIR)
	$(BIN)/gbdk-n-compile-4.sh $^ -o $(OBJ_DIR)/$^.rel

clean:
	rm -rf $(OBJ_DIR)
	rm -f *.gb

run:
#	vba $(ROM_NAME)
	wine ../../bgb/bgb.exe ./$(ROM_NAME)

full: clean build run

flash:
	sudo $(FLASHER)/ems-flasher --bank 1 --verbose --write $(ROM_NAME)