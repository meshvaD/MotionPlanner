#include <vector>
#include <string>
#include "ik_solver.hpp"
#include <opencv2/opencv.hpp>

class CSpace
{
public:
    CSpace(LinkTree* link_tree, std::string cartesian_file, double scale) 
        : link_tree(link_tree), cartesian_file(cartesian_file), scale(scale) {};

    cv::Mat toConfiguration();

private:
    std::string cartesian_file;
    double scale;
    LinkTree* link_tree;
};