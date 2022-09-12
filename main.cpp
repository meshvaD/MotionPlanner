#include "include/ik_solver.hpp"
#include "include/animate.hpp"
#include "include/cspace.hpp"
#include "include/path_solver.hpp"

#include <string>
#include <math.h>
#include <vector>
#include <iostream>

int main(int argc, char** argv)
{
    LinkTree* link_tree = new LinkTree();
    for (int i=0; i<3; i++)
        link_tree->add_link_end(1,0);

    // TO GET IK SOLUTIONS

    // IKSolver* ik_solver = new IKSolver(vector2(2,1), link_tree);
    // ik_solver->solve();
    // ik_solver->print();

    // VISUALIZATION -- IK
    // AnimatedWindow window(argc, argv, ik_solver);

    // VISUALIZATION -- PATH SOLVER
    // double scale = 100;
    // CSpace* cspace = new CSpace(link_tree, "/home/meshva/cpp_projects/MotionPlanner/images/cartesian.jpg", scale);
    // cv::Mat im = cspace->toConfiguration();

    // TO SOLVE FOR PATHS, KNOWN START + END CARTESIAN POSITIONS

    PathSolver cpath({0,0},{2,1},link_tree, "/home/meshva/cpp_projects/MotionPlanner/images/none.png", 1, 2);
    std::vector<std::vector<double>>* p = cpath.solve();

    // TO SOLVE FOR PATHS, KNOWN START + END IK JOINT POSITIONS

    JointSpaceSolver path({0,0,0},{0,0,90},link_tree, "/home/meshva/cpp_projects/MotionPlanner/images/none.png", 1, 2);
    std::vector<std::vector<double>>* p = path.solve();
}