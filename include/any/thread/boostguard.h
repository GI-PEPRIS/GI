
#ifndef JTC_BOOSTGUARD_H
#define JTC_BOOSTGUARD_H
#include "boost/function.hpp"

class CAnyBoostGuard{
public:
	boost::function0<void> const m_function;
	bool m_is_active;
	CAnyBoostGuard(boost::function0<void> const & call_on_exit):m_function(call_on_exit),m_is_active(true){
	}
	~CAnyBoostGuard(){
		if(m_is_active&& m_function){
			m_function();
		}
	}
	void disable(){
		m_is_active=false;
	}
};
#endif