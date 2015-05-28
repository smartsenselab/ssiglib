
#include <cameras/ip_video_camera_PTZ_Trend_Net7865.hpp>

int main(){

	ssf::IPVideoCameraPTZTrendNet7865 camera("172.22.22.210");

	//camera.check();
	//camera.setPAN(-10);
	//camera.setPAN(30);
	//camera.goHome();
	//camera.setZoom(-0.1);
	//camera.setPAN(-100);
	camera.setTILT(240);

	return 0;
}