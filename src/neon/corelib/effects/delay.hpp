#ifndef NEON__EFFECTS__DELAY_HPP
#define NEON__EFFECTS__DELAY_HPP

#include <core/effect.hpp>

namespace Ne
{
	namespace Effects
	{
		class Delay
			: public Ne::Effect
		{
		private:
			float* m_buffer;
			unsigned int m_offset;

		public:
			enum Parameters
			{
				DURATION = Ne::Effect::CUSTOM_BASE,
				DAMP,

				N_PARAMETERS
			};

			Delay();
			~Delay();

			float process(float in);
		};
	}
}

#endif /* NEON__EFFECTS__DELAY_HPP */

