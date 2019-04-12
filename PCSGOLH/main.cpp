#include <Windows.h>
#include <thread>
#include <chrono>
#include <string>
#include "sdk.hpp"
#include "loader.hpp"
#include "interfaces.h"
bool unload_flag = false;

DWORD WINAPI load(LPVOID base)
{
	AllocConsole();
	//freopen("CONOUT$", "w", stdout);
	freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

	SetConsoleTitleA("[PCSGOLH] console: ");
	Loader::initialize();

	std::cout << ">";
	std::string str;
	while (!unload_flag)
	{
		std::getline(std::cin, str);
		luaL_dostring(LuaState::pLuaState, str.c_str());
		std::cout << ">";
	}
	
	Logger::append(Logger::kLogType::NORMAL, "Unload Interfaces...\n");
	Interfaces::unload();

	Logger::append(Logger::kLogType::NORMAL, "Unload LuaState...\n");
	LuaState::unload();

	Logger::append(Logger::kLogType::NORMAL, "Unload Console...\n");
	fclose((FILE*)stdin);
	fclose((FILE*)stdout);
	FreeConsole();

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	FreeLibraryAndExitThread(static_cast<HMODULE>(base), 1);
	return TRUE;
}

BOOL APIENTRY DllMain(_In_ HINSTANCE hDll, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	/*
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hDll);
		HANDLE cheat_thread = CreateThread(nullptr, NULL, load, hDll, NULL, nullptr);
		if (!cheat_thread)
			return 0;

		CloseHandle(cheat_thread);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	*/
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hDll);
		HANDLE cheat_thread = CreateThread(nullptr, NULL, load, hDll, NULL, nullptr);
		if (!cheat_thread)
			return 0;

		CloseHandle(cheat_thread);
	}
	else if (ul_reason_for_call == DLL_PROCESS_DETACH) {
		return FALSE;
	}
	return TRUE;
}