#ifndef NEON__EFFECTS__TIMESHIFTER_HPP
#define NEON__EFFECTS__TIMESHIFTER_HPP

#include <core/effect.hpp>

namespace Ne
{
	namespace Effects
	{
		class Timeshifter
			: public Ne::Effect
		{
		private:
			unsigned int m_length;
			unsigned int m_writePosition;
			float* m_buffer;

		public:
			enum Parameters
			{
				OFFSET = Ne::Effect::CUSTOM_BASE,

				N_PARAMETERS
			};

			Timeshifter(unsigned int tempo);
			~Timeshifter();

			float process(float in);
		};
	}
}

#endif /* NEON__EFFECTS__TIMESHIFTER_HPP */

