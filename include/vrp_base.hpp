#ifndef VRP_BASE_HPP
#define VRP_BASE_HPP

#define DISPLAY_SOLUTION 1

#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdlib> // <--- CRUCIAL para rand()
#include <ctime>   // <--- Para la semilla del tiempo

// Estructura para representar a cada Cliente
struct Node {
    int id_;
    int x_;
    int y_;
    int demand_;
    bool is_routed_ = false;
};

// Estructura para representar a cada Vehículo
struct Vehicle {
    int id_;
    int capacity_;
    int load_;
    double cost_ = 0.0;
    std::vector<int> nodes_;
};

// Clase que representa la instancia global del problema
class Problem {
public:
    int noc_;                     // Cambiado # por //
    int nov_;                     // Cambiado # por //
    int capacity_;                // Cambiado # por //
    Node depot_;                  // Cambiado # por //
    std::vector<Node> nodes_;     // Cambiado # por //
    std::vector<Vehicle> vehicles_;
    std::vector<std::vector<double>> distanceMatrix_;

    Problem(int noc, int demand_range, int nov, int capacity, int grid_range) {
        noc_ = noc;
        nov_ = nov;
        capacity_ = capacity;

        depot_ = {0, grid_range / 2, grid_range / 2, 0, true};

        for (int i = 1; i <= noc_; ++i) {
            Node n;
            n.id_ = i;
            n.x_ = rand() % grid_range;
            n.y_ = rand() % grid_range;
            n.demand_ = 1 + (rand() % demand_range);
            n.is_routed_ = false;
            nodes_.push_back(n);
        }

        for (int i = 0; i < nov_; ++i) {
            Vehicle v;
            v.id_ = i;
            v.capacity_ = capacity_;
            v.load_ = capacity_;
            v.nodes_.push_back(depot_.id_);
            vehicles_.push_back(v);
        }

        int total_nodes = noc_ + 1;
        distanceMatrix_.assign(total_nodes, std::vector<double>(total_nodes, 0.0));

        std::vector<Node> all_nodes;
        all_nodes.push_back(depot_);
        all_nodes.insert(all_nodes.end(), nodes_.begin(), nodes_.end());

        for (int i = 0; i < total_nodes; ++i) {
            for (int j = 0; j < total_nodes; ++j) {
                double dx = all_nodes[i].x_ - all_nodes[j].x_;
                double dy = all_nodes[i].y_ - all_nodes[j].y_;
                distanceMatrix_[i][all_nodes[j].id_] = std::sqrt(dx*dx + dy*dy);
            }
        }
    }
};

struct VrpSolution {
    std::vector<Vehicle> vehicles_;
    double total_cost_ = 0.0;
    double execution_time_ms_ = 0.0;
    bool is_valid_ = false;
    std::string algorithm_name_;
};

#endif // VRP_BASE_HPP