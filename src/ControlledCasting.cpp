
#include "ControlledCasting.h"
#include "PCH.h"
#include "utility.h"
#include <iostream>
#include "Settings.h"
#include "DMMF_API.h"

namespace ControlledCasting {
	
	using namespace Settings;

	//Calculates the charge time of a staff
	float CalcStaffChargeTime(RE::MagicItem* magic, RE::MagicCaster* caster, RE::MagicSystem::CastingType casting, float time)
	{
		logger::debug("Calculating staff charge time");
		logger::debug("formid: {}", magic->GetFormID());
		
		float newTime = time;

		if (casting == RE::MagicSystem::CastingType::kFireAndForget) {
			if (bStaffFFOverrideToggle) {
				newTime = fStaffFFOverride;
			}

			newTime = newTime * fStaffFFMult;
		}
		if (casting == RE::MagicSystem::CastingType::kConcentration) {
			
			if (bStaffConcOverrideToggle) {
				newTime = fStaffConcOverride;
			}
			
			newTime = newTime + fStaffConcMod;
		}
		return newTime;
	}

	//Calculates the charge time of a scroll
	float CalcScrollChargeTime(RE::MagicItem* magic, RE::MagicCaster* caster, RE::MagicSystem::CastingType casting, float time)
	{

		logger::debug("Calculating scroll charge time");
		logger::debug("formid: {}", magic->GetFormID());

		float newTime = time;

		if (casting == RE::MagicSystem::CastingType::kFireAndForget) {

			if (bScrollFFOverrideToggle) {
				newTime = fScrollFFOverride;
			}

			newTime = newTime * fScrollFFMult;
			
		} 
		if (casting == RE::MagicSystem::CastingType::kConcentration) {
			
			if (bScrollConcOverrideToggle) {
				newTime = fScrollConcOverride;
			}

			newTime = newTime + fScrollConcMod;
			
		}
		return newTime;
	}

