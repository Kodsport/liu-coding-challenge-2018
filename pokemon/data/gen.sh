#!/bin/bash

g++ -std=c++17 -O2 gen.cpp -o generator

./generator 8 5 random 0.8 0.1 0.1 random_goal > data/small-1.in
./generator 10 10 random 0.8 0.15 0.05 random_goal > data/small-2.in
./generator 20 20 random 0.2 0.2 0.6 random_goal > data/small-3.in
./generator 15 15 labyrinth 0.5 0 0.5 random_goal > data/small-4.in
./generator 23 27 labyrinth 0.0 0 1.0 random_goal > data/small-5.in
./generator 40 40 long_path 0.0 0 1.0 random_goal > data/small-6.in
./generator 37 37 long_path 0.0 0 1.0 fixed_goal 35 35 > data/small-7.in
./generator 10 5 rows 0.0 0 1.0 random_goal > data/small-8.in

./generator 1000 1000 random 0.995 0.005 0.0 random_goal > data/random-1.in
./generator 1000 1000 random 0.1 0.0 0.9 random_goal > data/random-2.in
./generator 1000 1000 random 0.997 0.001 0.002 random_goal > data/random-3.in
./generator 1000 986 random 0.8 0.1 0.1 random_goal > data/random-4.in
./generator 999 1000 random 0.34 0.33 0.33 random_goal > data/random-5.in
./generator 129 317 random 0.99 0.01 0.0 random_goal > data/random-6.in
./generator 987 995 random 0.65 0.1 0.25 fixed_goal 985 1 > data/random-7.in
./generator 1000 1000 random 0.0 0.0 1.0 random_goal > data/random-8.in
./generator 1000 1000 random 1.0 0.0 0.0 random_goal > data/random-9.in
./generator 1000 1000 random 0.0 1.0 0.0 random_goal > data/random-10.in

./generator 3 1000 random 1.0 0.0 0.0 random_goal > data/narrow-1.in
./generator 1000 3 random 0.0 0.9 0.1 random_goal > data/narrow-2.in
./generator 8 1000 random 0.9 0.04 0.06 random_goal > data/narrow-3.in

./generator 1000 1000 labyrinth 0.0 0 1.0 random_goal > data/labyrinth-1.in
./generator 1000 1000 labyrinth 1.0 0 0.0 random_goal > data/labyrinth-2.in
./generator 1000 1000 labyrinth 0.01 0 0.99 random_goal > data/labyrinth-3.in
./generator 894 1000 labyrinth 0.005 0.005 0.99 random_goal > data/labyrinth-4.in
./generator 1000 999 labyrinth 0.0 0 1.0 random_goal > data/labyrinth-5.in
./generator 1000 1000 labyrinth 0.0 0 1.0 fixed_goal 1 1 > data/labyrinth-6.in

./generator 1000 1000 long_path 0.0 0 1.0 random_goal > data/long-path-1.in
./generator 999 999 long_path 1.0 0 0.0 random_goal > data/long-path-2.in
./generator 865 937 long_path 0.0 0 1.0 random_goal > data/long-path-3.in
./generator 998 998 long_path 0.0 0 1.0 fixed_goal 1 1 > data/long-path-4.in

./generator 1000 1000 rows 0.0 0 1.0 random_goal > data/rows-1.in
