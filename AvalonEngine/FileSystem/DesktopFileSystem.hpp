#pragma once

#include "FileSystem.hpp"

namespace av
{

    class DesktopFileSystem : public FileSystem
    {
    public:
        DesktopFileSystem();
        fs::Configuration GetConfiguration() override;
        void SaveConfiguration(fs::Configuration& l_cfg) override;
    private:
	    static bool FileExists(std::string filename);
		void GenerateDefaultConfiguration() const;

    };

}