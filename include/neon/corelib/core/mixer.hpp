#ifndef NEON__CORE__MIXER_HPP
#define NEON__CORE__MIXER_HPP

#define NEON_NUM_TRACKS         16
#define NEON_NUM_MASTER_EFFECTS 8

namespace Ne
{
	class Effect;
	class Track;

	class Mixer
	{
	private:
		/*struct GlobalControllerList
		{
			Controller* controller;
			GlobalControllerList* n;
		};

		GlobalControllerList* m_globalControllers;*/
		Effect* m_effects[NEON_NUM_MASTER_EFFECTS];
		Track*  m_tracks[NEON_NUM_TRACKS];

	public:
		Mixer();
		~Mixer();

		Track* track(unsigned int tId);

		void noteOn(unsigned int tId, unsigned int note, unsigned int velocity);
		void noteOff(unsigned int tId, unsigned int note);

		void setMasterEffectSlot(unsigned int id, Effect* fx);
		Effect* getMasterEffectSlot(unsigned int id);

		//void addGlobalController(Controller* c);
		//Controller* globalController(unsigned int id);

		void process(float cTime, float& l, float& r);
	};
}

#endif /* NEON__CORE__MIXER_HPP */
