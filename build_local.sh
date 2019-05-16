#!/bin/bash
g++ `find src/ -name '*.cpp'` -L. -l:libopencv_core.so -l:libopencv_highgui.so -l:libopencv_imgcodecs.so -l:libopencv_imgproc.so -g -o path-planner.app