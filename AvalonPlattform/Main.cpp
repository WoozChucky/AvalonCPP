#include "Locator.hpp"
#include "Audio/DesktopAudioPlayer.hpp"
#include "FileSystem/DesktopFileSystem.hpp"
#include "Logger/DesktopLogger.hpp"
#include "Game.hpp"
#include <cstdio>

int main() {
	srand(static_cast<unsigned int>(time(nullptr)));

	av::Locator::Initialize();
	av::Locator::Provide(new av::DesktopLogger());
	av::Locator::Provide(new av::DesktopAudioPlayer());
	av::Locator::Provide(new av::DesktopFileSystem());

	av::Game(av::Locator::GetFileSystem().GetConfiguration()).Run();
}
