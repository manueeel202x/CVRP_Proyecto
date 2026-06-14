#ifndef LOCAL_SEARCH_INTRA_HPP
#define LOCAL_SEARCH_INTRA_HPP

#include "vrp_base.hpp"

class LocalSearchIntraSolution {
public:
    Problem problem_;

    // El constructor recibe el problema base
    LocalSearchIntraSolution(const Problem& p);

    // Método principal que ejecuta la optimización
    VrpSolution Solve();
};

#endif // LOCAL_SEARCH_INTRA_HPP