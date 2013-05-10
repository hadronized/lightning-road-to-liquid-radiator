#ifndef NEON__INSTRUMENTS__SAMPLER_HPP
#define NEON__INSTRUMENTS__SAMPLER_HPP

#include <core/instrument.hpp>
/*#include <core/controller.hpp>*/

namespace Ne
{
	class  Property;
	struct Sample;

	namespace Instruments
	{
		class Sampler
			: public Ne::Instrument/*,
			  public Ne::Controller*/
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
			float   m_readOffset;
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

				N_PARAMETERS
			};

			enum ExposedValues
			{
				ENVELOPE_OUT = 0,
				N_EXPOSED_VALUES
			};

			Sampler(Sample* sample, bool loops = true);
			Sampler(const Sampler& s);
			~Sampler();

			Ne::Instrument* clone();

			float process();

			void onNoteOn();
			void onNoteOff();
		};
	}
}

#endif /* NEON__INSTRUMENTS__SAMPLER_HPP */
