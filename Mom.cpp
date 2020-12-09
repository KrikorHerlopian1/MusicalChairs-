//
//  Mom.cpp
//  Program 5
//
//  Created by Krikor Herlopian and Ricardo Aliwalas on October 20, 2020.
//  Copyright © 2020 Krikor Herlopian. All rights reserved.
//

#include "Mom.hpp"
#include <algorithm>

Mom::Mom(int nKids) {
    m = Model(nKids-1);
    
    Kid* players[nKids];
    for (int i=0; i<nKids; i++) {
        players[i] = new Kid(&m, i);
    }
    stillIn = nKids;
    
    // check if  all threads created before starting.
    Model* model = &m;
    pthread_mutex_lock(&model->mx);
    for (;;) {
        if (model->threadsCreated >= stillIn) {
            break;
        } else {
            pthread_cond_wait(&model->cv2,&model->mx);
        }
    }
    pthread_mutex_unlock(&model->mx);
    
    for (int x=0; x<(nKids-1); x++) {
        PlayOneRound(&m,players);
        cout << "\nNUMBER OF PLAYERS Left:" <<  stillIn << endl;
    }
    if (stillIn == 1) {
        cout << "\nCongratulations Winner is Player: " << players[0]->getId() << " , GO HOME NOW!" << endl;
        pthread_kill(players[0]->getTid(), SIGQUIT);
        pthread_join(players[0]->getTid(), NULL);
    }
    
}

bool valueComp(Kid* const &a, Kid* const &b) {
    return a->getSeatNumber() < b->getSeatNumber();
}

void Mom::PlayOneRound(Model* m, Kid* players[]){
    
    cout << "\n--------------------------NEW ROUND---------------------------" << endl;
    for (int i=0; i<m->nChairs; i++) {
        m->chairs[i]=-1;
    }
    m->nMarching=0;
    
    for (int i=0; i<stillIn; i++) {
        players[i]->standUp();
    }
    
    usleep(100000);
    pthread_mutex_lock(&m->mx);
    for (int i=0; i<stillIn; i++) {
        pthread_kill(players[i]->getTid(), SIGUSR1);
    }

    // wait for signal from kid
    for (;;) {
        if (m->nMarching == stillIn) {
            break;
        } else {
            pthread_cond_wait(&m->cv2,&m->mx);
        }
    }
   
    usleep(100000);
    m->nMarching = 0;
    for (int i=0; i<stillIn; i++) {
        pthread_kill(players[i]->getTid(), SIGUSR2);
    }
    usleep(100000);
    for (;;) {
        if (m->nMarching == stillIn) {
            break;
        } else {
            // wait for signal from the kid
            pthread_cond_wait(&m->cv,&m->mx);
        }
    }
    pthread_mutex_unlock(&m->mx);
    usleep(100000);
    
    int found = -1;
    cout << "Child " << "\t\tSITTING " << "\t\tseat" << endl;
    cout << "------------------------------------------------------------" << endl;
    
    //sort players by seat number
    std::sort(players, players + stillIn, valueComp);
    
    //print players on screen with their seat number.
    for (int i=0; i<stillIn; i++) {
        if (!players[i]->isSitting()) {
            found = i;
            cout << players[i]->getId() << "\t\t" << (players[i]->isSitting() ? "Yes" : "No" ) \
                << "\t\t\t" << "KILLED " << players[i]->getSeatNumber() << endl;
            pthread_kill(players[i]->getTid(), SIGQUIT);
            pthread_join(players[i]->getTid(),NULL);
        } else {
            cout << players[i]->getId() << "\t\t"<<(players[i]->isSitting()  ? "Yes" : "No" ) \
                << "\t\t\t" << players[i]->getSeatNumber() << endl;
        }
    }
    
    swap(players[found],players[(stillIn-1)]);
    usleep(100000);
    
    m->nChairs--;
    m->chairs--;
    stillIn--;
}

