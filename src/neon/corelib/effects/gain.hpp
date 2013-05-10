#ifndef NEON__EFFECTS__GAIN_HPP
#define NEON__EFFECTS__GAIN_HPP

#include <core/effect.hpp>

namespace Ne
{
	namespace Effects
	{
		class Gain
			: public Ne::Effect
		{
		public:
			enum Parameters
			{
				GAIN = Ne::Effect::CUSTOM_BASE,

				N_PARAMETERS
			};

			Gain();
			~Gain();

			float process(float in);
		};
	}
}

#endif /* NEON__EFFECTS__GAIN_HPP */

