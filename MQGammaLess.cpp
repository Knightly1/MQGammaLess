#include <mq/Plugin.h>

PreSetup("MQGammaLess");
PLUGIN_VERSION(0.1);

#ifdef ROF2EMU
DETOUR_TRAMPOLINE_DEF(BOOL WINAPI, SetDeviceGammaRamp_Trampoline, (HDC hdc, LPVOID lpRamp))
static uintptr_t s_gammaRampAddress = 0;

int WINAPI SetDeviceGammaRamp_Hook(HDC hdc, LPVOID lpRamp)
{
	return 1;
}
#endif

PLUGIN_API void InitializePlugin()
{
	DebugSpewAlways("MQGammaLess::Initializing version %f", MQ2Version);
#ifdef ROF2EMU
	auto hGdi32 = GetModuleHandle("gdi32.dll");
	if (hGdi32)
	{
		s_gammaRampAddress = reinterpret_cast<uintptr_t>(GetProcAddress(hGdi32, "SetDeviceGammaRamp"));
	}

	if (s_gammaRampAddress != 0)
	{
		EzDetour(s_gammaRampAddress, SetDeviceGammaRamp_Hook, SetDeviceGammaRamp_Trampoline);
		WriteChatf("\ag[MQGammaLess]\ax Gamma protection enabled");
	}
#else
	DebugSpewAlways("MQGammaLess::Not enabled for this client");
#endif
}

PLUGIN_API void ShutdownPlugin()
{
	DebugSpewAlways("MQGammaLess::Shutting down");
#ifdef ROF2EMU
	if (s_gammaRampAddress != 0)
	{
		RemoveDetour(s_gammaRampAddress);
		s_gammaRampAddress = 0;
	}
#endif
}