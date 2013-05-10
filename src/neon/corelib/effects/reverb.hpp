#ifndef NEON__EFFECTS__REVERB_HPP
#define NEON__EFFECTS__REVERB_HPP

#include <core/effect.hpp>
#include <core/math.hpp>

namespace Ne
{
	namespace Effects
	{
		class Reverb
			: public Ne::Effect
		{
		private:
			struct FBCF
			{
				int   m_l,
				      m_p;
				float m_f,
					  m_d,
					  m_lastOut;
				float* m_buffer;

				FBCF(int length)
				{
					m_l = length;
					m_p = 0;
					m_f = 0.2f;
					m_d = 0.84f;
					m_lastOut = 0.0f;
					m_buffer = new float[m_l];
					for(int i = 0; i < m_l; ++i)
						m_buffer[i] = 0.0f;
				}

				float process(float in)
				{
					float fOut = ((m_f - m_d) * m_buffer[m_p] + m_d * m_lastOut);
					float outValue = in + m_f * fOut;
					m_lastOut = fOut;
					m_buffer[m_p] = outValue;
					++m_p %= m_l;

					if(fabs(m_buffer[m_p]) < 0.00001f)
						m_buffer[m_p] = 0.0f;

					return outValue;
				}
			};

			struct Allpass
			{
				int   m_p,
				      m_l;
				float m_g;
				float* m_buffer;

				Allpass(int length, float gain = 0.7f)
				{
					m_l = length;
					m_g = gain;
					m_p = 0;
					m_buffer = new float[m_l];
					for(int i = 0; i < m_l; ++i)
						m_buffer[i] = 0.0f;
				}

				float process(float in)
				{
					float preIn = m_buffer[m_p] * m_g + in;
					float outValue = -m_g * preIn + m_buffer[m_p];
					m_buffer[m_p] = preIn;
					++m_p %= m_l;

					if(fabs(m_buffer[m_p]) < 0.00001f)
						m_buffer[m_p] = 0.0f;

					return outValue;
				}
			};

			FBCF* m_fbcf1;
			FBCF* m_fbcf2;
			FBCF* m_fbcf3;
			FBCF* m_fbcf4;
			FBCF* m_fbcf5;
			FBCF* m_fbcf6;
			FBCF* m_fbcf7;
			FBCF* m_fbcf8;

			Allpass* m_ap1;
			Allpass* m_ap2;
			Allpass* m_ap3;
			Allpass* m_ap4;

		public:
			enum Parameters
			{
				DRY = Ne::Effect::CUSTOM_BASE,
				WET,
				ROOM_SIZE,
				DAMP,

				N_PARAMETERS
			};

			Reverb();
			~Reverb();

			float process(float in);
			void onChange();
		};
	}
}

#endif /* NEON__EFFECTS__REVERB_HPP */

