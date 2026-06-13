#ifndef GREEDY_HPP
#define GREEDY_HPP

#include "vrp_base.hpp"

class GreedySolution {
private:
    Problem problem_instance_;
    std::pair<bool, Node> find_closest(const Vehicle& v, const std::vector<Node>& nodes);

public:
    GreedySolution(const Problem& p);
    VrpSolution Solve();
};

#endif // GREEDY_HPP