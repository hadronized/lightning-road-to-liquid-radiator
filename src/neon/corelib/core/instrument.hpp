#ifndef NEON__CORE__INSTRUMENT_HPP
#define NEON__CORE__INSTRUMENT_HPP

#include <core/parametrable.hpp>

namespace Ne
{
	enum InstrumentSlideMode
	{
		eNoSlide,
		eLegato,
		ePortamento
	};

	/* abstract */ class Instrument
		: public Parametrable
	{
	protected:
		float m_prevFrequency;
		float m_nextFrequency;
		float m_currFrequency;

		float m_currVelocity;

		unsigned int m_currNoteId;

		float m_velocity;

		bool  m_noteIsOn;

		InstrumentSlideMode m_slideMode;
		float               m_slideMu;

	public:
		enum Properties
		{
			SLIDE_RATE  = 0,
			PITCH,
			CUSTOM_BASE
		};

		Instrument(unsigned int nParameters);
		Instrument(const Instrument& i);
		virtual ~Instrument() {}

		virtual float       process() = 0;
		virtual Instrument* clone() = 0;

		virtual void        onNoteOn()  {}
		virtual void        onNoteOff() {}

		void                update();

		void                setSlideMode(InstrumentSlideMode slideMode);

		void                noteOn(int noteNo, float velocity);
		void                noteOff();
	};
}

#endif /* NEON__CORE__INSTRUMENT_HPP */
