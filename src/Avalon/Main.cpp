#include <ctime>
#include <Locator.h>
#include <Game.h>
#include <DesktopFileSystem.h>

using namespace av;

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	Locator::Provide(new DesktopFileSystem());

	Game(Locator::GetFileSystem().GetConfiguration()).Run();
}
