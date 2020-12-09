//
//  main.cpp
//  Program 5
//
//  Created by Krikor Herlopian and Ricardo Aliwalas on October 20, 2020.
//  Copyright © 2020 Krikor Herlopian. All rights reserved.
//

#include <iostream>
#include "Mom.hpp"

bool hasOnlyDigits(const string s){
  return s.find_first_not_of( "0123456789" ) == string::npos;
}

int main(int argc, const char * argv[]) {
    if (argc < 2) {
       fatal("Please enter number of players\n");
    }
    else if (!hasOnlyDigits(argv[1])) {
        fatal("First argument should be number (no dots no comma)\n");
    }
    else{
        banner();
        int numberOfKids = atoi(argv[1]);
        if(numberOfKids < 2){
            fatal("Number of kids playing should be at least 2 and higher.\n");
        }
        Mom Mom(numberOfKids);
        bye();
    }
    return 0;
}