	//Calculates the charge time of a normal spell
	float CalcSpellChargeTime(RE::MagicItem* magic, RE::MagicCaster* caster, RE::MagicSystem::CastingType casting, float time)
	{
		int numeffects = magic->effects.size();
		int32_t difficulty;
		bool ritual;
		RE::ActorValue school;
		RE::Actor* actor;
		if (actor = caster->GetCasterAsActor()) {
			if (numeffects > 0) {

				logger::debug("Getting school and difficulty");
				
				auto costliest = magic->GetCostliestEffectItem();
				if (costliest) {
					school = magic->GetCostliestEffectItem()->baseEffect->GetMagickSkill();
					difficulty = magic->GetCostliestEffectItem()->baseEffect->GetMinimumSkillLevel();
					ritual = magic->GetCostliestEffectItem()->baseEffect->HasKeywordString("RitualSpellEffect");
				}
			} else {
				return time;
			}

			auto PlayerRef = RE::PlayerCharacter::GetSingleton();
			if (actor == PlayerRef) {
				switch (school) {
				case RE::ActorValue::kAlteration:
					FFmult_School = fAlterationMult;
					ConcMod_School = fAlterationMod;

					break;
				case RE::ActorValue::kConjuration:
					FFmult_School = fConjurationMult;
					ConcMod_School = fConjurationMod;

					break;
				case RE::ActorValue::kDestruction:
					FFmult_School = fDestructionMult;
					ConcMod_School = fDestructionMod;

					break;
				case RE::ActorValue::kIllusion:
					FFmult_School = fIllusionMult;
					ConcMod_School = fIllusionMod;

					break;
				case RE::ActorValue::kRestoration:
					FFmult_School = fRestorationMult;
					ConcMod_School = fRestorationMod;

					break;
				}
				switch (difficulty) {
				case 0:
					FFmult_Difficulty = fNoviceMult;
					ConcMod_Difficulty = fNoviceMod;
					FFoverride_Difficulty = fNoviceFFOverride;
					ConcOverride_Difficulty = fNoviceConcOverride;
					FFoverride_Toggle_Difficulty = bNoviceFFOverrideToggle;
					ConcOverride_Toggle_Difficulty = bNoviceConcOverrideToggle;

					break;
				case 25:
					FFmult_Difficulty = fApprenticeMult;
					ConcMod_Difficulty = fApprenticeMod;
					FFoverride_Difficulty = fApprenticeFFOverride;
					ConcOverride_Difficulty = fApprenticeConcOverride;
					FFoverride_Toggle_Difficulty = bApprenticeFFOverrideToggle;
					ConcOverride_Toggle_Difficulty = bApprenticeConcOverrideToggle;

					break;
				case 50:
					FFmult_Difficulty = fAdeptMult;
					ConcMod_Difficulty = fAdeptMod;
					FFoverride_Difficulty = fAdeptFFOverride;
					ConcOverride_Difficulty = fAdeptConcOverride;
					FFoverride_Toggle_Difficulty = bAdeptFFOverrideToggle;
					ConcOverride_Toggle_Difficulty = bAdeptConcOverrideToggle;

					break;
				case 75:
					FFmult_Difficulty = fExpertMult;
					ConcMod_Difficulty = fExpertMod;
					FFoverride_Difficulty = fExpertFFOverride;
					ConcOverride_Difficulty = fExpertConcOverride;
					FFoverride_Toggle_Difficulty = bExpertFFOverrideToggle;
					ConcOverride_Toggle_Difficulty = bExpertConcOverrideToggle;

					break;
				case 90:
					FFmult_Difficulty = fExpertMult;
					ConcMod_Difficulty = fExpertMod;
					FFoverride_Difficulty = fExpertFFOverride;
					ConcOverride_Difficulty = fExpertConcOverride;
					FFoverride_Toggle_Difficulty = bExpertFFOverrideToggle;
					ConcOverride_Toggle_Difficulty = bExpertConcOverrideToggle;

					break;
				case 100:
					FFmult_Difficulty = fMasterMult;
					ConcMod_Difficulty = fMasterMod;
					FFoverride_Difficulty = fMasterFFOverride;
					ConcOverride_Difficulty = fMasterConcOverride;
					FFoverride_Toggle_Difficulty = bMasterFFOverrideToggle;
					ConcOverride_Toggle_Difficulty = bMasterConcOverrideToggle;

					break;
				}


				logger::debug("The casting type is: {}", *reinterpret_cast<int*>(&casting));
				logger::debug("The original charge time was: {}", time);
				
				if (casting == RE::MagicSystem::CastingType::kFireAndForget) {
					if (FFoverride_Toggle_Difficulty) {
						time = FFoverride_Difficulty;
					}
					if (ritual) {
						FFmult_Difficulty = fRitualMult;
						if (fRitualFFOverride) {
							time = fRitualFFOverride;
						}
					}
					auto newTime = time * fBaseFFMult * FFmult_School * FFmult_Difficulty;
					logger::debug("The new charge time is: {}", newTime);
					
					return newTime;

				} else if (casting == RE::MagicSystem::CastingType::kConcentration) {
					if (ConcOverride_Toggle_Difficulty) {
						time = ConcOverride_Difficulty;
					}
					if (ritual) {
						ConcMod_Difficulty = fRitualMod;
						if (bRitualConcOverrideToggle) {
							time = fRitualConcOverride;
						}
					}

					auto newTime = time + fBaseConcMod + ConcMod_School + ConcMod_Difficulty;
					logger::debug("The new charge time is: {}", newTime);

					return newTime;

				} else {
					return time;
				}
			} else {
				switch (school) {
				case RE::ActorValue::kAlteration:
					FFmult_School = fAlterationMult_NPC;
					ConcMod_School = fAlterationMod_NPC;

					break;
				case RE::ActorValue::kConjuration:
					FFmult_School = fConjurationMult_NPC;
					ConcMod_School = fConjurationMod_NPC;

					break;
				case RE::ActorValue::kDestruction:
					FFmult_School = fDestructionMult_NPC;
					ConcMod_School = fDestructionMod_NPC;

					break;
				case RE::ActorValue::kIllusion:
					FFmult_School = fIllusionMult_NPC;
					ConcMod_School = fIllusionMod_NPC;

					break;
				case RE::ActorValue::kRestoration:
					FFmult_School = fRestorationMult_NPC;
					ConcMod_School = fRestorationMod_NPC;

					break;
				}
				switch (difficulty) {
				case 0:
					FFmult_Difficulty = fNoviceMult_NPC;
					ConcMod_Difficulty = fNoviceMod_NPC;
					FFoverride_Difficulty = fNoviceFFOverride_NPC;
					ConcOverride_Difficulty = fNoviceConcOverride_NPC;
					FFoverride_Toggle_Difficulty = bNoviceFFOverrideToggle_NPC;
					ConcOverride_Toggle_Difficulty = bNoviceConcOverrideToggle_NPC;

					break;
				case 25:
					FFmult_Difficulty = fApprenticeMult_NPC;
					ConcMod_Difficulty = fApprenticeMod_NPC;
					FFoverride_Difficulty = fApprenticeFFOverride_NPC;
					ConcOverride_Difficulty = fApprenticeConcOverride_NPC;
					FFoverride_Toggle_Difficulty = bApprenticeFFOverrideToggle_NPC;
					ConcOverride_Toggle_Difficulty = bApprenticeConcOverrideToggle_NPC;

					break;
				case 50:
					FFmult_Difficulty = fAdeptMult_NPC;
					ConcMod_Difficulty = fAdeptMod_NPC;
					FFoverride_Difficulty = fAdeptFFOverride_NPC;
					ConcOverride_Difficulty = fAdeptConcOverride_NPC;
					FFoverride_Toggle_Difficulty = bAdeptFFOverrideToggle_NPC;
					ConcOverride_Toggle_Difficulty = bAdeptConcOverrideToggle_NPC;

					break;
				case 75:
					FFmult_Difficulty = fExpertMult_NPC;
					ConcMod_Difficulty = fExpertMod_NPC;
					FFoverride_Difficulty = fExpertFFOverride_NPC;
					ConcOverride_Difficulty = fExpertConcOverride_NPC;
					FFoverride_Toggle_Difficulty = bExpertFFOverrideToggle_NPC;
					ConcOverride_Toggle_Difficulty = bExpertConcOverrideToggle_NPC;

					break;
				case 90:
					FFmult_Difficulty = fExpertMult_NPC;
					ConcMod_Difficulty = fExpertMod_NPC;
					FFoverride_Difficulty = fExpertFFOverride_NPC;
					ConcOverride_Difficulty = fExpertConcOverride_NPC;
					FFoverride_Toggle_Difficulty = bExpertFFOverrideToggle_NPC;
					ConcOverride_Toggle_Difficulty = bExpertConcOverrideToggle_NPC;

					break;
				case 100:
					FFmult_Difficulty = fMasterMult_NPC;
					ConcMod_Difficulty = fMasterMod_NPC;
					FFoverride_Difficulty = fMasterFFOverride_NPC;
					ConcOverride_Difficulty = fMasterConcOverride_NPC;
					FFoverride_Toggle_Difficulty = bMasterFFOverrideToggle_NPC;
					ConcOverride_Toggle_Difficulty = bMasterConcOverrideToggle_NPC;

					break;
				}

				logger::debug("The casting type is: {}", *reinterpret_cast<int*>(&casting));
				logger::debug("The original charge time was: {}", time);
				
				if (casting == RE::MagicSystem::CastingType::kFireAndForget) {
					if (FFoverride_Toggle_Difficulty) {
						time = FFoverride_Difficulty;
					}
					if (ritual) {
						FFmult_Difficulty = fRitualMult_NPC;
						if (fRitualFFOverride_NPC) {
							time = fRitualFFOverride_NPC;
						}
					}
					auto newTime = time * fBaseFFMult_NPC * FFmult_School * FFmult_Difficulty;

					logger::debug("The new charge time is: {}", newTime);
					
					return newTime;

				} else if (casting == RE::MagicSystem::CastingType::kConcentration) {
					if (ConcOverride_Toggle_Difficulty) {
						time = ConcOverride_Difficulty;
					}
					if (ritual) {
						ConcMod_Difficulty = fRitualMod_NPC;
						if (bRitualConcOverrideToggle_NPC) {
							time = fRitualConcOverride_NPC;
						}
					}

					auto newTime = time + fBaseConcMod_NPC + ConcMod_School + ConcMod_Difficulty;

					logger::debug("The new charge time is: {}", newTime);

					return newTime;

				} else {
					return time;
				}
			}
			
		} else {
			logger::warn("Could not get actor from magic caster; returning original time.");
			return time;
		}
	}
	
