#root/components/CMakeLists.txt

ssf_add_module(core REQUIRED BOOST system filesystem log log_setup thread date_time OPENCV opencv_core opencv_imgproc opencv_highgui opencv_world)
ssf_add_module(algorithms REQUIRED OPENCV opencv_core opencv_ml opencv_imgproc opencv_objdetect opencv_highgui opencv_world DEPENDENCIES core)
ssf_add_module(cameras DEPENDENCIES core)
ssf_add_module(fes DEPENDENCIES core)