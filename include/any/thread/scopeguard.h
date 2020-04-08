#include "boost/function.hpp"

class CAnyScopeGuard{
public:
	boost::function0<void> const m_function;
	bool m_is_active;
	CAnyScopeGuard(boost::function0<void> const & call_on_exit):m_function(call_on_exit),m_is_active(true){
	}
	~CAnyScopeGuard(){
		if(m_is_active&& m_function){
			m_function();
		}
	}
	void disable(){
		m_is_active=false;
	}
};