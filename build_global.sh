#!/bin/bash
g++ `find src/ -name '*.cpp'` `pkg-config --cflags --libs opencv` -g -o path-planner.app