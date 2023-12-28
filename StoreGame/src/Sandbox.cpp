#include <engine.h>
#include "core\Log.h"
int main(int argc, char** argv)
{
	ALStore::Log::Init();
	AL_CORE_INFO("Loger init");

	return 0;
} 