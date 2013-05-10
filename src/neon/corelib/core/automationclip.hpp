#ifndef NEON__CORE__AUTOMATIONCLIP_HPP
#define NEON__CORE__AUTOMATIONCLIP_HPP
/*
#include <core/controller.hpp>

namespace Ne
{
	enum AutomationType
	{
		eHold,
		eLinear,
		eCosine,

		eUndefined
	};

	struct AutomationPoint
	{
		float time;
		float value;

		AutomationType type;
	};

	class AutomationClip
	{
	private:
		struct AutomationClipPoint
		{
			AutomationPoint p;
			AutomationClipPoint* n;
		};

		AutomationClipPoint* m_points;
		float m_duration;

	public:
		AutomationClip();
		~AutomationClip();

		void pushPoint(float time, float value, AutomationType type);
		float duration() const;
		float automate(float time);
	};
}
*/
#endif /* NEON__CORE__AUTOMATIONCLIP_HPP */
