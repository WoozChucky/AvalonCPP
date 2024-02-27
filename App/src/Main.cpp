#include <Avalon.h>

class AvalonApplication : public Avalon::Application
{
public:
	AvalonApplication()
	{
	}

	~AvalonApplication()
	{
	}

};

Avalon::Application* Avalon::CreateApplication()
{
	return new AvalonApplication();
}

