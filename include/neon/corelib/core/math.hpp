#ifndef NEON__MATH_HPP
#define NEON__MATH_HPP

#include <cmath>

#ifndef M_PI
# define M_PI 3.14159265f
#endif /* M_PI */

#define NE__FFT_FORWARD 0
#define NE__FFT_INVERSE 1

#define clamp(x,a,b) (x<a?a:(x>b?b:x))

float randf();

void   ne__fft_transform(unsigned int num_samples, float* real_in, float* imag_in, float* real_out, float* imag_out, unsigned char dir);
float* ne__simple_ifft(unsigned int num_samples, float* amplitudes, float* phases);

#define fmin(a,b) (a<b?a:b)

#endif /* NEON__MATH_HPP */

