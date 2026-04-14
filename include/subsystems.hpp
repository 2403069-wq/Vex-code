#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"
#include "pros/motor_group.hpp"

extern Drive chassis;

// tren motriz
inline pros::MotorGroup left_motors({-6, -7, -8});
inline pros::MotorGroup right_motors({1, 2, 3});

// selector
inline pros::Motor selector(10);

// almacén
inline pros::Motor almacen(-9);

    // succión
    inline pros::MotorGroup intake_motors({4, 5});
    inline pros::Motor intake_expul(-12);

    extern bool intake_expul_activado;

// pistón
inline pros::adi::DigitalOut piston('A');