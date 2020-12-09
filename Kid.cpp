//
//  Kid.cpp
//  Program 5
//
//  Created by Krikor Herlopian and Ricardo Aliwalas on October 20, 2020.
//  Copyright © 2020 Krikor Herlopian. All rights reserved.
//

#include "Kid.hpp"

static void handler(int hand) {
    return;
}

Kid::Kid(Model* model, int idNumber) {
    m = model;
    pthread_attr_t  attr;
    pthread_attr_init(&attr);
    pthread_create(&tid, NULL, startThread, (void*) this);
    sigemptyset(&set);
    sigaddset(&set, SIGQUIT);
    sigaddset(&set, SIGUSR1);
    sigaddset(&set, SIGUSR2);
    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);
    signal(SIGQUIT, NULL);
    id=idNumber;
    seatNumber= -1;
}

void Kid::play(){
    int temp;
    pthread_mutex_lock(&m->mx);
    m->threadsCreated++;
    pthread_cond_signal(&m->cv2);   // wake up mom thread created
    pthread_mutex_unlock(&m->mx);
    for (;;) {
        usleep(10000);
        sigwait(&set,&temp);
        if (strcmp(sigName(temp),"SIGQUIT") == 0) {
            pthread_exit(NULL);
        }
        else if (strcmp(sigName(temp),"SIGSITDOWN") == 0) {
            doSit();
        }
        else if (strcmp(sigName(temp),"SIGDOMARCH") == 0) {
            doMarch();
        }
    }
}

//  A mutator, standUp(), that Mom will call at the beginning of each round.
//  This function sets the seatNumber to -1, signifying that the child is
//  standing up (has no seat).
void Kid::standUp() {
    m->chairs[seatNumber] = -1;
    seatNumber = -1;
}

// Called from play() when the Kid receives the SIGUSR1 signal
void Kid::doMarch(){
    pthread_mutex_lock(&m->mx);
    wantSeat = rand() % (m->nChairs);
    m->nMarching++;
    pthread_cond_signal(&m->cv2);   // wake up mom I am marching
    pthread_mutex_unlock(&m->mx);
}

void Kid::doSit(){
    pthread_mutex_lock(&m->mx);
    int size = m->nChairs+1;
    pthread_mutex_unlock(&m->mx);
    int mWantSeat = wantSeat;
    if (seatNumber == -1) {
        for (int i=0; i<size; i++) {
            pthread_mutex_lock(&m->mx);
            if (m->chairs[wantSeat]==-1) {
                m->chairs[wantSeat]= id;
                seatNumber = wantSeat;
                pthread_mutex_unlock(&m->mx);
                break;
            } else {
                wantSeat++;
                // assume we got 6 sits, and we started checking from 4th. We check 4, 5, 6
                // then we need to check 0,1,2,3..and at 4th we need to stop since we checked already.
                if (wantSeat == mWantSeat) {
                    wantSeat = -1;
                    seatNumber = -1;
                }
                else if(wantSeat >= m->nChairs) {
                    // since we started checking for seats from random seat number
                    // assume we got 6 sits, and we started checking from 4th. We check 4, 5, 6
                    // then we need to check 0. Thats why we reset.
                    wantSeat = 0;
                }
            }
            pthread_mutex_unlock(&m->mx);
        }
        pthread_mutex_lock(&m->mx);
        m->nMarching++;
        pthread_cond_signal(&m->cv);  // wake up mom, I am done sitting
        pthread_mutex_unlock(&m->mx);
    }
}

// Get functions for the ID number and the tid
int Kid::getId() {
    return id;
}

pthread_t Kid::getTid() {
    return tid;
}

//  A predicate (boolean function) that returns a value indicating whether the
//  Kid is sitting or standing up.
bool Kid::isSitting() {
    if (seatNumber==-1) {
        return false;
    } else {
        return true ;
    }
}

int Kid::getSeatNumber(){
    return seatNumber;
}