	//Calculates the charge time based on the caster, spell, and selected MCM settings
	float GetNewChargeTime(RE::MagicCaster* caster, float time) {
		RE::MagicItem* spell = (caster->currentSpell);

		if (spell) {
			auto type = spell->GetSpellType();
			auto casting = spell->GetCastingType();

			RE::Actor* actor;
			if (actor = caster->GetCasterAsActor()) {
				if (type == RE::MagicSystem::SpellType::kSpell || type == RE::MagicSystem::SpellType::kStaffEnchantment || type == RE::MagicSystem::SpellType::kScroll) {
					if (casting == RE::MagicSystem::CastingType::kFireAndForget || casting == RE::MagicSystem::CastingType::kConcentration) {

						logger::debug("Calculating new charge time for {}'s {} spell.", actor->GetDisplayFullName(), spell->fullName.c_str());
						
						int numeffects = spell->effects.size();
						int32_t difficulty;
						bool ritual;
						RE::ActorValue school;

						if (numeffects > 0) {

							logger::debug("Getting school and difficulty");
			
							auto costliest = spell->GetCostliestEffectItem();
							if (costliest) {
								school = spell->GetCostliestEffectItem()->baseEffect->GetMagickSkill();
								difficulty = spell->GetCostliestEffectItem()->baseEffect->GetMinimumSkillLevel();
								ritual = spell->GetCostliestEffectItem()->baseEffect->HasKeywordString("RitualSpellEffect");
							}
						} else {
							return time;
						}
						if (type == RE::MagicSystem::SpellType::kSpell || (bStaffAsSpell == 1 && type == RE::MagicSystem::SpellType::kStaffEnchantment) || (bScrollAsSpell == 1 && type == RE::MagicSystem::SpellType::kScroll)) {
							auto newTime = CalcSpellChargeTime(spell, caster, casting, time);

							logger::debug("The new charge time is: {}", newTime);
							
							return newTime;
						} else if (type == RE::MagicSystem::SpellType::kScroll) {
							auto newTime = CalcScrollChargeTime(spell, caster, casting, time);

							logger::debug("The new charge time is: {}", newTime);
							
							return newTime;

						} else if (type == RE::MagicSystem::SpellType::kStaffEnchantment) {
							auto newTime = CalcStaffChargeTime(spell, caster, casting, time);

							logger::debug("The new charge time is: {}", newTime);
							
							return newTime;
						} else {
							return time;
						}
					} else {

						logger::debug("Spell wasn't a concentration or fire and forget spell, returning original time.");
						
						return time;
					}
				} else {
					logger::warn("Magic item was not a spell, scroll, or staff");
					return time;
				}
			} else {
				logger::warn("Caster was not a valid actor");
				return time;
			}
		} else {
			logger::warn("Caster did not have a valid magic item; returning original time.");
			return time;
		}
	} 

