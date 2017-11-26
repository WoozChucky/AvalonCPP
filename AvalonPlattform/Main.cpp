#include "Game.hpp"

int main() {
	srand(time(nullptr));
	av::Game(800, 600).Run();
}
