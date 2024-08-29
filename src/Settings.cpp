#include "Settings.h"
#include "Logger.h"

namespace Settings
{
	void Settings::ReadSettings() {

		constexpr auto defaultSettingsPath = L"Data/MCM/Config/ControlledCasting/settings.ini";
		constexpr auto mcmPath = L"Data/MCM/Settings/ControlledCasting.ini";

		auto dataHandler = RE::TESDataHandler::GetSingleton(); //may not need

		const auto readMCM = [&](std::filesystem::path path) {
			CSimpleIniA mcm;
			mcm.SetUnicode();

			mcm.LoadFile(path.string().c_str());

			//Other Settings
			ReadIntSetting(mcm, "OtherSettings", "iLogLevel", iLogLevel);
			ReadBoolSetting(mcm, "OtherSettings", "bStaffAsSpell", bStaffAsSpell);
			ReadBoolSetting(mcm, "OtherSettings", "bScrollAsSpell", bScrollAsSpell);

			//Resource
			ReadIntSetting(mcm, "Resource", "iResource", iResource);
			ReadIntSetting(mcm, "Resource", "iResource_NPC", iResource_NPC);
			ReadFloatSetting(mcm, "Resource", "fMagickaMult", fMagickaMult);
			ReadFloatSetting(mcm, "Resource", "fHealthMult", fHealthMult);
			ReadFloatSetting(mcm, "Resource", "fStaminaMult", fStaminaMult);
			ReadFloatSetting(mcm, "Resource", "fMagickaMult_NPC", fMagickaMult_NPC);
			ReadFloatSetting(mcm, "Resource", "fHealthMult_NPC", fHealthMult_NPC);
			ReadFloatSetting(mcm, "Resource", "fStaminaMult_NPC", fStaminaMult_NPC);

			//Staff
			ReadFloatSetting(mcm, "Staff", "fStaffFFMult", fStaffFFMult);
			ReadFloatSetting(mcm, "Staff", "fStaffFFOverride", fStaffFFOverride);

			ReadFloatSetting(mcm, "Staff", "fStaffConcMod", fStaffConcMod);
			ReadFloatSetting(mcm, "Staff", "fStaffConcOverride", fStaffConcOverride);

			ReadBoolSetting(mcm, "Staff", "bStaffConcOverrideToggle", bStaffConcOverrideToggle);
			ReadBoolSetting(mcm, "Staff", "bStaffFFOverrideToggle", bStaffFFOverrideToggle);

			//Scrolls
			ReadFloatSetting(mcm, "Scroll", "fScrollFFMult", fScrollFFMult);
			ReadFloatSetting(mcm, "Scroll", "fScrollFFOverride", fScrollFFOverride);

			ReadFloatSetting(mcm, "Scroll", "fScrollConcMod", fScrollConcMod);
			ReadFloatSetting(mcm, "Scroll", "fScrollConcOverride", fScrollConcOverride);

			ReadBoolSetting(mcm, "Scroll", "bScrollConcOverrideToggle", bScrollConcOverrideToggle);
			ReadBoolSetting(mcm, "Scroll", "bScrollFFOverrideToggle", bScrollFFOverrideToggle);

			//Player
			//Fire and Forget
			ReadFloatSetting(mcm, "Player_FF", "fBaseFFMult", fBaseFFMult);
			ReadFloatSetting(mcm, "Player_FF", "fNoviceMult", fNoviceMult);
			ReadFloatSetting(mcm, "Player_FF", "fApprenticeMult", fApprenticeMult);
			ReadFloatSetting(mcm, "Player_FF", "fAdeptMult", fAdeptMult);
			ReadFloatSetting(mcm, "Player_FF", "fExpertMult", fExpertMult);
			ReadFloatSetting(mcm, "Player_FF", "fMasterMult", fMasterMult);
			ReadFloatSetting(mcm, "Player_FF", "fRitualMult", fRitualMult);
			ReadFloatSetting(mcm, "Player_FF", "fAlterationMult", fAlterationMult);
			ReadFloatSetting(mcm, "Player_FF", "fConjurationMult", fConjurationMult);
			ReadFloatSetting(mcm, "Player_FF", "fDestructionMult", fDestructionMult);
			ReadFloatSetting(mcm, "Player_FF", "fIllusionMult", fIllusionMult);
			ReadFloatSetting(mcm, "Player_FF", "fRestorationMult", fRestorationMult);
			

			ReadFloatSetting(mcm, "Player_FF", "fNoviceFFOverride", fNoviceFFOverride);
			ReadFloatSetting(mcm, "Player_FF", "fApprenticeFFOverride", fApprenticeFFOverride);
			ReadFloatSetting(mcm, "Player_FF", "fAdeptFFOverride", fAdeptFFOverride);
			ReadFloatSetting(mcm, "Player_FF", "fExpertFFOverride", fExpertFFOverride);
			ReadFloatSetting(mcm, "Player_FF", "fMasterFFOverride", fMasterFFOverride);
			ReadFloatSetting(mcm, "Player_FF", "fRitualFFOverride", fRitualFFOverride);

			ReadBoolSetting(mcm, "Player_FF", "bNoviceFFOverride", bNoviceFFOverrideToggle);
			ReadBoolSetting(mcm, "Player_FF", "bApprenticeFFOverrideToggle", bApprenticeFFOverrideToggle);
			ReadBoolSetting(mcm, "Player_FF", "bAdeptFFOverrideToggle", bAdeptFFOverrideToggle);
			ReadBoolSetting(mcm, "Player_FF", "bExpertFFOverrideToggle", bExpertFFOverrideToggle);
			ReadBoolSetting(mcm, "Player_FF", "bMasterFFOverrideToggle", bMasterFFOverrideToggle);
			ReadBoolSetting(mcm, "Player_FF", "bRitualFFOverrideToggle", bRitualFFOverrideToggle);

			//Concentration
			ReadFloatSetting(mcm, "Player_Conc", "fBaseConcMod", fBaseConcMod);
			ReadFloatSetting(mcm, "Player_Conc", "fNoviceMod", fNoviceMod);
			ReadFloatSetting(mcm, "Player_Conc", "fApprenticeMod", fApprenticeMod);
			ReadFloatSetting(mcm, "Player_Conc", "fAdeptMod", fAdeptMod);
			ReadFloatSetting(mcm, "Player_Conc", "fExpertMod", fExpertMod);
			ReadFloatSetting(mcm, "Player_Conc", "fMasterMod", fMasterMod);
			ReadFloatSetting(mcm, "Player_Conc", "fRitualMod", fRitualMod);
			ReadFloatSetting(mcm, "Player_Conc", "fAlterationMod", fAlterationMod);
			ReadFloatSetting(mcm, "Player_Conc", "fConjurationMod", fConjurationMod);
			ReadFloatSetting(mcm, "Player_Conc", "fDestructionMod", fDestructionMod);
			ReadFloatSetting(mcm, "Player_Conc", "fIllusionMod", fIllusionMod);
			ReadFloatSetting(mcm, "Player_Conc", "fRestorationMod", fRestorationMod);

			ReadFloatSetting(mcm, "Player_Conc", "fNoviceConcOverride", fNoviceConcOverride);
			ReadFloatSetting(mcm, "Player_Conc", "fApprenticeConcOverride", fApprenticeConcOverride);
			ReadFloatSetting(mcm, "Player_Conc", "fAdeptConcOverride", fAdeptConcOverride);
			ReadFloatSetting(mcm, "Player_Conc", "fExpertConcOverride", fExpertConcOverride);
			ReadFloatSetting(mcm, "Player_Conc", "fMasterConcOverride", fMasterConcOverride);
			ReadFloatSetting(mcm, "Player_Conc", "fRitualConcOverride", fRitualConcOverride);

			ReadBoolSetting(mcm, "Player_Conc", "bNoviceConcOverride", bNoviceConcOverrideToggle);
			ReadBoolSetting(mcm, "Player_Conc", "bApprenticeConcOverrideToggle", bApprenticeConcOverrideToggle);
			ReadBoolSetting(mcm, "Player_Conc", "bAdeptConcOverrideToggle", bAdeptConcOverrideToggle);
			ReadBoolSetting(mcm, "Player_Conc", "bExpertConcOverrideToggle", bExpertConcOverrideToggle);
			ReadBoolSetting(mcm, "Player_Conc", "bMasterConcOverrideToggle", bMasterConcOverrideToggle);
			ReadBoolSetting(mcm, "Player_Conc", "bRitualConcOverrideToggle", bRitualConcOverrideToggle);

			//NPC
			//Fire and Forget
			ReadFloatSetting(mcm, "NPC_FF", "fBaseFFMult_NPC", fBaseFFMult_NPC);
			ReadFloatSetting(mcm, "NPC_FF", "fNoviceMult_NPC", fNoviceMult_NPC);
			ReadFloatSetting(mcm, "NPC_FF", "fApprenticeMult_NPC", fApprenticeMult_NPC);
			ReadFloatSetting(mcm, "NPC_FF", "fAdeptMult_NPC", fAdeptMult_NPC);
			ReadFloatSetting(mcm, "NPC_FF", "fExpertMult_NPC", fExpertMult_NPC);
			ReadFloatSetting(mcm, "NPC_FF", "fMasterMult_NPC", fMasterMult_NPC);
			ReadFloatSetting(mcm, "NPC_FF", "fRitualMult_NPC", fRitualMult_NPC);
			ReadFloatSetting(mcm, "NPC_FF", "fAlterationMult_NPC", fAlterationMult_NPC);
			ReadFloatSetting(mcm, "NPC_FF", "fConjurationMult_NPC", fConjurationMult_NPC);
			ReadFloatSetting(mcm, "NPC_FF", "fDestructionMult_NPC", fDestructionMult_NPC);
			ReadFloatSetting(mcm, "NPC_FF", "fIllusionMult_NPC", fIllusionMult_NPC);
			ReadFloatSetting(mcm, "NPC_FF", "fRestorationMult_NPC", fRestorationMult_NPC);

			ReadFloatSetting(mcm, "NPC_FF", "fNoviceFFOverride_NPC", fNoviceFFOverride_NPC);
			ReadFloatSetting(mcm, "NPC_FF", "fApprenticeFFOverride_NPC", fApprenticeFFOverride_NPC);
			ReadFloatSetting(mcm, "NPC_FF", "fAdeptFFOverride_NPC", fAdeptFFOverride_NPC);
			ReadFloatSetting(mcm, "NPC_FF", "fExpertFFOverride_NPC", fExpertFFOverride_NPC);
			ReadFloatSetting(mcm, "NPC_FF", "fMasterFFOverride_NPC", fMasterFFOverride_NPC);
			ReadFloatSetting(mcm, "NPC_FF", "fRitualFFOverride_NPC", fRitualFFOverride_NPC);

			ReadBoolSetting(mcm, "NPC_FF", "bNoviceFFOverrideToggle_NPC", bNoviceFFOverrideToggle_NPC);
			ReadBoolSetting(mcm, "NPC_FF", "bApprenticeFFOverrideToggle_NPC", bApprenticeFFOverrideToggle_NPC);
			ReadBoolSetting(mcm, "NPC_FF", "bAdeptFFOverrideToggle_NPC", bAdeptFFOverrideToggle_NPC);
			ReadBoolSetting(mcm, "NPC_FF", "bExpertFFOverrideToggle_NPC", bExpertFFOverrideToggle_NPC);
			ReadBoolSetting(mcm, "NPC_FF", "bMasterFFOverrideToggle_NPC", bMasterFFOverrideToggle_NPC);
			ReadBoolSetting(mcm, "NPC_FF", "bRitualFFOverrideToggle_NPC", bRitualFFOverrideToggle_NPC);

			//Concentration
			ReadFloatSetting(mcm, "NPC_Conc", "fBaseConcMod_NPC", fBaseConcMod_NPC);
			ReadFloatSetting(mcm, "NPC_Conc", "fNoviceMod_NPC", fNoviceMod_NPC);
			ReadFloatSetting(mcm, "NPC_Conc", "fApprenticeMod_NPC", fApprenticeMod_NPC);
			ReadFloatSetting(mcm, "NPC_Conc", "fAdeptMod_NPC", fAdeptMod_NPC);
			ReadFloatSetting(mcm, "NPC_Conc", "fExpertMod_NPC", fExpertMod_NPC);
			ReadFloatSetting(mcm, "NPC_Conc", "fMasterMod_NPC", fMasterMod_NPC);
			ReadFloatSetting(mcm, "NPC_Conc", "fRitualMod_NPC", fRitualMod_NPC);
			ReadFloatSetting(mcm, "NPC_Conc", "fAlterationMod_NPC", fAlterationMod_NPC);
			ReadFloatSetting(mcm, "NPC_Conc", "fConjurationMod_NPC", fConjurationMod_NPC);
			ReadFloatSetting(mcm, "NPC_Conc", "fDestructionMod_NPC", fDestructionMod_NPC);
			ReadFloatSetting(mcm, "NPC_Conc", "fIllusionMod_NPC", fIllusionMod_NPC);
			ReadFloatSetting(mcm, "NPC_Conc", "fRestorationMod_NPC", fRestorationMod_NPC);

			ReadFloatSetting(mcm, "NPC_Conc", "fNoviceConcOverride_NPC", fNoviceConcOverride_NPC);
			ReadFloatSetting(mcm, "NPC_Conc", "fApprenticeConcOverride_NPC", fApprenticeConcOverride_NPC);
			ReadFloatSetting(mcm, "NPC_Conc", "fAdeptConcOverride_NPC", fAdeptConcOverride_NPC);
			ReadFloatSetting(mcm, "NPC_Conc", "fExpertConcOverride_NPC", fExpertConcOverride_NPC);
			ReadFloatSetting(mcm, "NPC_Conc", "fMasterConcOverride_NPC", fMasterConcOverride_NPC);
			ReadFloatSetting(mcm, "NPC_Conc", "fRitualConcOverride_NPC", fRitualConcOverride_NPC);

			ReadBoolSetting(mcm, "NPC_Conc", "bNoviceConcOverrideToggle_NPC", bNoviceConcOverrideToggle_NPC);
			ReadBoolSetting(mcm, "NPC_Conc", "bApprenticeConcOverrideToggle_NPC", bApprenticeConcOverrideToggle_NPC);
			ReadBoolSetting(mcm, "NPC_Conc", "bAdeptConcOverrideToggle_NPC", bAdeptConcOverrideToggle_NPC);
			ReadBoolSetting(mcm, "NPC_Conc", "bExpertConcOverrideToggle_NPC", bExpertConcOverrideToggle_NPC);
			ReadBoolSetting(mcm, "NPC_Conc", "bMasterConcOverrideToggle_NPC", bMasterConcOverrideToggle_NPC);
			ReadBoolSetting(mcm, "NPC_Conc", "bRitualConcOverrideToggle_NPC", bRitualConcOverrideToggle_NPC);


		};
		logger::info("Reading MCM .ini...");

		readMCM(defaultSettingsPath);  // read the default ini first
		readMCM(mcmPath);

		logger::info("...success");

		Log::UpdateLogLevel(Settings::iLogLevel);

	}


	void Settings::ReadBoolSetting(CSimpleIniA& a_ini, const char* a_sectionName, const char* a_settingName, bool& a_setting)
	{
		const char* bFound = nullptr;
		bFound = a_ini.GetValue(a_sectionName, a_settingName);
		if (bFound) {
			a_setting = a_ini.GetBoolValue(a_sectionName, a_settingName);
		}
	}

	void Settings::ReadFloatSetting(CSimpleIniA& a_ini, const char* a_sectionName, const char* a_settingName, float& a_setting)
	{
		const char* bFound = nullptr;
		bFound = a_ini.GetValue(a_sectionName, a_settingName);
		if (bFound) {
			a_setting = static_cast<float>(a_ini.GetDoubleValue(a_sectionName, a_settingName));
		}
	}

	void Settings::ReadIntSetting(CSimpleIniA& a_ini, const char* a_sectionName, const char* a_settingName, int& a_setting)
	{
		const char* bFound = nullptr;
		bFound = a_ini.GetValue(a_sectionName, a_settingName);
		if (bFound) {
			a_setting = static_cast<int>(a_ini.GetLongValue(a_sectionName, a_settingName));
		}
	}
}
