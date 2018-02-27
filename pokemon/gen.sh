#!/bin/bash

g++ -std=c++17 -O2 gen.cpp -o generator

./generator 8 5 random 0.8 0.1 0.1 random_goal > data/small-1
./generator 10 10 random 0.8 0.15 0.05 random_goal > data/small-2
./generator 20 20 random 0.2 0.2 0.6 random_goal > data/small-3
./generator 15 15 labyrinth 0.5 0 0.5 random_goal > data/small-4
./generator 23 27 labyrinth 0.0 0 1.0 random_goal > data/small-5
./generator 40 40 long_path 0.0 0 1.0 random_goal > data/small-6
./generator 37 37 long_path 0.0 0 1.0 fixed_goal 35 35 > data/small-7

./generator 1000 1000 random 0.995 0.005 0.0 random_goal > data/random-1
./generator 1000 1000 random 0.1 0.0 0.9 random_goal > data/random-2
./generator 1000 1000 random 0.997 0.001 0.002 random_goal > data/random-3
./generator 1000 986 random 0.8 0.1 0.1 random_goal > data/random-4
./generator 999 1000 random 0.34 0.33 0.33 random_goal > data/random-5
./generator 129 317 random 0.99 0.01 0.0 random_goal > data/random-6
./generator 987 995 random 0.65 0.1 0.25 fixed_goal 985 1 > data/random-7
./generator 1000 1000 random 0.0 0.0 1.0 random_goal > data/random-8
./generator 1000 1000 random 1.0 0.0 0.0 random_goal > data/random-9
./generator 1000 1000 random 0.0 1.0 0.0 random_goal > data/random-10

./generator 3 1000 random 1.0 0.0 0.0 random_goal > data/narrow-1
./generator 1000 3 random 0.0 0.9 0.1 random_goal > data/narrow-2
./generator 8 1000 random 0.9 0.04 0.06 random_goal > data/narrow-3

./generator 1000 1000 labyrinth 0.0 0 1.0 random_goal > data/labyrinth-1
./generator 1000 1000 labyrinth 1.0 0 0.0 random_goal > data/labyrinth-2
./generator 1000 1000 labyrinth 0.01 0 0.99 random_goal > data/labyrinth-3
./generator 894 1000 labyrinth 0.005 0.005 0.99 random_goal > data/labyrinth-4
./generator 1000 999 labyrinth 0.0 0 1.0 random_goal > data/labyrinth-5
./generator 1000 1000 labyrinth 0.0 0 1.0 fixed_goal 1 1 > data/labyrinth-6

./generator 1000 1000 long_path 0.0 0 1.0 random_goal > data/long-path-1
./generator 999 999 long_path 1.0 0 0.0 random_goal > data/long-path-2
./generator 865 937 long_path 0.0 0 1.0 random_goal > data/long-path-3
./generator 998 998 long_path 0.0 0 1.0 fixed_goal 1 1 > data/long-path-4
