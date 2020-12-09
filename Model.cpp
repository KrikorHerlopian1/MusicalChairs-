//
//  Model.cpp
//  Program 5
//
//  Created by Krikor Herlopian and Ricardo Aliwalas on October 20, 2020.
//  Copyright © 2020 Krikor Herlopian. All rights reserved.
//

#include "Model.hpp"

Model::Model(int numberOfChairsNeeded) {
    nChairs = numberOfChairsNeeded;
    chairs = new int[numberOfChairsNeeded];
}

