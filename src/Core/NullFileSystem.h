#pragma once

#include "FileSystem.h"

namespace av
{

	class NullFileSystem : public FileSystem
	{
	public:
		NullFileSystem();
		fs::Configuration GetConfiguration() override { return fs::Configuration{ }; }
		void SaveConfiguration(fs::Configuration&) override {}
	};

}