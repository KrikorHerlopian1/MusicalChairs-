//
//  Model.hpp
//  Program 5
//
//  Created by Krikor Herlopian and Ricardo Aliwalas on October 20, 2020.
//  Copyright © 2020 Krikor Herlopian. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

#include <stdio.h>
#include "tools.hpp"
#include <mutex>
using namespace std;

struct Model{
    //A mutex lock to control all the other parts of the model.
    pthread_mutex_t mx = PTHREAD_MUTEX_INITIALIZER;
    // An int variable, nChairs, stores the number of chairs in use
    // for the current round of the game.
    int nChairs;
    // A pointer to the chair array, with (nKids−1) ints
    int *chairs;
    // An int variable, nMarching, for the number of kids currently
    //  marching around the chairs.
    int nMarching;
    int threadsCreated = 0;
    // Two condition variables that kid-threads use to signal Mom
    pthread_cond_t cv = PTHREAD_COND_INITIALIZER;
    pthread_cond_t cv2 = PTHREAD_COND_INITIALIZER;
    Model(int numberOfChairsNeeded);
    Model()= default;
    ~Model()=default;
};

#endif /* Model_hpp */
