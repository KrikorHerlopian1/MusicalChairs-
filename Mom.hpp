//
//  Mom.hpp
//  Program 5
//
//  Created by Krikor Herlopian and Ricardo Aliwalas on October 20, 2020.
//  Copyright © 2020 Krikor Herlopian. All rights reserved.
//

#ifndef Mom_hpp
#define Mom_hpp

#include <stdio.h>
#include <vector>
#include "Kid.hpp"
#include "Model.hpp"

class Mom {
private:
    Model m;
    int stillIn;
    void PlayOneRound(Model* m,Kid* players[]);
public:
    Mom(int nKids);
};

#endif /* Mom_hpp */
