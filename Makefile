exp1_1: experiment_1/1_starting_with_ab/starting_with_ab.c
	gcc -o experiment_1/1_starting_with_ab/starting_with_ab.out experiment_1/1_starting_with_ab/starting_with_ab.c

exp1_2: experiment_1/2_containing_11/containing_11.c
	gcc -o experiment_1/2_containing_11/containing_11.out experiment_1/2_containing_11/containing_11.c

exp1_3: experiment_1/3_ending_with_100/ending_with_100.c
	gcc -o experiment_1/3_ending_with_100/ending_with_100.out experiment_1/3_ending_with_100/ending_with_100.c


exp2_1: experiment_2/1_ending_with_001/ending_with_001.cpp
	g++ \
		-o experiment_2/1_ending_with_001/ending_with_001.out \
		-I experiment_2/include \
		-std=c++17 \
		experiment_2/1_ending_with_001/ending_with_001.cpp \
		experiment_2/common.cpp \
		experiment_2/State.cpp