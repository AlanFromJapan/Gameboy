BIN = /home/alan/Git/gbdk-n/bin
OBJ_DIR=./obj

OBJ_FILES = $(OBJ_DIR)/Map_Intro.rel \
			$(OBJ_DIR)/my_lib01.rel \
			$(OBJ_DIR)/main.rel

build: $(OBJ_FILES)
	$(BIN)/gbdk-n-link.sh $(OBJ_DIR)/*.rel  -o $(OBJ_DIR)/MysticSnake-n.ihx 
	$(BIN)/gbdk-n-make-rom.sh $(OBJ_DIR)/MysticSnake-n.ihx MysticSnake-n.gb

$(OBJ_DIR)/%.rel : ./%.c
	mkdir -p $(OBJ_DIR)
	$(BIN)/gbdk-n-compile-4.sh $^ -o $(OBJ_DIR)/$^.rel

clean:
	rm -rf $(OBJ_DIR)
	rm -f *.gb

run:
	vba MysticSnake-n.gb