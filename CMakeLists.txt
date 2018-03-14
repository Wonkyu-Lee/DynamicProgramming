cmake_minimum_required(VERSION 3.8)
project(DynamicProgramming)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp
        longest_common_subsequence.cpp
        longest_repeating_subsequence.cpp
        binomial_coefficient.cpp
        largest_sum_contiguous_subarray.cpp
        ugly_numbers.cpp
        maximum_size_square_submatrix.cpp
        longest_increasing_subsequence.cpp coin_change.cpp
        zero_one_knapsack.cpp
        cutting_rod.cpp
        subset_sum.cpp
        min_jumps.cpp
        car_assembly.cpp
        maximum_sum_increasing_subsequence.cpp
        optimal_binary_search_tree.cpp
        edit_distance.cpp
        matrix_chain_multiplication.cpp unbounded_knapsack.cpp)
add_executable(DynamicProgramming ${SOURCE_FILES})