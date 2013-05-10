#ifndef NEON__CORE__PARAMETRABLE_HPP
#define NEON__CORE__PARAMETRABLE_HPP

namespace Ne
{
	class Parametrable
	{
	protected:
		float* m_parameters;
		float* m_parametersAbsolute;
		float* m_parametersRelative;
		unsigned int m_nParameters;

		bool m_isClone;

		void f_onGlobalChange();

	public:
		enum ValueType
		{
			ABSOLUTE = 0,
			RELATIVE
		};

		Parametrable(unsigned int nParameters);
		Parametrable(const Parametrable& p);
		~Parametrable();

		void   set(unsigned int parameterId, float value, ValueType type = ABSOLUTE);
		float  get(unsigned int parameterId);
		float* ptr(unsigned int parameterId);

		virtual void onChange() {}
	};
}

#endif /* NEON__CORE__PARAMETRABLE_HPP */

