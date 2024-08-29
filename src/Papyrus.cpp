#include "Papyrus.h"
#include "Settings.h"


namespace Papyrus
{
	void OnConfigClose(RE::TESQuest*)
	{
		Settings::ReadSettings();
	}

	bool Register(RE::BSScript::IVirtualMachine* a_vm)
	{
		a_vm->RegisterFunction("OnConfigClose", "_CC_MCM", OnConfigClose);

		return true;
	}
}
