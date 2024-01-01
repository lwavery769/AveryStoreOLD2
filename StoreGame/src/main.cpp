#include "Sandbox.h"

int main()
{
	ALStore::Log::Init();
	AL_CORE_INFO("Loger init");
	Sandbox Sandbox;
	Sandbox.init();
	Sandbox.run();
	return 0;
}
