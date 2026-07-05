#include "brute_force.hpp"
#include <chrono>
#include <numeric>
#include <iostream>
#include <algorithm>
BruteForceSolution::BruteForceSolution(const Problem& p) : problem_instance_(p) {
    best_cost_ = 1e9; // Inicializamos con un costo infinito
}

void BruteForceSolution::evaluate_permutation(const std::vector<int>& permutation) {
    std::vector<Vehicle> current_vehicles = problem_instance_.vehicles_;
    int vehicle_index = 0;
    int num_vehicles = current_vehicles.size(); //problem_instace_.nov_

    // Intentamos asignar los clientes de la permutación actual a los vehículos
    for (int client_id : permutation) {
        const Node& client = problem_instance_.nodes_[client_id - 1]; // id_ empieza en 1

        while(vehicle_index < num_vehicles){ //sirve para mantener el analisis sobre el vehiculo actual
            if(client.demand_ > current_vehicles[vehicle_index].load_){
                int last_node = current_vehicles[vehicle_index].nodes_.back();
                current_vehicles[vehicle_index].cost_ += problem_instance_.distanceMatrix_[last_node][problem_instance_.depot_.id_];
                current_vehicles[vehicle_index].nodes_.push_back(problem_instance_.depot_.id_);
                vehicle_index++;
            }
            else{
                Vehicle& v = current_vehicles[vehicle_index];
                v.cost_ += problem_instance_.distanceMatrix_[v.nodes_.back()][client.id_];
                v.load_ -= client.demand_;
                v.nodes_.push_back(client.id_);
                break;
            }
        }

        if (vehicle_index >= num_vehicles) {
            return;
        }

    }

    //esto es para cerrar la ruta del ultimo vehiculo utilizado
    int last_node = current_vehicles[vehicle_index].nodes_.back();
    current_vehicles[vehicle_index].cost_ += problem_instance_.distanceMatrix_[last_node][problem_instance_.depot_.id_];
    current_vehicles[vehicle_index].nodes_.push_back(problem_instance_.depot_.id_);

    // Calcular el costo total de esta configuración
    double current_total_cost = 0.0;
    for (const auto& v : current_vehicles) {
        current_total_cost += v.cost_;
    }

    // Si encontramos una mejor solución, la guardamos
    if (current_total_cost < best_cost_) {
        best_cost_ = current_total_cost;
        best_vehicles_ = current_vehicles;
    }
}

VrpSolution BruteForceSolution::Solve() {
    auto start_time = std::chrono::high_resolution_clock::now();

    int n = problem_instance_.noc_;
    std::vector<int> permutation(n);
    // Llenamos el vector con los IDs de los clientes: 1, 2, ..., n
    std::iota(permutation.begin(), permutation.end(), 1);

    best_cost_ = 1e9;
    best_vehicles_.clear();

    // Evaluamos absolutamente todas las permutaciones de los clientes
    do {
        evaluate_permutation(permutation);
    } while (std::next_permutation(permutation.begin(), permutation.end()));

    auto end_time = std::chrono::high_resolution_clock::now();
    double elapsed_time = std::chrono::duration<double, std::milli>(end_time - start_time).count();

    VrpSolution sol; //sol : solution
    sol.vehicles_ = best_vehicles_;
    sol.total_cost_ = best_cost_;
    sol.execution_time_ms_ = elapsed_time;
    sol.is_valid_ = (best_cost_ < 1e9);
    sol.algorithm_name_ = "Algoritmo de Fuerza Bruta (Exacto)";

    return sol;
}