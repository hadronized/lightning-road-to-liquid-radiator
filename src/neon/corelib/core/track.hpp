#ifndef NEON__CORE__TRACK_HPP
#define NEON__CORE__TRACK_HPP

#define NEON_POLYPHONY     16
#define NEON_EFFECT_SLOTS  8

#define NEON_VOICE_MAX_AGE 1000000000

#include <core/parametrable.hpp>

namespace Ne
{
	class Effect;
	class Instrument;

	class Track
		: public Parametrable
	{
	private:
		struct Voice
		{
			Instrument* instrument;
			unsigned int note;
			int age;
		};

		Voice*    m_voices[NEON_POLYPHONY];
		Effect*   m_effects[NEON_EFFECT_SLOTS];

		bool      m_monophonic;

	public:
		enum Parameters
		{
			VOLUME = 0,
			PAN,

			N_PARAMETERS
		};

		Track();
		~Track();

		Instrument* instrument();
		void setInstrument(Instrument* ins, bool monophonic = false);

		Effect* effectSlot(unsigned int id);
		void setEffectSlot(unsigned int id, Effect* fx);

		void noteOn(unsigned int noteNo, int velocity);
		void noteOff(unsigned int noteNo);

		void process(float& l, float& r);
	};
}

#endif /* NEON__CORE__TRACK_HPP */
