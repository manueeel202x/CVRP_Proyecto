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
        if (v.nodes_.size() < 4) continue;

        bool mejora = true;
        while (mejora) {
            mejora = false;

            double max_ahorro = 0.0;
            size_t mejor_i = 0;
            size_t mejor_j = 0;

            // Escaneamos TODO el vecindario de la ruta buscando el mejor movimiento posible
            for (size_t i = 1; i < v.nodes_.size() - 2; ++i) {
                for (size_t j = i + 1; j < v.nodes_.size() - 1; ++j) {

                    int n_i = v.nodes_[i];
                    int n_next_i = v.nodes_[i+1];
                    int n_j = v.nodes_[j];
                    int n_next_j = v.nodes_[j+1];

                    double dist_actual = problem_.distanceMatrix_[n_i][n_next_i] +
                                         problem_.distanceMatrix_[n_j][n_next_j];

                    double dist_nueva = problem_.distanceMatrix_[n_i][n_j] +
                                        problem_.distanceMatrix_[n_next_i][n_next_j];

                    // Calculamos el ahorro neto de esta opción
                    double ahorro_actual = dist_actual - dist_nueva;

                    // Si este cambio es mejor que el anterior máximo guardado, lo recordamos
                    if (ahorro_actual > max_ahorro) {
                        max_ahorro = ahorro_actual;
                        mejor_i = i;
                        mejor_j = j;
                    }
                }
            }

            // Al salir de los bucles 'for', RECIÉN aplicamos el ÚNICO movimiento que más ahorró
            if (max_ahorro > 0.0) {
                std::reverse(v.nodes_.begin() + mejor_i + 1, v.nodes_.begin() + mejor_j + 1);
                mejora = true; // Forzamos otra pasada del while para verificar si quedan más mejoras
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