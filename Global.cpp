//
//  Global.cpp
//  Program 5
//
//  Created by Krikor Herlopian and Ricardo Aliwalas on October 20, 2020.
//  Copyright © 2020 Krikor Herlopian. All rights reserved.
//
#include "Global.hpp"

void* startThread(void* kid) {
    Kid* k = (Kid*) kid;
    k->play();
    return NULL;
}

const char* sigName(int sig) {
    if (SIGUSR2==sig) {
        return "SIGSITDOWN";
    }
    else if (SIGUSR1==sig) {
        return "SIGDOMARCH";
    }
    else {
        return "SIGQUIT";
    }
}
