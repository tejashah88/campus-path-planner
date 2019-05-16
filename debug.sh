#!/bin/bash
valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --track-origins=yes --num-callers=30 -v ./app