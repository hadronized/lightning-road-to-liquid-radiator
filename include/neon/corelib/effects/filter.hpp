#ifndef __NEON__EFFECTS__FILTER_HPP__
#define __NEON__EFFECTS__FILTER_HPP__

#include <core/effect.hpp>

namespace Ne
{
	class Property;

	namespace Effects
	{
		class Filter
			: public Ne::Effect
		{
		private:
			float m_lowpass,
			      m_bandpass,
				  m_highpass,
				  m_notch,
				  m_peak;

			float m_drive, m_freq, m_fc, m_damp;

		public:
			enum Parameters
			{
				LOWPASS_LEVEL = Ne::Effect::CUSTOM_BASE,
				BANDPASS_LEVEL,
				HIGHPASS_LEVEL,
				NOTCH_LEVEL,
				PEAK_LEVEL,

				CUTOFF,
				RESONANCE,
				DRIVE,

				N_PARAMETERS
			};

			Filter();
			~Filter();

			float process(float in);

			void onChange();
		};
	}
}

#endif /* __NEON__EFFECTS__FILTER_HPP__ */

