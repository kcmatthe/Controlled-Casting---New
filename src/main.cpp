#include "PCH.h"
#include "Logger.h"
#include "skse/API.h"
#include "skse/SKSE.h"
#include "skse/Version.h"
#include <ShlObj.h>
#include "ControlledCasting.h"
#include "Papyrus.h"
#include "Settings.h"



using namespace RE::BSScript;
using namespace SKSE;
using namespace SKSE::log;
using namespace SKSE::stl;

namespace
{
	/**
	 * \brief Sink to capture SKSE events.
	 * \param event - Submitted event.
	 */
	void OnEvent(SKSE::MessagingInterface::Message* event)
	{
		// After all the ESM/ESL/ESP plugins are loaded.
		if (event->type == SKSE::MessagingInterface::kDataLoaded) {
			logger::info("Data Loaded");			
		}
		// When Skyrim starts, SKSE will begin by querying for SKSE plugins and then calling each plugin's SKSEPlugin_Load function.
		// Once all load functions are called this message is sent.
		else if (event->type == SKSE::MessagingInterface::kPostLoad) {
			logger::info("Post Load");
		}
		// The user has started a new game by selecting New Game at the main menu.
		else if (event->type == SKSE::MessagingInterface::kNewGame) {
			logger::info("New Game");
			Settings::ReadSettings();
		}
		// The user has loaded a saved game.
		else if (event->type == SKSE::MessagingInterface::kPostLoadGame) {
			logger::info("Post Load Game");
			//ControlledCasting::GetChargeTimeVHook::_UpdateGlobals();
			Settings::ReadSettings();
		}
		// Once all kPostLoad handlers have run, it will signal kPostPostLoad.
		else if (event->type == SKSE::MessagingInterface::kPostPostLoad) {
			logger::info("Post Post Load");
			
		}
	}

	void InitializePapyrus()
	{
		logger::info("Initializing Papyrus binding...");
		if (GetPapyrusInterface()->Register(Papyrus::Register)) {
			logger::info("Papyrus functions bound.");
		} else {
			logger::info("Failure to register Papyrus bindings.");
		}
	}

	/**
	 * \brief Returns the type of Skyrim that is running. Anniversary Edition, Special Edition, VR or Unknown.
	 * \return - Type of Skyrim that is running.
	 */
	static std::string_view GetRuntimeString()
	{
		switch (REL::Module::GetRuntime()) {
		case REL::Module::Runtime::AE:
			return "Anniversary Edition"sv;
		case REL::Module::Runtime::SE:
			return "Special Edition"sv;
		case REL::Module::Runtime::VR:
			return "VR"sv;
		default:;
		}
		return "Unknown"sv;
	}
}

extern "C" DLLEXPORT constinit auto SKSEPlugin_Version = []() {
	SKSE::PluginVersionData v;
	v.PluginVersion(Version::MAJOR);
	v.PluginName(Version::PROJECT);
	v.AuthorName("_kmatt_");
	v.UsesAddressLibrary(true);
	v.CompatibleVersions({ SKSE::RUNTIME_SSE_LATEST_AE });
	v.UsesNoStructs(true);

	return v;
}();

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Query(const SKSE::QueryInterface* a_skse, SKSE::PluginInfo* a_info)
{
	a_info->infoVersion = SKSE::PluginInfo::kVersion;
	a_info->name = Version::PROJECT.data();
	a_info->version = Version::MAJOR;

	if (a_skse->IsEditor()) {
		logger::critical("Loaded in editor, marking as incompatible"sv);
		return false;
	}

	const auto ver = a_skse->RuntimeVersion();

	return true;
}

SKSEPluginLoad(const SKSE::LoadInterface* skse)
{
	SKSE::Init(skse);
	Log::SetupLog();

	SKSE::GetMessagingInterface()->RegisterListener(OnEvent);

	ControlledCasting::CasterHook::Install();

	InitializePapyrus();

	return true;
};
