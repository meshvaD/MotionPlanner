#pragma once

#include "ik_solver.hpp"
#include <GL/glut.h>

class AnimatedWindow
{
public:
    AnimatedWindow(int argc, char** argv, IKSolver* ik_solver);
    void draw();
    void timer(int value);

private:
    IKSolver* ik_solver;
    bool cont = true;
    int iter_count = 0;
};