#ifndef NEON__CORE__EFFECT_HPP
#define NEON__CORE__EFFECT_HPP

#include <core/parametrable.hpp>

namespace Ne
{
	class Effect
		: public Ne::Parametrable
	{
	public:
		enum Parameters
		{
			CUSTOM_BASE = 0
		};

		Effect(unsigned int nParameters);
		virtual float process(float in) = 0;
	};
}

#endif /* NEON__CORE__EFFECT_HPP */
