#include "include/animate.hpp"

#include <GL/glut.h>
#include "include/vector2.hpp"
#include <iostream>

AnimatedWindow* curr_instance;
void drawCallback()
{
    curr_instance->draw();
}

void timerCallback(int value)
{
    curr_instance->timer(value);
}

AnimatedWindow::AnimatedWindow(int argc, char** argv, IKSolver* ik_solver)
{
    this->ik_solver = ik_solver;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hello world!");

    glutTimerFunc(500,timerCallback,0);
    ::curr_instance = this;
    glutDisplayFunc(drawCallback);

    glutMainLoop();
}

void AnimatedWindow::timer(int value)
{
    if (!cont)
        return;

    glutTimerFunc(500,timerCallback,0);

    ik_solver->solveIteration();
    bool solved = ik_solver->reached();

    std::cout << solved << ", " << iter_count << std::endl;

    if (solved)
        std::cout << "DONE" << std::endl;

    if (solved || iter_count > 10)
        cont = false;

    iter_count ++;
        
    glutPostRedisplay();
}

void AnimatedWindow::draw()
{
    //navigate to last line, draw all lines until that
    glClear(GL_COLOR_BUFFER_BIT);

    Link* link_next = ik_solver->end_link;
    while (link_next != NULL)
    {
        vector2 origin = vector2();
        if (link_next->parent != NULL)
            origin = link_next->parent->end_pos / 3;
        vector2 dest = link_next->end_pos / 3;

        std::cout << origin*3 << " to " << dest*3 << std::endl;

        glBegin(GL_LINES);
            glVertex2f(origin[0], origin[1]);
            glVertex2f(dest[0], dest[1]);
        glEnd();

        link_next = link_next->parent;
    }

    // std::cout << origin << " to " << dest << std::endl;

    glFlush();
}