	//Sets the resource used for casting based on MCM Settings
	void SetCastingResource(RE::MagicCaster* caster) { //need to update for player vs NPC. Also should make its own MCM page
		
		auto actor = caster->GetCasterAsActor();
		auto player = RE::PlayerCharacter::GetSingleton();
		RE::ActorValue resource = RE::ActorValue::kMagicka;
		if (actor == player) {
			switch (Settings::iResource) {
			case 0:
				//DMMF::SetResource(caster, RE::ActorValue::kMagicka);
				resource = DMMF::GetResource(caster);
				break;
			case 1:
				DMMF::SetResource(caster, RE::ActorValue::kHealth);
				resource = RE::ActorValue::kHealth;
				break;
			case 2:
				DMMF::SetResource(caster, RE::ActorValue::kStamina);
				resource = RE::ActorValue::kStamina;
				break;
			default:
				//DMMF::SetResource(caster, RE::ActorValue::kMagicka);
				resource = DMMF::GetResource(caster);
				break;
			}
			logger::info("Setting resource to {}", resource);
			switch (resource) {
			case RE::ActorValue::kMagicka:
				DMMF::AddCostMultiplier(caster, Settings::fMagickaMult);
				break;
			case RE::ActorValue::kHealth:
				DMMF::AddCostMultiplier(caster, Settings::fHealthMult);
				break;
			case RE::ActorValue::kStamina:
				DMMF::AddCostMultiplier(caster, Settings::fStaminaMult);
				break;
			default:
				DMMF::AddCostMultiplier(caster, Settings::fMagickaMult);
				break;
			}
		} else {
			switch (Settings::iResource_NPC) {
			case 0:
				//DMMF::SetResource(caster, RE::ActorValue::kMagicka);
				resource = DMMF::GetResource(caster);
				break;
			case 1:
				DMMF::SetResource(caster, RE::ActorValue::kHealth);
				resource = RE::ActorValue::kHealth;
				break;
			case 2:
				DMMF::SetResource(caster, RE::ActorValue::kStamina);
				resource = RE::ActorValue::kStamina;
				break;
			default:
				//DMMF::SetResource(caster, RE::ActorValue::kMagicka);
				resource = DMMF::GetResource(caster);
				break;
			}
			logger::info("Setting resource to {}", resource);
			switch (resource) {
			case RE::ActorValue::kMagicka:
				DMMF::AddCostMultiplier(caster, Settings::fMagickaMult_NPC);
				break;
			case RE::ActorValue::kHealth:
				DMMF::AddCostMultiplier(caster, Settings::fHealthMult_NPC);
				break;
			case RE::ActorValue::kStamina:
				DMMF::AddCostMultiplier(caster, Settings::fStaminaMult_NPC);
				break;
			default:
				DMMF::AddCostMultiplier(caster, Settings::fMagickaMult_NPC);
				break;
			}
		}
		
	}

