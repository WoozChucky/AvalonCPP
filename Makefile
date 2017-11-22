#Set all the compilation flags
OS := $(shell uname)
CC=g++ -std=c++14
ENGINE_PATH=AvalonEngine
PLATTFORM_PATH=AvalonPlattform
INCLUDE_ENGINE=-I $(ENGINE_PATH)
BUILD_DIR=Build/$(OS)
LINK_LIBARIES=-lsfml-graphics -lsfml-window -lsfml-system

output: Main.o Game.o GameState.o Player.o Enemy.o Button.o MenuState.o
	g++ -std=c++14 Main.o Game.o GameState.o Player.o Enemy.o Button.o MenuState.o -o output $(LINK_LIBARIES)
	mkdir -p $(BUILD_DIR)
	mv *.o $(BUILD_DIR)
	mv output $(BUILD_DIR)

Main.o: $(PLATTFORM_PATH)/Main.cpp $(ENGINE_PATH)/States/GameState.hpp
	$(CC) $(INCLUDE_ENGINE) -c $(PLATTFORM_PATH)/Main.cpp

Game.o: $(PLATTFORM_PATH)/Game.cpp $(PLATTFORM_PATH)/Game.hpp
	$(CC) $(INCLUDE_ENGINE) -c $(PLATTFORM_PATH)/Game.cpp 

GameState.o: $(ENGINE_PATH)/States/GameState.cpp $(ENGINE_PATH)/States/GameState.hpp
	$(CC) $(INCLUDE_ENGINE) -c $(ENGINE_PATH)/States/GameState.cpp

Player.o: $(ENGINE_PATH)/Entities/Player.cpp $(ENGINE_PATH)/Entities/Player.hpp
	$(CC) $(INCLUDE_ENGINE) -c $(ENGINE_PATH)/Entities/Player.cpp

Enemy.o: $(ENGINE_PATH)/Entities/Enemy.cpp $(ENGINE_PATH)/Entities/Enemy.hpp
	$(CC) $(INCLUDE_ENGINE) -c $(ENGINE_PATH)/Entities/Enemy.cpp

MenuState.o: $(ENGINE_PATH)/States/MenuState.cpp $(ENGINE_PATH)/States/MenuState.hpp
	$(CC) $(INCLUDE_ENGINE)/States -c $(ENGINE_PATH)/States/MenuState.cpp

Button.o: $(ENGINE_PATH)/UI/Button.cpp $(ENGINE_PATH)/UI/Button.hpp
	$(CC) $(INCLUDE_ENGINE)/UI -c $(ENGINE_PATH)/UI/Button.cpp

clean:
	rm *.o
	rm $(BUILD_DIR)/*.o $(BUILD_DIR)/output
run:
	./$(BUILD_DIR)/output