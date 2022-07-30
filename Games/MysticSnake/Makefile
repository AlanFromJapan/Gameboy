# ROM name
ROM_NAME = MysticSnake-n.gb

# Bins and libs
BIN = /home/alan/Git/gbdk-n/bin
OBJ_DIR=./obj
FLASHER = /home/alan/Git/Gameboy/ems-flasher


OBJ_FILES = $(OBJ_DIR)/Map_Intro.rel \
			$(OBJ_DIR)/Map_Room1.rel \
			$(OBJ_DIR)/Map_Title.rel \
			$(OBJ_DIR)/Map_BigRoom1.rel \
			$(OBJ_DIR)/Map_Outside1.rel \
			$(OBJ_DIR)/my_lib01.rel \
			$(OBJ_DIR)/graphics.rel \
			$(OBJ_DIR)/transitions.rel \
			$(OBJ_DIR)/tests.rel \
			$(OBJ_DIR)/inputs.rel \
			$(OBJ_DIR)/windows.rel \
			$(OBJ_DIR)/ai.rel \
			$(OBJ_DIR)/maps.rel \
			$(OBJ_DIR)/main.rel

build: $(OBJ_FILES)
	@echo "\e[36mLinking .rel files to .ihx file...\e[0m"
	$(BIN)/gbdk-n-link-4.sh $(OBJ_DIR)/*.rel  -o $(OBJ_DIR)/MysticSnake-n.ihx 
	@echo "\e[36mConvert .ihx file to final .gb ...\e[0m"
	$(BIN)/gbdk-n-make-rom-4.sh -yn "Mystic Snake" $(OBJ_DIR)/MysticSnake-n.ihx $(ROM_NAME)
	@echo "\e[36mFinished!\e[0m"

$(OBJ_DIR)/%.rel : ./%.c
	@echo "\e[36mBuilding $^\e[0m"
	mkdir -p $(OBJ_DIR)
	$(BIN)/gbdk-n-compile-4.sh $^ -o $(OBJ_DIR)/$^.rel

clean:
	@echo "\e[31mCleaning up old files\e[0m"
	rm -rf $(OBJ_DIR)
	rm -f *.gb

run:
	@echo "\e[1;32mRun !!\e[0m"
#	vba $(ROM_NAME)
	wine ../../bgb/bgb.exe ./$(ROM_NAME)

full: clean build run

flash:
	sudo $(FLASHER)/ems-flasher --bank 1 --verbose --write $(ROM_NAME)