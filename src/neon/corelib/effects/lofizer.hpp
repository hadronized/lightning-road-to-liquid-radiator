#ifndef NEON__EFFECTS__LOFIZER_HPP
#define NEON__EFFECTS__LOFIZER_HPP

#include <core/effect.hpp>

namespace Ne
{
	namespace Effects
	{
		class Lofizer
			: public Ne::Effect
		{
		private:
			float        m_lastIn;

			unsigned int m_dsCounter;
			unsigned int m_dsStep;

		public:
			enum Parameters
			{
				QUANTIZATION = Ne::Effect::CUSTOM_BASE,
				DOWNSAMPLING,

				N_PARAMETERS
			};

			Lofizer();
			~Lofizer();

			float process(float in);
			void onChange();
		};
	}
}

#endif /* NEON__EFFECTS__LOFIZER_HPP */

