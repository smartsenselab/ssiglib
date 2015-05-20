
#include <cameras\video_camera_PTZ_Trend_Net7865.hpp>

int main(){

	ssf::VideoCameraPTZTrendNet7865 camera("ip");

	camera.getCurrentPan();

	return 0;
}