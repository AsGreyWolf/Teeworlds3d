#!/bin/sh
g++ -o teeworlds3d -O3 -DLINUX --std=c++11 src/client/*.cpp src/client/components/*.cpp src/client/components/graphics/*.cpp -lGL -lGLEW -lSDL2 -lSDL2_image -lSDL2_ttf -lGLU
