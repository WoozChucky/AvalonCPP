#include "NullFileSystem.hpp"

av::NullFileSystem::NullFileSystem()
{
    
}

av::fs::Configuration av::NullFileSystem::GetConfiguration()
{
	const fs::Configuration read_cfg = {};	
	return read_cfg;
}

void av::NullFileSystem::SaveConfiguration(fs::Configuration& l_cfg)
{

}