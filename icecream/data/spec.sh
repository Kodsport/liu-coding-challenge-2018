#!/bin/bash
rm -rf secret
mkdir secret

g++ -std=gnu++11 gen.cpp -o gen
g++ -std=gnu++11 ../submissions/accepted/icecream_mw.cpp -o sol
g++ -std=gnu++11 ../submissions/time_limit_exceeded/icecream_mw.cpp -o bruteforce

CURCASE=-1

# Arguments: testcasename type seed n k a
testcase() {
    CURCASE=$((CURCASE + 1))
  	NAME=$1
  	echo Case $NAME
	./gen $2 $3 $4 $5 $6 > "secret/$NAME.in"
	(./sol < "secret/$NAME.in") > "secret/$NAME.ans"
#	(./bruteforce < "secret/$NAME.in") > "secret/$NAME.ans2"
#	diff "secret/$NAME.ans" "secret/$NAME.ans2"
}

testcase cycles-small-1 cycles 2298 7 5 1
testcase cycles-small-2 cycles 2299 192 6 1
testcase cycles-small-3 cycles 2300 10 6 2
testcase cycles-small-4 cycles 2301 5182731 8 3
testcase cycles-small-5 cycles 2302 1423 10 4

testcase cycles-medium-1 cycles 2303 1029 54 1
testcase cycles-medium-2 cycles 2304 2991 19 4
testcase cycles-medium-3 cycles 2305 1982 65 2
testcase cycles-medium-4 cycles 2306 19 98 2
testcase cycles-medium-5 cycles 2307 9283741 8 2

testcase cycles-large-1 cycles 2308 989107991 99 2
testcase cycles-large-2 cycles 2309 991189692 97 1
testcase cycles-large-3 cycles 2310 999878553 100 10
testcase cycles-large-4 cycles 2311 995428921 98 3

testcase random-small-1 random 3210 2 2 10
testcase random-small-2 random 3211 4 4 10
testcase random-small-3 random 3212 3 5 1
testcase random-small-4 random 3213 1 97 200
testcase random-small-5 random 3214 6842938 1 93
testcase random-small-6 random 3215 1 1 5

testcase random-medium-1 random 1982 8273 73 96
testcase random-medium-2 random 1983 913 92 2

testcase random-large-1 random 1984 998919847 99 2
testcase random-large-2 random 1985 879857483 100 97
testcase random-large-3 random 1986 1000000000 100 158

testcase just_cone-small-1 just_cone 2751 1 1 3
testcase just_cone-small-2 just_cone 2752 56 3 81
testcase just_cone-small-3 just_cone 2753 2 81 8

testcase just_cone-medium-1 just_cone 2754 1928 81 17

testcase just_cone-large-1 just_cone 2755 999859381 95 80
testcase just_cone-large-2 just_cone 2756 58372813 53 4

testcase one_scoop-small-1 one_scoop 1382 3 3 51
testcase one_scoop-small-2 one_scoop 1383 105 5 1

testcase one_scoop-medium-1 one_scoop 1384 1029 56 102
testcase one_scoop-medium-2 one_scoop 1385 2192 73 2

testcase one_scoop-large-1 one_scoop 1386 989483213 98 54
testcase one_scoop-large-2 one_scoop 1387 931534352 99 3

testcase k_scoops-small-1 msmall_scoops 7182 15 4 4

testcase k_scoops-medium-1 msmall_scoops 7183 1024 100 100
testcase k_scoops-medium-2 msmall_scoops 7184 3017 53 53

testcase k_scoops-large-1 msmall_scoops 7185 1000000000 100 100
testcase k_scoops-large-2 msmall_scoops 7185 987875381 99 99

testcase msmall_scoops-small-1 msmall_scoops 6189 731 9 7
testcase msmall_scoops-small-2 msmall_scoops 6190 14 17 14
testcase msmall_scoops-small-3 msmall_scoops 6191 8 15 9
testcase msmall_scoops-small-4 msmall_scoops 6192 512 17 2

testcase msmall_scoops-medium-1 msmall_scoops 6193 2154 42 33
testcase msmall_scoops-medium-2 msmall_scoops 6194 1998 61 13

testcase msmall_scoops-large-1 msmall_scoops 6195 957343583 98 96
testcase msmall_scoops-large-2 msmall_scoops 6196 999995832 100 73
testcase msmall_scoops-large-3 msmall_scoops 6197 857343593 87 3

testcase mlarge_scoops-small-1 mlarge_scoops 4888 19 4 17
testcase mlarge_scoops-small-2 mlarge_scoops 4889 60 20 41
testcase mlarge_scoops-small-3 mlarge_scoops 4893 35 5 31

testcase mlarge_scoops-medium-1 mlarge_scoops 4891 2257 61 2197
testcase mlarge_scoops-medium-2 mlarge_scoops 4892 3500 50 3452
testcase mlarge_scoops-medium-3 mlarge_scoops 4894 1630 17 1623

testcase mlarge_scoops-large-1 mlarge_scoops 4895 9100928 97 9100832
testcase mlarge_scoops-large-2 mlarge_scoops 4896 10000000 100 9999902
testcase mlarge_scoops-large-3 mlarge_scoops 4897 7766381 7 7766378
testcase mlarge_scoops-large-4 mlarge_scoops 4898 9730234525 83 973023443

