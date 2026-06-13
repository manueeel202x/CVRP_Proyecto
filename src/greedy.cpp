#include "greedy.hpp"
#include <chrono>
#include <iostream>

GreedySolution::GreedySolution(const Problem& p) : problem_instance_(p) {}

std::pair<bool, Node> GreedySolution::find_closest(const Vehicle& v, const std::vector<Node>& nodes) {
    double min_dist = 1e9;
    Node closest_node;
    bool found = false;

    // El último nodo visitado por el vehículo actual
    int last_node_id = v.nodes_.back();

    for (const auto& node : nodes) {
        if (!node.is_routed_ && node.id_ != 0) { // No ruteado y que no sea el depósito
            double dist = problem_instance_.distanceMatrix_[last_node_id][node.id_];
            if (dist < min_dist) {
                min_dist = dist;
                closest_node = node;
                found = true;
            }
        }
    }
    return {found, closest_node};
}

VrpSolution GreedySolution::Solve() {
    auto start_time = std::chrono::high_resolution_clock::now();

    // Copiamos los nodos y vehículos de la instancia para no alterar el problema original
    std::vector<Node> local_nodes = problem_instance_.nodes_;
    std::vector<Vehicle> local_vehicles = problem_instance_.vehicles_;

    for (auto& v : local_vehicles) {
        while (true) {
            auto [found, closest_node] = find_closest(v, local_nodes);

            // Si encontramos un vecino cercano y el camión tiene capacidad para su demanda
            if (found && v.load_ - closest_node.demand_ >= 0) {
                v.load_ -= closest_node.demand_;
                v.cost_ += problem_instance_.distanceMatrix_[v.nodes_.back()][closest_node.id_];
                v.nodes_.push_back(closest_node.id_);

                // Marcamos como visitado en nuestra lista local
                for (auto& n : local_nodes) {
                    if (n.id_ == closest_node.id_) {
                        n.is_routed_ = true;
                        break;
                    }
                }
            } else {
                // Si no hay capacidad o ya no hay más clientes, el vehículo regresa al depósito
                v.cost_ += problem_instance_.distanceMatrix_[v.nodes_.back()][problem_instance_.depot_.id_];
                v.nodes_.push_back(problem_instance_.depot_.id_);
                break; // Se cierra la ruta de este vehículo
            }
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    double elapsed_time = std::chrono::duration<double, std::milli>(end_time - start_time).count();

    // Calcular el costo total acumulado por todos los camiones
    double total_cost = 0.0;
    for (const auto& v : local_vehicles) {
        total_cost += v.cost_;
    }

    // Verificar si quedaron clientes sin atender
    bool all_visited = true;
    for (const auto& n : local_nodes) {
        if (!n.is_routed_) {
            all_visited = false;
        }
    }

    VrpSolution sol;
    sol.vehicles_ = local_vehicles;
    sol.total_cost_ = total_cost;
    sol.execution_time_ms_ = elapsed_time;
    sol.is_valid_ = all_visited;
    sol.algorithm_name_ = "Algoritmo Greedy (Vecino Cercano)";

    return sol;
}