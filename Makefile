#Set all the compilation flags
OS := $(shell uname)
CC=g++ -std=c++14
ENGINE_PATH=AvalonEngine
INCLUDE_ENGINE=-I $(ENGINE_PATH)
BUILD_DIR=Build/$(OS)

output: Main.o Game.o GameState.o Player.o Enemy.o Button.o MenuState.o
	g++ -std=c++14 Main.o Game.o GameState.o Player.o Enemy.o Button.o MenuState.o -o output -lsfml-graphics -lsfml-window -lsfml-system
	mkdir -p $(BUILD_DIR)
	mv *.o $(BUILD_DIR)
	mv output $(BUILD_DIR)

Main.o: AvalonPlattform/Main.cpp AvalonEngine/GameState.hpp
	$(CC) $(INCLUDE_ENGINE) -c AvalonPlattform/Main.cpp

Game.o: AvalonPlattform/Game.cpp AvalonPlattform/Game.hpp
	g++ -std=c++14 -I AvalonEngine -c AvalonPlattform/Game.cpp 

GameState.o: AvalonEngine/GameState.cpp AvalonEngine/GameState.hpp
	g++ -std=c++14 -I AvalonEngine -c AvalonEngine/GameState.cpp

Player.o: AvalonEngine/Player.cpp AvalonEngine/Player.hpp
	g++ -std=c++14 -I AvalonEngine -c AvalonEngine/Player.cpp

Enemy.o: AvalonEngine/Enemy.cpp AvalonEngine/Enemy.hpp
	g++ -std=c++14 -I AvalonEngine -c AvalonEngine/Enemy.cpp

MenuState.o: AvalonEngine/States/MenuState.cpp AvalonEngine/States/MenuState.hpp
	g++ -std=c++14 -I AvalonEngine/States -c AvalonEngine/States/MenuState.cpp

Button.o: AvalonEngine/UI/Button.cpp AvalonEngine/UI/Button.hpp
	g++ -std=c++14 -I AvalonEngine/UI -c AvalonEngine/UI/Button.cpp

clean:
	rm *.o output
run:
	./$(BUILD_DIR)/output