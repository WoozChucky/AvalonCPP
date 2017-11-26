#include "Game.hpp"

int main() {
	srand(time(nullptr));
	av::Game(1920, 1080).Run();
}
