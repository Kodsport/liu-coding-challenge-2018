#!/bin/bash

g++ -std=c++17 -fsanitize=address,undefined -O2 gen.cpp -o generator

./generator 8 5 random 0.8 0.1 0.1 random_goal > secret/small-1.in
./generator 10 10 random 0.8 0.15 0.05 random_goal > secret/small-2.in
./generator 20 20 random 0.2 0.2 0.6 random_goal > secret/small-3.in
./generator 15 15 labyrinth 0.5 0 0.5 random_goal > secret/small-4.in
./generator 23 27 labyrinth 0.0 0 1.0 random_goal > secret/small-5.in
./generator 40 40 long_path 0.0 0 1.0 random_goal > secret/small-6.in
./generator 37 37 long_path 0.0 0 1.0 fixed_goal 35 35 > secret/small-7.in

./generator 1000 1000 random 0.995 0.005 0.0 random_goal > secret/random-1.in
./generator 1000 1000 random 0.1 0.0 0.9 random_goal > secret/random-2.in
./generator 1000 1000 random 0.997 0.001 0.002 random_goal > secret/random-3.in
./generator 1000 986 random 0.8 0.1 0.1 random_goal > secret/random-4.in
./generator 999 1000 random 0.34 0.33 0.33 random_goal > secret/random-5.in
./generator 129 317 random 0.99 0.01 0.0 random_goal > secret/random-6.in
./generator 987 995 random 0.65 0.1 0.25 fixed_goal 985 1 > secret/random-7.in
./generator 1000 1000 random 0.0 0.0 1.0 random_goal > secret/random-8.in
./generator 1000 1000 random 1.0 0.0 0.0 random_goal > secret/random-9.in
./generator 1000 1000 random 0.0 1.0 0.0 random_goal > secret/random-10.in

./generator 3 1000 random 1.0 0.0 0.0 random_goal > secret/narrow-1.in
./generator 1000 3 random 0.0 0.9 0.1 random_goal > secret/narrow-2.in
./generator 8 1000 random 0.9 0.04 0.06 random_goal > secret/narrow-3.in

./generator 1000 1000 labyrinth 0.0 0 1.0 random_goal > secret/labyrinth-1.in
./generator 1000 1000 labyrinth 1.0 0 0.0 random_goal > secret/labyrinth-2.in
./generator 1000 1000 labyrinth 0.01 0 0.99 random_goal > secret/labyrinth-3.in
./generator 894 1000 labyrinth 0.005 0.005 0.99 random_goal > secret/labyrinth-4.in
./generator 1000 999 labyrinth 0.0 0 1.0 random_goal > secret/labyrinth-5.in
./generator 1000 1000 labyrinth 0.0 0 1.0 fixed_goal 1 1 > secret/labyrinth-6.in

./generator 1000 1000 long_path 0.0 0 1.0 random_goal > secret/long-path-1.in
./generator 999 999 long_path 1.0 0 0.0 random_goal > secret/long-path-2.in
./generator 865 937 long_path 0.0 0 1.0 random_goal > secret/long-path-3.in
./generator 998 998 long_path 0.0 0 1.0 fixed_goal 1 1 > secret/long-path-4.in
