#pragma once

namespace Settings
{
	//Functions
	
	void ReadSettings();


	static void ReadBoolSetting(CSimpleIniA& a_ini, const char* a_sectionName, const char* a_settingName, bool& a_setting);
	static void ReadFloatSetting(CSimpleIniA& a_ini, const char* a_sectionName, const char* a_settingName, float& a_setting);
	static void ReadIntSetting(CSimpleIniA& a_ini, const char* a_sectionName, const char* a_settingName, int& a_setting);
	
	
	//Globals

	//Other Settings
	//inline bool bShowMsgs = false;
	inline int iLogLevel = 2;
	inline bool bStaffAsSpell = false;
	inline bool bScrollAsSpell = false;

	//Resources
	inline int iResource = 0;
	inline int iResource_NPC = 0;
	inline float fMagickaMult = 1.0;
	inline float fHealthMult = 1.0;
	inline float fStaminaMult = 1.0;
	inline float fMagickaMult_NPC = 1.0;
	inline float fHealthMult_NPC = 1.0;
	inline float fStaminaMult_NPC = 1.0;

	//Staff
	inline float fStaffFFMult = 1; 
	inline float fStaffFFOverride = 0.5; 
	
	inline float fStaffConcMod = 0; 
	inline float fStaffConcOverride = 0; 

	inline bool bStaffFFOverrideToggle = false; 
	inline bool bStaffConcOverrideToggle = false; 
 
	//Scroll
	inline float fScrollFFMult = 1;
	inline float fScrollFFOverride = 0.5;

	inline float fScrollConcMod = 0;
	inline float fScrollConcOverride = 0;

	inline bool bScrollFFOverrideToggle = false;
	inline bool bScrollConcOverrideToggle = false;

	//Player
	//Fire and Forget
	inline float fBaseFFMult = 1;
	inline float fNoviceMult = 1;
	inline float fApprenticeMult = 1;
	inline float fAdeptMult = 1;
	inline float fExpertMult = 1;
	inline float fMasterMult = 1;
	inline float fAlterationMult = 1;
	inline float fConjurationMult = 1;
	inline float fDestructionMult = 1;
	inline float fIllusionMult = 1;
	inline float fRestorationMult = 1;
	inline float fRitualMult = 1;

	inline float fNoviceFFOverride = 0.5;
	inline float fApprenticeFFOverride = 0.5;
	inline float fAdeptFFOverride = 0.5;
	inline float fExpertFFOverride = 0.5;
	inline float fMasterFFOverride = 3;
	inline float fRitualFFOverride = 3;

	inline bool bNoviceFFOverrideToggle = false;
	inline bool bApprenticeFFOverrideToggle = false;
	inline bool bAdeptFFOverrideToggle = false;
	inline bool bExpertFFOverrideToggle = false;
	inline bool bMasterFFOverrideToggle = false;
	inline bool bRitualFFOverrideToggle = false;

	//Concentration
	inline float fBaseConcMod = 0;
	inline float fNoviceMod = 0;
	inline float fApprenticeMod = 0;
	inline float fAdeptMod = 0;
	inline float fExpertMod = 0;
	inline float fMasterMod = 0;
	inline float fAlterationMod = 0;
	inline float fConjurationMod = 0;
	inline float fDestructionMod = 0;
	inline float fIllusionMod = 0;
	inline float fRestorationMod = 0;
	inline float fRitualMod = 0;

	inline float fNoviceConcOverride = 0;
	inline float fApprenticeConcOverride = 0;
	inline float fAdeptConcOverride = 0;
	inline float fExpertConcOverride = 0;
	inline float fMasterConcOverride = 3;
	inline float fRitualConcOverride = 3;

	inline bool bNoviceConcOverrideToggle = false;
	inline bool bApprenticeConcOverrideToggle = false;
	inline bool bAdeptConcOverrideToggle = false;
	inline bool bExpertConcOverrideToggle = false;
	inline bool bMasterConcOverrideToggle = false;
	inline bool bRitualConcOverrideToggle = false;

	//NPC
	//Fire and Forget
	inline float fBaseFFMult_NPC = 1;
	inline float fNoviceMult_NPC = 1;
	inline float fApprenticeMult_NPC = 1;
	inline float fAdeptMult_NPC = 1;
	inline float fExpertMult_NPC = 1;
	inline float fMasterMult_NPC = 1;
	inline float fAlterationMult_NPC = 1;
	inline float fConjurationMult_NPC = 1;
	inline float fDestructionMult_NPC = 1;
	inline float fIllusionMult_NPC = 1;
	inline float fRestorationMult_NPC = 1;
	inline float fRitualMult_NPC = 1;

	inline float fNoviceFFOverride_NPC = 0.5;
	inline float fApprenticeFFOverride_NPC = 0.5;
	inline float fAdeptFFOverride_NPC = 0.5;
	inline float fExpertFFOverride_NPC = 0.5;
	inline float fMasterFFOverride_NPC = 3;
	inline float fRitualFFOverride_NPC = 3;

	inline bool bNoviceFFOverrideToggle_NPC = false;
	inline bool bApprenticeFFOverrideToggle_NPC = false;
	inline bool bAdeptFFOverrideToggle_NPC = false;
	inline bool bExpertFFOverrideToggle_NPC = false;
	inline bool bMasterFFOverrideToggle_NPC = false;
	inline bool bRitualFFOverrideToggle_NPC = false;

	//Concentration
	inline float fBaseConcMod_NPC = 0;
	inline float fNoviceMod_NPC = 0;
	inline float fApprenticeMod_NPC = 0;
	inline float fAdeptMod_NPC = 0;
	inline float fExpertMod_NPC = 0;
	inline float fMasterMod_NPC = 0;
	inline float fAlterationMod_NPC = 0;
	inline float fConjurationMod_NPC = 0;
	inline float fDestructionMod_NPC = 0;
	inline float fIllusionMod_NPC = 0;
	inline float fRestorationMod_NPC = 0;
	inline float fRitualMod_NPC = 0;

	inline float fNoviceConcOverride_NPC = 0;
	inline float fApprenticeConcOverride_NPC = 0;
	inline float fAdeptConcOverride_NPC = 0;
	inline float fExpertConcOverride_NPC = 0;
	inline float fMasterConcOverride_NPC = 3;
	inline float fRitualConcOverride_NPC = 3;

	inline bool bNoviceConcOverrideToggle_NPC = false;
	inline bool bApprenticeConcOverrideToggle_NPC = false;
	inline bool bAdeptConcOverrideToggle_NPC = false;
	inline bool bExpertConcOverrideToggle_NPC = false;
	inline bool bMasterConcOverrideToggle_NPC = false;
	inline bool bRitualConcOverrideToggle_NPC = false;

}
