#ifndef NEON__CORE__WAVETABLE_HPP
#define NEON__CORE__WAVETABLE_HPP

#define WT_SINE     10
#define WT_SAW      11
#define WT_TRIANGLE 12
#define WT_SQUARE   13
#define WT_PWM_20   14
#define WT_PADSYNTH 15
#define WT_NOISE    16

namespace Ne
{
	struct Sample;

	class Wavetable
	{
	private:
		struct WavetableEntry
		{
			unsigned int    eid;
			Sample*         sample;

			WavetableEntry* n;
		};

		WavetableEntry* m_entries;

	public:
		Wavetable();
		~Wavetable();

		void push(unsigned int id, float baseFrequency, unsigned int length, float* data);
		Sample* fetch(unsigned int id);
	};
}

#endif /* NEON__CORE__WAVETABLE_HPP */
