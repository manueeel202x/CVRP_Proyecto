#include "local_search_intra.hpp"
#include "greedy.hpp" // Para obtener la solución inicial
#include <chrono>

LocalSearchIntraSolution::LocalSearchIntraSolution(const Problem& p) : problem_(p) {}

VrpSolution LocalSearchIntraSolution::Solve() {
    auto start = std::chrono::high_resolution_clock::now();

    // 1. Obtener la solución semilla usando el Greedy que ya programaron
    GreedySolution greedy_solver(problem_);
    VrpSolution solucion = greedy_solver.Solve();

    // 2. Local Search (Intra-vehículo usando 2-opt)
    for (auto& v : solucion.vehicles_) {
        if (v.nodes_.size() < 4) continue; // No se puede optimizar si son muy pocos nodos

        bool mejora = true;
        while (mejora) {
            mejora = false;
            // Evaluamos pares de conexiones internas (excluyendo el depósito en los extremos si es fijo)
            for (size_t i = 1; i < v.nodes_.size() - 2; ++i) {
                for (size_t j = i + 1; j < v.nodes_.size() - 1; ++j) {

                    int n_i = v.nodes_[i];
                    int n_next_i = v.nodes_[i+1];
                    int n_j = v.nodes_[j];
                    int n_next_j = v.nodes_[j+1];

                    // Distancia actual de las aristas
                    double dist_actual = problem_.distanceMatrix_[n_i][n_next_i] +
                                         problem_.distanceMatrix_[n_j][n_next_j];

                    // Distancia si invertimos el segmento
                    double dist_nueva = problem_.distanceMatrix_[n_i][n_j] +
                                        problem_.distanceMatrix_[n_next_i][n_next_j];

                    // Si la nueva distancia es menor, reconectamos la ruta (2-opt swap)
                    if (dist_nueva < dist_actual) {
                        std::reverse(v.nodes_.begin() + i + 1, v.nodes_.begin() + j + 1);
                        mejora = true;
                    }
                }
            }
        }

        // Recalcular el costo individual del vehículo optimizado
        v.cost_ = 0;
        for (size_t i = 0; i < v.nodes_.size() - 1; ++i) {
            v.cost_ += problem_.distanceMatrix_[v.nodes_[i]][v.nodes_[i+1]];
        }
    }

    // 3. Recalcular el costo total de la nueva solución híbrida
    solucion.total_cost_ = 0;
    for (const auto& v : solucion.vehicles_) {
        solucion.total_cost_ += v.cost_;
    }

    auto end = std::chrono::high_resolution_clock::now();
    solucion.execution_time_ms_ = std::chrono::duration<double, std::milli>(end - start).count();

    return solucion;
}