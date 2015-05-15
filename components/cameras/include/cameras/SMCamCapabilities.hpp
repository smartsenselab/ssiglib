#ifndef _SSF_CORE_SMCAMCAPABILITIES_HPP_
#define _SSF_CORE_SMCAMCAPABILITIES_HPP_

#include "SMData.hpp"

namespace ssf{

	class SMCamCapabilities : public SMData{
		friend class ModControlCameraIP;
		//Mutex threadlock;

		bool pan;
		bool tilt;
		bool zoom;
		bool velocity;//
		bool resolution;//
		bool fps;//

	public:
		SMCamCapabilities(bool pan = false, bool tilt = false, bool zoom = false, bool velocity = false) :
			pan(pan),
			tilt(tilt),
			zoom(zoom),
			velocity(velocity)
				{}
			//Tenho que setar o tipo do modulo?
			bool isPanCapable() {
				return pan;
			}

			bool isTiltCapable() {
				return tilt;
			}

			bool isZoomCapable() {
				return zoom;
			}

			bool isVelocityCapable() {
				return velocity;
			}

			bool isResolutionCapable() {
				return resolution;
			}
			bool isFpsCapable(){
				return fps;
			}

		virtual ~SMCamCapabilities(void);
		
		SMCamCapabilities(const SMCamCapabilities& rhs);
		
		SMCamCapabilities& operator=(const SMCamCapabilities& rhs);

	private:
		//private members

	};

}

#endif // !_SSF_CORE_SMCAMCAPABILITIES_HPP_