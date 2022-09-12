#include "include/cspace.hpp"
#include <math.h>
#include <iostream>

using namespace std;

cv::Mat CSpace::toConfiguration()
{
    //count number of links -- for extension (later)

    IKSolver* ik_solver = new IKSolver(vector2(0,0), link_tree); //dummy destination 0,0 -- will not use
    double step = 0.05;

    cv::Mat img = cv::imread(cartesian_file, cv::IMREAD_UNCHANGED);
    int cols = img.cols;
    int rows = img.rows;

    cv::Mat config(rows, cols, img.type());

    for (double i=0; i<2*M_PI; i += step)
    {
        for (double j=0; j<2*M_PI; j += step)
        {
            link_tree->start_link->angle = i;
            link_tree->end_link->angle = j;

            ik_solver->updateEndPosition(link_tree->start_link);
            vector2 end_pos = link_tree->end_link->end_pos;

            int im_x = end_pos[0] * scale + rows/2;
            int im_y = end_pos[1] * scale + cols/2;

            if (im_x <= cols && im_y <= rows)
            {
                if (img.at<cv::Vec3b>(im_x, im_y) == cv::Vec3b(255,255,255)) //if unoccupied, make image pos white
                    config.at<cv::Vec3b>(cv::Point(int(i * scale), int(j * scale))) = cv::Vec3b(255,255,255);
                else
                    config.at<cv::Vec3b>(cv::Point(int(i * scale), int(j * scale))) = cv::Vec3b(0,0,0);

            }
        }
    }
    cv::imwrite("/home/meshva/cpp_projects/MotionPlanner/images/config.jpg", config);
    // cv::imshow("config", img);

    delete ik_solver;
    return config;
}