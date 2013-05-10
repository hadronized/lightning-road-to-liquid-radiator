#ifndef NEON__CORE__AUTOMATIONCLIPINSTANCE_HPP
#define NEON__CORE__AUTOMATIONCLIPINSTANCE_HPP
/*
namespace Ne
{
	class AutomationClip;

	class AutomationClipInstance
		: public Ne::Controller
	{
	private:
		float m_output;

		AutomationClip* m_clip;
		float m_delta;

	public:
		enum ExposedValues
		{
			OUTPUT = 0,
			N_EXPOSED_VALUES
		};

		AutomationClipInstance(AutomationClip* clip, float delta)
			: Ne::Controller(N_EXPOSED_VALUES)
		{
			m_clip = clip;
			m_delta = delta;
			m_output = 0.0f;

			m_exposedValues[OUTPUT] = &m_output;
		}

		void process(float cTime)
		{
			if( ((cTime - m_delta) >= 0) && ((cTime - m_delta) < m_clip->duration()) )
			{
				m_output = m_clip->automate(cTime - m_delta);
				processLinks();
			}
		}
	};
}
*/
#endif /* NEON__CORE__AUTOMATIONCLIPINSTANCE_HPP */
