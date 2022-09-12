#pragma once

#include <utility>
#include <queue>
#include <unordered_set>
#include <opencv2/opencv.hpp>
#include "ik_solver.hpp"

struct Node
{
    Node(){} //default constructor needed for operator + priority queue
    Node(Node* parent, std::vector<double> coords) : parent(parent), coords(coords) {}
    bool operator() (const Node* n1, const Node* n2);

    Node* parent;
    std::vector<double> coords;
    double f = 0;
    double g = 0;
    double h = 0;
};

//wrapper for priority queue to find items
template <class T, class C>
struct PriorityQueue
{
    void push(T item)
    {
        pq_.push(item);
        set_.emplace(item);
    };
    void pop()
    {
        T top = pq_.top();
        set_.erase(top);
        pq_.pop();
    };
    T top() {return pq_.top();}
    bool empty() const {return set_.empty();}

    std::priority_queue<T, std::vector<T>, C> pq_;
    std::unordered_set<T> set_;
};

class PathSolver
{
public:
    PathSolver(std::vector<double> start, std::vector<double> goal, LinkTree* link_tree, std::string cartesian_map, double scale, double solve_step)
        : link_tree(link_tree), start(start), goal(goal), cartesian_map(cartesian_map), scale(scale), step(solve_step) {}
        
    std::vector<std::vector<double>>* solve();
    LinkTree* link_tree;
    std::string cartesian_map;
    double scale;
    double step;

private:
    virtual std::vector<Node*> getSuccessors(Node* n);

    double euclidean(std::vector<double> p1, std::vector<double> p2);
    double fCoords(PriorityQueue<Node*, Node> pq, std::vector<double> coords);
    std::vector<std::vector<double>>* getPath(Node* n);

    std::vector<double> start;
    std::vector<double> goal;
};

class JointSpaceSolver : public PathSolver
{
public:
    using PathSolver::PathSolver;
private:
    virtual std::vector<Node*> getSuccessors(Node* n);
};