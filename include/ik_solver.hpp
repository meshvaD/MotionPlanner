#pragma once

#include "vector2.hpp"
#include <vector>
#include "link.hpp"
#include <opencv2/opencv.hpp>

class IKSolver
{
public:
    IKSolver(vector2 dest, LinkTree* link_tree, std::string cartesian_file="", double scale=1);

    bool solve();
    bool solveIteration();

    void print();
    bool reached();

    void updateEndPosition(Link* l);
    bool validEndPosition();

    Link* end_link = NULL;

private:
    Link* start_link = NULL;
    vector2 dest;
    double scale;
    cv::Mat img;

    void updateLink(int i);
    double angleFromHorizontal(Link* l);
};