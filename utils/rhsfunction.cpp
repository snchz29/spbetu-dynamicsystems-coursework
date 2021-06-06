//
// Created by 79612 on 23.05.2021.
//

#include "rhsfunction.h"

bool EMFieldMovingFunction::terminatePredicate(Point3D &coord) {
    return displayNormal.x*(coord.x - displayTranspose.x) + \
            displayNormal.y*(coord.y - displayTranspose.y) + \
            displayNormal.z*(coord.z - displayTranspose.z) > 0.;
}

void EMFieldMovingFunction::addDisplay(QVector3D trans, QVector3D normal)
{
    displayTranspose = Point3D(trans.x(), trans.y(), trans.z());
    displayNormal = Point3D(normal.x(), normal.y(), normal.z());
}

State EMFieldMovingFunction::apply(State state) {
    Point3D dVelocity(0,0,0);
    for (auto &electricField : electricFields) {
        dVelocity = dVelocity + electricField->value * electricField->direction;
    }

    for (auto &magneticField : magneticFields) {
        dVelocity = dVelocity + magneticField->value * state.velocity.cross(magneticField->direction);
    }

    if (terminatePredicate(state.coordinate))
        throw 1;
    state.coordinate = state.velocity + dVelocity;
    State newState(state.coordinate, dVelocity, state.charge);
    return newState;
}


UniformField::UniformField(double value, const Point3D &direction)
        : value(value),
          direction(direction) {}

void EMFieldMovingFunction::addElectricField(UniformField *field) {
    electricFields.push_back(field);
}

std::vector<UniformField *> &EMFieldMovingFunction::getElectricFields() {
    return electricFields;
}

std::vector<UniformField *> &EMFieldMovingFunction::getMagneticFields() {
    return magneticFields;
}

void EMFieldMovingFunction::addMagneticField(UniformField *field) {
    magneticFields.push_back(field);
}

EMFieldMovingFunction::~EMFieldMovingFunction() noexcept {
    for (auto &e : electricFields) {
        delete e;
    }
    for (auto &m : magneticFields) {
        delete m;
    }
}
