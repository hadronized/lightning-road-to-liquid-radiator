#ifndef NEON__INSTRUMENTS__MULTITAPSAMPLER_HPP
#define NEON__INSTRUMENTS__MULTITAPSAMPLER_HPP

#include <core/instrument.hpp>

namespace Ne
{
	class  Property;
	struct Sample;

	namespace Instruments
	{
		class MultitapSampler
			: public Ne::Instrument
		{
		private:
			enum EnvelopeState
			{
				eInactive = 0,
				eAttack,
				eDecay,
				eSustain,
				eRelease
			};

			Sample* m_sample;
			float   m_readOffset[3];
			bool    m_loops;

			EnvelopeState m_envelopeState;
			float         m_envelopeValue;

		public:
			enum Parameters
			{
				ATTACK = Ne::Instrument::CUSTOM_BASE,
				DECAY,
				SUSTAIN,
				RELEASE,
				DETUNE,

				N_PARAMETERS
			};

			MultitapSampler(Sample* sample, bool loops = true);
			MultitapSampler(const MultitapSampler& m);
			~MultitapSampler();

			Ne::Instrument* clone();

			float process();

			void onNoteOn();
			void onNoteOff();
		};
	}
}

#endif /* NEON__INSTRUMENTS__MULTITAPSAMPLER_HPP */

