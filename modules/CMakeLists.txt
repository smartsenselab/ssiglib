#root/components/CMakeLists.txt

ssf_add_module(core REQUIRED BOOST system filesystem log log_setup thread date_time OPENCV opencv_core opencv_imgproc opencv_highgui)
ssf_add_module(algorithms REQUIRED OPENCV opencv_ts300 opencv_world300 opencv_core opencv_imgproc opencv_highgui DEPENDENCIES core)
ssf_add_module(cameras DEPENDENCIES core)
ssf_add_module(fes DEPENDENCIES core)