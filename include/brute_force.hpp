#ifndef BRUTE_FORCE_HPP
#define BRUTE_FORCE_HPP

#include "vrp_base.hpp"

class BruteForceSolution {
private:
    Problem problem_instance_;
    double best_cost_;
    std::vector<Vehicle> best_vehicles_;

    // Función recursiva para permutar y evaluar todas las combinaciones válidas
    //void permute_and_solve(std::vector<int>& current_permutation, int index);

    //Nota: permute_and_solve al parecer no se usa en el código, la ia lo generó pero
    //no lo utiliza
    void evaluate_permutation(const std::vector<int>& permutation);

public:
    BruteForceSolution(const Problem& p);
    VrpSolution Solve();
};

#endif // BRUTE_FORCE_HPP