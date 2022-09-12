#pragma once

#include "vector2.hpp"
#include <vector>

struct Link
{
    Link(Link* parent, Link* child, double length, double angle) 
        : parent(parent), child(child), length(length), angle(angle) {}

    Link* parent; //if no parent(null), place fixed at origin
    Link* child;

    double length;
    double angle; //wrt to parent
    vector2 end_pos; //position of tip
};

class LinkTree
{
public:
    void add_link_end(double length, double angle);

    Link* end_link;
    Link* start_link;
};