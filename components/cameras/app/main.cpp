
#include <cameras\video_camera_PTZ_Trend_Net7865.hpp>

int main(){

	ssf::VideoCameraPTZTrendNet7865 camera("172.22.22.210");

	camera.setPAN(30);
	//camera.setPAN(-100);
	//camera.setTILT(100);

	return 0;
}