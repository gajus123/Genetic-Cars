//
// Created by igor on 13.01.18.
//

#ifndef GENETIC_CARS_VEHICLE_H
#define GENETIC_CARS_VEHICLE_H

#include "include/Wheel.h"
#include "include/Body.h"

namespace Objects {

    class Vehicle {
    public:
        Vehicle(Wheel& front, Wheel& back, Body& body);

    private:
    };

}

#endif //GENETIC_CARS_VEHICLE_H
