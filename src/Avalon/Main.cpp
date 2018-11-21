#define _CRTDBG_MAP_ALLOC
#include <cstdlib>  
#include <crtdbg.h>  

#include <ctime>
#include <Locator.h>
#include <Game.h>
#include <DesktopFileSystem.h>

using namespace av;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	srand(static_cast<unsigned int>(time(nullptr)));

	Locator::Provide(new DesktopFileSystem());

	Game(Locator::GetFileSystem().GetConfiguration()).Run();

	_CrtDumpMemoryLeaks();
}
