//
// Created by 79612 on 23.05.2021.
//

#include "session.h"
#include "../solvers/solver.h"
#include "../solvers/rk4.h"
#include "../solvers/euler.h"

void solverRunnable(Particle *particle) {
    auto ptr = std::shared_ptr<RhsFunction>(new EMFieldMovingFunction(
            Point3D(0, 0, 1),
            Point3D(0, 1, 0), 2, 3));
    auto s = std::shared_ptr<Solver>(new EulerSolver(
            ptr,
            [&particle](State state) -> void {
                particle->setX(state.coordinate.x);
                particle->setY(state.coordinate.y);
                particle->setZ(state.coordinate.z);
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }, 0.01, 10000
    ));
    State state(Point3D(0, 0, 0), Point3D(0, 0, 0), 1);
    s->solve(state);
}

void Session::start(Particle *particle) {
    solverThread = std::thread(solverRunnable, particle);
}

void Session::stop() {
    if (solverThread.native_handle())
        pthread_cancel(solverThread.native_handle());
    solverThread.join();
}

