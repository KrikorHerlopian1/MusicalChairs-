//
//  Global.hpp
//  Program 5
//
//  Created by Krikor Herlopian and Ricardo Aliwalas on October 20, 2020.
//  Copyright © 2020 Krikor Herlopian. All rights reserved.
//

#ifndef Global_hpp
#define Global_hpp

#include <stdio.h>
#include <signal.h>
#include "Kid.hpp"

void* startThread(void* kid);
const char* sigName(int sig);
#endif /* Global_hpp */
