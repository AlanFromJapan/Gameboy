# ROM name
ROM_NAME = justasnake
ROM_LABEL = "Just a Snake"

# Bins and libs
BIN = /home/alan/Git/gbdk-n/bin
OBJ_DIR=./obj
FLASHER = /home/alan/Git/Gameboy/ems-flasher


OBJ_FILES = $(OBJ_DIR)/Map_SplashScreen.rel \
			$(OBJ_DIR)/window.rel \
			$(OBJ_DIR)/Map_Arene.rel \
			$(OBJ_DIR)/Map_Arene2.rel \
			$(OBJ_DIR)/Map_Arene3.rel \
			$(OBJ_DIR)/Map_Arene4.rel \
			$(OBJ_DIR)/Map_Arene5.rel \
			$(OBJ_DIR)/Map_Arene6.rel \
			$(OBJ_DIR)/Map_Arene7.rel \
			$(OBJ_DIR)/Map_Arene8.rel \
			$(OBJ_DIR)/Map_Arene9.rel \
			$(OBJ_DIR)/Map_Arene10.rel \
			$(OBJ_DIR)/Map_About.rel \
			$(OBJ_DIR)/transition.rel \
			$(OBJ_DIR)/my_lib01.rel \
			$(OBJ_DIR)/main.rel

build: $(OBJ_FILES)
	@echo "\e[36mLinking .rel files to .ihx file...\e[0m"
	$(BIN)/gbdk-n-link-4.sh $(OBJ_DIR)/*.rel  -o $(OBJ_DIR)/$(ROM_NAME).ihx 
	@echo "\e[36mConvert .ihx file to final .gb ...\e[0m"
	$(BIN)/gbdk-n-make-rom-4.sh -yn $(ROM_LABEL) $(OBJ_DIR)/$(ROM_NAME).ihx $(ROM_NAME).gb
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
#	vba $(ROM_NAME).gb
	wine ../../bgb/bgb.exe ./$(ROM_NAME).gb

full: clean build run

flash:
	sudo $(FLASHER)/ems-flasher --bank 1 --verbose --write $(ROM_NAME).gb
