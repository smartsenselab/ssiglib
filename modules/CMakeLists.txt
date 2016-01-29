#root/components/CMakeLists.txt

ssig_add_module(core REQUIRED OPENCV opencv_core opencv_imgproc opencv_imgcodecs opencv_highgui)
ssig_add_module(ml OPENCV opencv_core opencv_ml opencv_imgproc opencv_objdetect opencv_highgui opencv_world DEPENDENCIES core)
ssig_add_module(descriptors CUDA OPENCV opencv_core opencv_ml opencv_imgproc opencv_objdetect opencv_highgui opencv_world DEPENDENCIES core)
ssig_add_module(hashing OPENCV opencv_core DEPENDENCIES core ml)
#ssf_add_module(optimization OPENCV opencv_core DEPENDENCIES core)
