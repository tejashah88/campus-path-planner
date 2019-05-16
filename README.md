# campus-path-planner
An OpenCV GUI application for computing the shortest path (via Dijkstra's) between two points on a campus map. This was done as my final project for my COMSC-210 class in DVC. Tested with OpenCV 3.2.0 but should work for later versions.

## How to use
1. Clone this repository
2. Supply your `map.png` and a black and white `outline.png` that represents the valid areas that can be traversed on.
3. Compile the program (assuming that you've already set up OpenCV)
   1. If you have setup OpenCV with `pkg-config`, you can compile with `build_global.sh`
   2. Otherwise, you'll need to provide the following shared object files (ending with .so) in the `libs/` folder before running `build_local.sh`
      1. `libopencv_core.so`
      2. `libopencv_highgui.so`
      3. `libopencv_imgproc.so`
      4. `libopencv_imgcodecs.so`
4. Run the program with `./path-planner.app`.

Note: The current implementation does not scale well for relatively large images (due to the use of an adjacency matrix), which means that you should expect a high memory usage. As a result, the RESIZE_FACTOR parameter controls how big the graph is relative to the input image.