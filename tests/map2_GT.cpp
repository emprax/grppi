/**
* @version		GrPPI v0.1
* @copyright		Copyright (C) 2017 Universidad Carlos III de Madrid. All rights reserved.
* @license		GNU/GPL, see LICENSE.txt
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You have received a copy of the GNU General Public License in LICENSE.txt
* also available in <http://www.gnu.org/licenses/gpl.html>.
*
* See COPYRIGHT.txt for copyright notices and details.
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <include/map.h>
#include <gtest/gtest.h>
#include "../include/enable_flags.hpp"

using namespace std;
using namespace grppi;

int map_example2(auto &p) {

#ifndef NTHREADS
#define NTHREADS 6
#endif
    int output = 0;
    std::vector<int> in(100);
    for(int i=0;i<in.size();i++) in[i] = i;
    std::vector<int> out(100);
    int i = 0;

    grppi::map( p,
        [&](){
             if( i < in.size()) {
                  optional<int> element(i);
                  i++;
                  return element;
             }
             return optional<int>();
        },
        [&](int index){
             out[index] = in[index];
        }
    );
		
		for(int i=0;i<in.size();i++){
      output += out[i];
		}

    return output;
}



TEST(GrPPI, map_example2_seq ){
    sequential_execution p{};
    EXPECT_EQ(4950, map_example2(p) );
}

TEST(GrPPI, map_example2_thr ){
    parallel_execution_thr p{NTHREADS};
    EXPECT_EQ(4950, map_example2(p) );
}

#ifdef OMP_ENABLE
    TEST(GrPPI, map_example2_omp ){
        parallel_execution_omp p{NTHREADS};
        EXPECT_EQ(4950, map_example2(p) );
    }
#endif
#ifdef TBB_ENABLE
    /* Not yet implemented */
    /*TEST(GrPPI, map_example2_tbb ){
        parallel_execution_tbb p{NTHREADS};
        EXPECT_EQ(4950, map_example2(p) );
    }*/
#endif


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}