	//Hook the begingging of spell casting (RequestCast) to send updated casting info to DMMF
	void CasterHook::RequestCastImpl(RE::MagicCaster* caster) {
		logger::info("RequestCast");
		if (auto a = caster->GetCasterAsActor(); a && caster->currentSpell && (caster->currentSpell->GetSpellType() == RE::MagicSystem::SpellType::kSpell || caster->currentSpell->GetSpellType() == RE::MagicSystem::SpellType::kStaffEnchantment) || caster->currentSpell->GetSpellType() == RE::MagicSystem::SpellType::kScroll) {
			auto spell = caster->currentSpell;
			float origin = caster->currentSpell->GetChargeTime();

			logger::info("The original time was {} seconds", origin);

			float newTime = GetNewChargeTime(caster, (origin));

			logger::info("The new charge time is {} seconds", newTime);

			SendChargeTime(caster, newTime);
			SetCastingResource(caster);
		}
		func3(caster);
	}

	//Installs hooked functions
	void CasterHook::Install() {
		logger::info("CasterHook Installed");
		REL::Relocation<uintptr_t> ActorCasterVtbl{ RE::VTABLE_ActorMagicCaster[0] };

		CasterHook::func3 = ActorCasterVtbl.write_vfunc(0x3, &CasterHook::RequestCastImpl);
	}

	//Sends the charge time to DMMF
	void SendChargeTime(RE::MagicCaster* caster, float time)
	{
		logger::debug("sending data to SetCastTime function");
		DMMF::SetChargeTime(caster, time);
	}

}


