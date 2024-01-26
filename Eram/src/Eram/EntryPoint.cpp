#include "erpch.h"

#include "Eram/Core/Log.h"
#include "Eram/Core/Application.h"

#ifdef ER_PLATFORM_WINDOWS

int main()
{
	Eram::Log::Init();
	ER_INFO("Initialized Log");

	ER_PROFILE_BEGIN_SESSION("Eram", "EramProfile.json");
	Eram::Application application;
	ER_PROFILE_END_SESSION();
}

#endif