#include "include/ik_solver.hpp"
#include <math.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

IKSolver::IKSolver(vector2 dest, LinkTree* link_tree, std::string cartesian_file, double scale)
{
    this->dest = dest;
    this->start_link = link_tree->start_link;
    this->end_link = link_tree->end_link;
    this->scale = scale;
    this->img = cv::imread(cartesian_file, cv::IMREAD_UNCHANGED);

    updateEndPosition(start_link);
}

double IKSolver::angleFromHorizontal(Link* link)
{
    if (link->parent == NULL)
        return link->angle;
    
    return link->angle + angleFromHorizontal(link->parent);
}

void IKSolver::updateEndPosition(Link* link)
{
    vector2 origin = vector2();
    if (link->parent != NULL)
        origin = link->parent->end_pos; 

    double angle = angleFromHorizontal(link);
    link->end_pos = vector2(link->length * cos(angle), link->length * sin(angle)) + origin;

    if (link->child != NULL)
        updateEndPosition(link->child);
}

bool IKSolver::validEndPosition()
{
    double x = end_link->end_pos[0];
    double y = end_link->end_pos[1];

    // std::cout << img.at<cv::Vec3b>(x, y) << std::endl;

    return true;

    //if white, allowed pos
    // if (img.at<cv::Vec3b>(x, y) == cv::Vec3b(255,255,255))
    //     return true;
    // return false;
}

bool IKSolver::reached()
{
    return end_link->end_pos == dest;
}

bool IKSolver::solve()
{
    //limits iteration, should probably work (unit tests??)
    for (int i=0; i<10; i++)
    {
        solveIteration();
        // cout << endl;
        print();

        if (reached())
            break;
    }

    if (reached())
    {
        cout << "ik success" << endl;
        return true;
    }
    cout << "ik failure" << endl;
    return false;
}

bool IKSolver::solveIteration()
{
    //start with end effector, move backwards w parent, update theta
    //after each angle update, update end_effector positions
    bool update_angle = false;

    Link* curr = end_link;

    while (curr != NULL && end_link->end_pos != dest)
    {        
        vector2 origin = vector2();
        if (curr->parent != NULL)
            origin = curr->parent->end_pos; 

        double angle = dot(unit_vector(dest - origin), unit_vector(end_link->end_pos - origin));  
        angle = acos(angle);  
        curr->angle = angle;

        // cout << "dest: " << dest << " origin: " << origin << " end effector " << end_link->end_pos << endl;

        updateEndPosition(curr);

        if (angle != 0)
            update_angle = true;

        // cout << curr->angle << endl;
        
        curr = curr->parent;
    }

    return update_angle;
}

void IKSolver::print()
{
    Link* curr = end_link;
    while (curr != NULL)
    {
        // cout << "end position: " << curr->end_pos << endl;
        curr = curr->parent;
    }
}
