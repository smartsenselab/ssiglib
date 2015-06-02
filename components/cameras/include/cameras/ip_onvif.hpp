#ifndef _SSF_CORE_IP_ONVIF_HPP_
#define _SSF_CORE_IP_ONVIF_HPP_

#include "cameras/ip_fixa.hpp"

namespace ssf{

	class Onvif : public CameraFixa{
	
	public:
		CAMERAS_EXPORT Onvif(void);
		CAMERAS_EXPORT virtual ~Onvif(void);
		CAMERAS_EXPORT Onvif(const Onvif& rhs);
		CAMERAS_EXPORT Onvif& operator=(const Onvif& rhs);

	private:
		//private members

	};

}

#endif // !_SSF_CORE_IP_ONVIF_HPP_