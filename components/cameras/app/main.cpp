
#include <cameras/ip_video_camera_PTZ_Trend_Net7865.hpp>
#include <cameras/ip_fixa.hpp>
#include <cameras/ip_onvif_ptz.hpp>

int main(){

	ssf::OnvifPTZ camera2("172.22.22.221");
	//ssf::IPVideoCameraPTZTrendNet7865 camera("172.22.22.210");
	//camera.check();
	//camera.setPAN(-10);
	//camera.setPAN(30);
	//camera.goHome();
	camera2.setZoom(100);
	camera2.setPAN(-80);
	camera2.setTILT(-80);
	camera2.getPosition();
	//camera.setPAN(-100);
//	camera.setTILT(240);

	return 0;
}