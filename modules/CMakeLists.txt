#root/components/CMakeLists.txt

ssf_add_module(core REQUIRED OPENCV opencv_core opencv_imgproc opencv_highgui)
#ssf_add_module(algorithms REQUIRED OPENCV opencv_core opencv_ml opencv_imgproc opencv_objdetect opencv_highgui opencv_world DEPENDENCIES core)
ssf_add_module(ml REQUIRED OPENCV opencv_core opencv_ml opencv_imgproc opencv_objdetect opencv_highgui opencv_world DEPENDENCIES core)