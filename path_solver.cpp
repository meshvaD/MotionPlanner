#include "include/path_solver.hpp"
#include <vector>
#include <iostream>
#include <math.h>
#include <limits.h>

using namespace std;

bool Node::operator() (const Node* n1, const Node* n2)
{
    return n1->f > n2->f;
}

vector<vector<double>>* PathSolver::getPath(Node* n)
{
    vector<vector<double>>* path = new vector<vector<double>>();
    while (n != NULL)
    {
        path->insert(path->begin(), n->coords);

        for (int i=0; i<n->coords.size(); i++)
            cout << n->coords[i] << " , ";
        cout << endl;
        n = n->parent;
    }
    return path;
}

vector<vector<double>>* PathSolver::solve()
{
    Node* s = new Node(NULL, start);

    // priority_queue<Node*, vector<Node*>, Node> open;
    PriorityQueue<Node*, Node> open;
    open.push(s);
    PriorityQueue<Node*, Node> closed;

    while (!open.empty())
    {
        //get open node with lowest f
        Node* q = open.top();
        open.pop();

        //generate 8 successors with parent q
        vector<Node*> succ = getSuccessors(q);
        for(const auto& s: succ)
        {
            //if successor is goal, stop search
            if (s->coords == goal)
            {
                std::cout << "solved" << std::endl;
                return getPath(s);
            }

            //compute g and h, set new f
            s->g = q->g + euclidean(q->coords, s->coords);
            s->h = euclidean(goal, s->coords);
            s->f = s->g + s->h;

            //if node in open with lower f, skip
            if (fCoords(open, s->coords) < 0 && (fCoords(closed, s->coords) < 0 || fCoords(closed, s->coords) >= s->f))
                open.push(s);
        }
        //push q on closed list
        closed.push(q);
    }
    return NULL;
}

// FOR PLANNING IN CARTESIAN SPACE
vector<Node*> PathSolver::getSuccessors(Node* n)
{
    std::cout << "HERE C" << std::endl;
    //one unit in each direction, can adjust granularity
    vector<pair<int,int>> dirs = {{1,0},{1,1},{1,-1},{0,1},{0,-1},{-1,0},{-1,1},{-1,-1}};
    vector<Node*> succ;

    for(const auto& d: dirs)
    {
        Node* next = new Node(n, {n->coords[0] + d.first*step, n->coords[1] + d.second*step});
        
        //only add successful if ik sol exists
        IKSolver ik_solver(vector2(next->coords[0], next->coords[1]), link_tree, cartesian_map, scale);
        if (ik_solver.solve())
            succ.push_back(next);
    }
    return succ;
}

// FOR PLANNING IN JOINT SPACE
vector<Node*> JointSpaceSolver::getSuccessors(Node* n)
{
    std::cout << ".";
    vector<Node*> succ;

    IKSolver ik_solver(vector2(0,0), link_tree, cartesian_map, scale); //dummy destination
    // in 2D ** degree CW (can have both CW and CCW), do forward kinematics to see if valid
    Link* curr_link = link_tree->start_link;

    //create vec with all link angles
    for(int i=0; i<n->coords.size(); i++)
    {
        curr_link->angle = n->coords[i];
        curr_link = curr_link->child;
    }
    curr_link = link_tree->start_link;
    int link_pos = 0;
    while (curr_link != NULL)
    {
        curr_link->angle += step;
        ik_solver.updateEndPosition(link_tree->start_link);

        //push back node with joint values instead of coords
        if (ik_solver.validEndPosition())
        {
            double temp = n->coords[link_pos];
            n->coords[link_pos] += step;
            Node* next = new Node(n, n->coords);
            succ.push_back(next);

            n->coords[link_pos] = temp;
        }
        curr_link->angle -= step;
        curr_link = curr_link->child;
        link_pos ++;
    }
    return succ;
}

double PathSolver::euclidean(std::vector<double> p1, std::vector<double> p2)
{
    double pow_sum = 0;
    for (int i=0; i<p1.size(); i++)
        pow_sum += pow(p1[i] - p2[i], 2);
    
    return pow(pow_sum, 0.5);
}

double PathSolver::fCoords(PriorityQueue<Node*, Node> pq, std::vector<double> coords)
{
    for (unordered_set<Node*>::iterator it = pq.set_.begin(); it != pq.set_.end(); ++it)
    {
        if ((*it)->coords == coords)
        {
            return (*it)->f;
        }
    }
    return -1;
}