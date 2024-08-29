#pragma once

#include "PCH.h"
#include "RE/M/MagicCaster.h"


namespace ControlledCasting {

	float GetNewChargeTime(RE::MagicCaster* caster, float time);

	inline float FFmult_Difficulty = 1;
	inline float FFmult_School = 1;
	
	inline float ConcMod_Difficulty = 0;
	inline float ConcMod_School = 0;

	inline float FFoverride_Difficulty;
	inline float ConcOverride_Difficulty;
	inline bool FFoverride_Toggle_Difficulty = false;
	inline bool ConcOverride_Toggle_Difficulty = false;

	struct CasterHook
	{
	public:

		static void RequestCastImpl(RE::MagicCaster* caster);

		static inline REL::Relocation<decltype(RequestCastImpl)> func3;

		static void Install();
	};

	
	void SendChargeTime(RE::MagicCaster* caster, float time);
	
		
}


