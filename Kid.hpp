//
//  Kid.hpp
//  Program 5
//
//  Created by Krikor Herlopian and Ricardo Aliwalas on October 20, 2020.
//  Copyright © 2020 Krikor Herlopian. All rights reserved.
//

#ifndef Kid_hpp
#define Kid_hpp

#include <stdio.h>
#include "Model.hpp"
#include "Global.hpp"
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>


class Kid{
private:
    sigset_t set;
    // a pointer to the shared model
    Model* m;
    // the kid's id number (0,1,2)
    int id;
    pthread_t tid;
    int seatNumber;
    int wantSeat;
public:
    int getId();
    pthread_t getTid();
    int getSeatNumber();
    Kid() = default;
    Kid(Model* m, int idNumber);
    bool isSitting();
    void standUp();
    void doSit();
    void play();
    void doMarch();
};
#endif /* Kid_hpp */
