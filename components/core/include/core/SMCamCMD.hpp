#ifndef _SSF_CORE_SMCAMCMD_HPP_
#define _SSF_CORE_SMCAMCMD_HPP_

#include "SMData.hpp"

namespace ssf{

	enum CAM_CMD_TYPE {
		CAM_LEFT,
		CAM_RIGHT,
		CAM_UP,
		CAM_DOWN,
		CAM_ZOOMIN,
		CAM_ZOOMOUT,
		CAM_VELOCITY,
		CAM_RESOLUTION,
		CAM_FPS
};

	class SMCamCMD : public SMData {
		friend class ModControlCameraIP;
		
		CAM_CMD_TYPE type;
		union{
			int angle;
			int level;
			int velocity;
			int resolution;
			int fps;
		} params;

	public:
		
		SMCamCMD();
		
		//pan
		static SMCamCMD* Left(int angle) {
			SMCamCMD *cmd = new SMCamCMD();
			cmd->params.angle = angle;
			cmd->type = CAM_CMD_TYPE::CAM_LEFT;
			return cmd;
		}
		
		static SMCamCMD* Right(int angle) {
			SMCamCMD *cmd = new SMCamCMD();
			cmd->params.angle = angle;
			cmd->type = CAM_CMD_TYPE::CAM_RIGHT;
			return cmd;
		}

		// tilt
		static SMCamCMD* Up(int angle) {
			SMCamCMD *cmd = new SMCamCMD();
			cmd->params.angle = angle;
			cmd->type = CAM_CMD_TYPE::CAM_UP;
			return cmd;
		}

		static SMCamCMD* Down(int angle) {
			SMCamCMD *cmd = new SMCamCMD();
			cmd->params.angle = angle;
			cmd->type = CAM_CMD_TYPE::CAM_DOWN;
			return cmd;
		}

		// zoom
		static SMCamCMD* Zoom(int level) {
			SMCamCMD *cmd = new SMCamCMD();
			cmd->params.level = level;
			cmd->type = CAM_CMD_TYPE::CAM_ZOOMIN;
			return cmd;
		}

		//Resolution
		static SMCamCMD* Resolution(int level) {
			SMCamCMD *cmd = new SMCamCMD();
			cmd->params.resolution = level;
			cmd->type = CAM_CMD_TYPE::CAM_RESOLUTION;
			return cmd;
		}

		//Fps
		static SMCamCMD* Fps(int level) {
			SMCamCMD *cmd = new SMCamCMD();
			cmd->params.fps = level;
			cmd->type = CAM_CMD_TYPE::CAM_FPS;
			return cmd;
		}

		// velocity
		static SMCamCMD* Velocity(int velocity) {
			SMCamCMD *cmd = new SMCamCMD();
			cmd->params.velocity = velocity;
			cmd->type = CAM_CMD_TYPE::CAM_VELOCITY;
			return cmd;
		}


		virtual ~SMCamCMD(void);
		SMCamCMD(const SMCamCMD& rhs);
		SMCamCMD& operator=(const SMCamCMD& rhs);

	private:
		//private members
	};

}

#endif // !_SSF_CORE_SMCAMCMD_HPP_