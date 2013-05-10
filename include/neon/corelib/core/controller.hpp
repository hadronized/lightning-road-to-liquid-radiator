#ifndef NE__CORE__CONTROLLER_HPP
#define NE__CORE__CONTROLLER_HPP

namespace Ne
{
	class Controller
	{
	private:
		struct ControllerLink
		{
			unsigned int valueId;
			float* target;
			unsigned char type;

			float rangeMin;
			float rangeMax;

			ControllerLink* n;
		};

	protected:
		float**         m_exposedValues;
		unsigned int    m_nExposedValues;

		ControllerLink* m_links;

	public:
		enum LinkType {
			ABSOLUTE = 0,
			RELATIVE
		};
		Controller(unsigned int nExposedValues);
		void link(unsigned int valueId, float* target, LinkType type, float rangeMin = 0.0f, float rangeMax = 1.0f);

		virtual void process(float cTime) {};

		void processLinks();
	};
}

#endif /* NE__CORE__CONTROLLER_HPP */

