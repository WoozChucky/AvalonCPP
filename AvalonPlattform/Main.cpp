#include "Game.hpp"

int main() {
	srand(time(nullptr));
	av::Game(1024, 768).Run();
}
