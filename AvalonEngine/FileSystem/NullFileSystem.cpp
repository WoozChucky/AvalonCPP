#include "NullFileSystem.hpp"

av::NullFileSystem::NullFileSystem()
{
    
}

av::fs::Configuration av::NullFileSystem::GetConfiguration()
{
	fs::Configuration read_cfg;	
	return read_cfg;
}

void av::NullFileSystem::SaveConfiguration(av::fs::Configuration& l_cfg)
{

}