//
// Created by Nuno Levezinho on 07/02/2018.
//

#include "NullFileSystem.h"

av::NullFileSystem::NullFileSystem() = default;

av::fs::Configuration av::NullFileSystem::GetConfiguration()
{
    const fs::Configuration read_cfg = {};
    return read_cfg;
}

void av::NullFileSystem::SaveConfiguration(fs::Configuration& l_cfg)
{

}