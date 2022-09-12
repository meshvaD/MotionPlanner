#include "include/link.hpp"

void LinkTree::add_link_end(double length, double angle)
{
    Link* new_link = new Link(NULL, NULL, length, angle);
    if (start_link == NULL)
    {
        start_link = new_link;
        end_link = new_link;
    }
    else
    {
        new_link->parent = end_link;
        end_link->child = new_link;
        end_link = new_link;
    }

}