#ifndef NEON__EFFECTS__CHORUS_HPP
#define NEON__EFFECTS__CHORUS_HPP

#include <core/effect.hpp>
#include <core/math.hpp>

namespace Ne
{
	namespace Effects
	{
		class Chorus
			: public Ne::Effect
		{
		private:
			struct ChorusFilter
		    {
		        enum FilterType
		        {
		            Lowpass = 0,
		            Highpass,
		            Bandpass,
		            Notch,
		            Peak
		        };

		        ChorusFilter(float cutoff, float resonance, FilterType filterType = Lowpass)
		        {
		            c0 = cutoff;
		            c1 = resonance;

		            _filterType = filterType;

		            _outValue = _yold1 = _yold2 = 0.0f;
		            _xold1 = _xold2 = 0.0f;
		            _outValue = 0.0f;
		        }

		        float process(float in)
		        {
		            // T vars
		            switch(_filterType)
		            {
		            case Lowpass:
		            case Highpass:
		                _t0 = cos(M_PI * (0.998f * c0 + 0.001f));
		                _t1 = sin(M_PI * (0.998f * c0 + 0.001f)) / (8.0f * (c1 + 0.001f));
		                _t2 = 1.0f + _t1;
		                break;
		            default: // BP, notch, peak
		                _t0 = cos(M_PI * (c0 * 0.998f + 0.001f));
		                _t1 = c1 * 0.998f + 0.001f;
		                break;
		            }

		            // A vars
		            switch(_filterType)
		            {
		            case Lowpass:
		                _a0 = (1.0f - _t0) / (2.0f * _t2);
		                _a1 = (1.0f - _t0) / _t2;
		                _a2 = (1.0f - _t0) / (2.0f * _t2);
		                break;
		            case Highpass:
		                _a0 = (1.0f + _t0) / (2.0f * _t2);
		                _a1 = -(1.0f + _t0) / _t2;
		                _a2 = (1.0f + _t0) / (2.0f * _t2);
		                break;
		            default:
		                _a0 = (1 - _t1) * sqrt(_t1 * (_t1 - 4.0f * _t0 + 2.0f) + 1.0f);
		                break;
		            }

		            // B vars
		            switch(_filterType)
		            {
		            case Lowpass:
		            case Highpass:
		                _b1 = -2.0f * _t0 / _t2;
		                _b2 = (1.0f - _t1) / _t2;
		                break;
		            default: // BP, notch, peak
		                _b1 = -2.0f * _t1 * _t0;
		                _b2 = _t1 * _t1;
		            }

		            if(_filterType == Lowpass || _filterType == Highpass)
		            {
		                _yold2 = _yold1;
		                _yold1 = _outValue;
		                _outValue = _a2 * _xold2 + _a1 * _xold1 + _a0 * in - _b2 * _yold2 - _b1 * _yold1;
		                _xold2 = _xold1;
		                _xold1 = in;
		                return _outValue;
		            }

		            _yold2 = _yold1;
		            _yold1 = _outValue;

					if(fabs(_xold2) < 0.00001f)
						_xold2 = 0.0f;
					if(fabs(_xold1) < 0.00001f)
						_xold1 = 0.0f;
					if(fabs(_yold2) < 0.00001f)
						_yold2 = 0.0f;
					if(fabs(_yold1) < 0.00001f)
						_yold1 = 0.0f;

		            _outValue = _a0 * in - _b2 * _yold2 - _b1 * _yold1;

		            if(_filterType == Peak)
		                _outValue += in;

		            else if(_filterType == Notch)
		                _outValue = in - _outValue;

		            return _outValue;
		        }

		        float c0, c1;

		        FilterType _filterType;

		        float _a0, _a1, _a2;
		        float _b1, _b2;
		        float _t0, _t1, _t2;
		        float _xold1, _xold2;
		        float _yold1, _yold2;
		        float _outValue;
		    };

		    float* m_buffer;
	        int    m_length;
	        float  m_depth;
	        int    m_position;
	        float  m_tapPos[3];
	        float  m_lfoStatus[3];
	        float  m_lfoFreq[3];
	        ChorusFilter* m_flt;

		public:
			enum Parameters
			{
				DELAY = Ne::Effect::CUSTOM_BASE,
				DEPTH,
				SPEED,
				DRY,
				WET,
				FILTER_CUTOFF,

				N_PARAMETERS
			};

			static const int MAX_SAMPLES = 1323;

			Chorus(ChorusFilter::FilterType filterType = ChorusFilter::Lowpass);
			~Chorus();

			float process(float in);
			void onChange();
		};
	}
}

#endif /* NEON__EFFECTS__CHORUS_HPP */
