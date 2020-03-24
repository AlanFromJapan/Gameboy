BIN = /home/alan/Git/gbdk-n/bin
OBJ=./obj

build:
	mkdir -p $(OBJ)
	$(BIN)/gbdk-n-compile-4.sh Map_Intro.c -o $(OBJ)/Map_Intro.rel
	$(BIN)/gbdk-n-compile-4.sh my_lib01.c -o $(OBJ)/my_lib01.rel
	$(BIN)/gbdk-n-compile-4.sh main.c -o $(OBJ)/main.rel
	$(BIN)/gbdk-n-link.sh $(OBJ)/*.rel  -o $(OBJ)/MysticSnake-n.ihx 
	$(BIN)/gbdk-n-make-rom.sh $(OBJ)/MysticSnake-n.ihx MysticSnake-n.gb


clean:
	rm -rf $(OBJ)
	rm -f *.gb
