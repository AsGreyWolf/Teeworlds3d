#!/bin/sh
g++ -o teeworlds3d -Ofast -DLINUX --std=c++11 src/shared/*.cpp src/shared/world/*.cpp src/client/*.cpp src/client/components/*.cpp src/client/components/graphics/*.cpp -lGL -lGLEW -lSDL2 -lSDL2_image -lSDL2_ttf -lGLU