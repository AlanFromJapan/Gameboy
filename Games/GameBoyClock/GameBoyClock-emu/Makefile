# ROM name
ROM_NAME = gbclock-emu
ROM_LABEL = "CLOCKEMU"
ROM_EXT = gb

# Bins and libs
BIN = /home/alan/Git/gbdk-n/bin
OBJ_DIR=./obj
FLASHER = /home/alan/Git/Gameboy/ems-flasher


OBJ_FILES = $(OBJ_DIR)/my_lib01.rel \
			$(OBJ_DIR)/Map_Screen1.rel \
			$(OBJ_DIR)/main.rel

build: $(OBJ_FILES)
	@echo "\e[36mLinking .rel files to .ihx file...\e[0m"
	$(BIN)/gbdk-n-link.sh $(OBJ_DIR)/*.rel  -o $(OBJ_DIR)/$(ROM_NAME).ihx 
#	@echo "\e[36mConvert .ihx file to final .gbc (see -yc flag!) ...\e[0m"
#	$(BIN)/gbdk-n-make-rom-4.sh -yc -yn $(ROM_LABEL) $(OBJ_DIR)/$(ROM_NAME).ihx $(ROM_NAME).$(ROM_EXT)
	$(BIN)/gbdk-n-make-rom.sh -yn $(ROM_LABEL) $(OBJ_DIR)/$(ROM_NAME).ihx $(ROM_NAME).$(ROM_EXT)
	@echo "\e[36mFinished!\e[0m"

$(OBJ_DIR)/%.rel : ./%.c
	@echo "\e[36mBuilding $^\e[0m"
	mkdir -p $(OBJ_DIR)
	$(BIN)/gbdk-n-compile.sh $^ -o $(OBJ_DIR)/$^.rel

clean:
	@echo "\e[31mCleaning up old files\e[0m"
	rm -rf $(OBJ_DIR)
	rm -f *.$(ROM_EXT)

run:
	@echo "\e[1;32mRun !!\e[0m"
	vba $(ROM_NAME).$(ROM_EXT)
#	wine ../../bgb/bgb.exe ./$(ROM_NAME).$(ROM_EXT)

run2:
	@echo "\e[1;32mRun 2 instances connected with BGB !!\e[0m"
	wine ../../../bgb/bgb.exe ./$(ROM_NAME).$(ROM_EXT) -listen 55555 &
	sleep 2s
#	connect BGB need to have the IP of the host also (otherwise can't connect on Linux)
	wine ../../../bgb/bgb.exe ./$(ROM_NAME).$(ROM_EXT) -connect 127.0.0.1:55555 &

full: clean build run

flash:
	sudo $(FLASHER)/ems-flasher --bank 1 --verbose --write $(ROM_NAME).$(ROM_EXT)
