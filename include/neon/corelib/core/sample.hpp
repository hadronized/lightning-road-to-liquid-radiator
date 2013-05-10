#ifndef NEON__CORE__SAMPLE_HPP
#define NEON__CORE__SAMPLE_HPP

#define NE_PADSYNTH_HARMONICS        512
#define NE_PADSYNTH_SAMPLE_LENGTH    262144
#define NE_PADSYNTH_SAMPLE_FREQUENCY 55.0f

namespace Ne
{
	struct Sample
	{
		float baseFrequency;
		unsigned int length;
		float* data;

		static void expand(const signed char* input, unsigned int inputLength, float** output, unsigned int* outputLength);
		static void compress(const signed char* input, unsigned int inputLength, signed char** output, unsigned int* outputLength);
		static float* generatePadsynth();
	};
}

#endif /* NEON__CORE__SAMPLE_HPP */
