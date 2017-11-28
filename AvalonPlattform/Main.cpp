#include "Locator.hpp"
#include "Audio/DesktopAudioPlayer.hpp"
#include "FileSystem/DesktopFileSystem.hpp"
#include "Game.hpp"
#include <cstdio>

#define LOG(input) std::cerr << #input << std::endl;

int main() {
	srand(time(nullptr));

	av::Locator::Initialize();
	av::Locator::Provide(new av::DesktopAudioPlayer());
	av::Locator::Provide(new av::DesktopFileSystem());

	av::Game(av::Locator::GetFileSystem().GetConfiguration()).Run();
}
