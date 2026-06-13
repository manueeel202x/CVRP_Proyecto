#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "greedy.hpp"
#include "brute_force.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Obliga a las columnas a estirarse uniformemente para ocupar todo el ancho disponible
    ui->tablaResultados->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // Obliga a las filas a hacer lo mismo verticalmente
    ui->tablaResultados->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Configuración inicial de los selectores de algoritmos
    QStringList algoritmos = {"Algoritmo Greedy (Vecino Cercano)", "Fuerza Bruta (Exacto)"};
    ui->comboAlgoritmo1->addItems(algoritmos);
    ui->comboAlgoritmo2->addItems(algoritmos);
}

MainWindow::~MainWindow() {
    delete ui;
    if (current_problem) delete current_problem;
}

void MainWindow::on_btnEjecutar_clicked() {
    // 1. Capturar parámetros ingresados por el usuario en el panel izquierdo
    int clientes = ui->spinClientes->value();
    int vehiculos = ui->spinVehiculos->value();
    int capacidad = ui->spinCapacidad->value();

    // Generar una única instancia para garantizar consistencia comparativa
    if (current_problem) delete current_problem;
    current_problem = new Problem(clientes, 4, vehiculos, capacidad, 100);

    // 2. Evaluar Algoritmo 1 según selección
    VrpSolution solucion1;
    if (ui->comboAlgoritmo1->currentIndex() == 0) {
        GreedySolution solver(*current_problem);
        solucion1 = solver.Solve();
    } else {
        BruteForceSolution solver(*current_problem);
        solucion1 = solver.Solve();
    }

    // 3. Evaluar Algoritmo 2 según selección
    VrpSolution solucion2;
    if (ui->comboAlgoritmo2->currentIndex() == 0) {
        GreedySolution solver(*current_problem);
        solucion2 = solver.Solve();
    } else {
        BruteForceSolution solver(*current_problem);
        solucion2 = solver.Solve();
    }
    //limpiar
    if (ui->lienzoAlgoritmo1->scene()) {
        delete ui->lienzoAlgoritmo1->scene();
    }
    // 4. Enviar soluciones a los paneles de visualización del centro
    QGraphicsScene *scene1 = new QGraphicsScene(this);
    ui->lienzoAlgoritmo1->setScene(scene1);

    // Dibujar Depósito Central (Un cuadrado rojo grande en el centro)
    scene1->addRect(current_problem->depot_.x_ * 4 - 6, current_problem->depot_.y_ * 4 - 6, 12, 12,
                    QPen(Qt::red), QBrush(Qt::red));

    // Dibujar Clientes (Círculos azules)
    for (const auto& node : current_problem->nodes_) {
        scene1->addEllipse(node.x_ * 4 - 4, node.y_ * 4 - 4, 8, 8, QPen(Qt::blue), QBrush(Qt::blue));
    }

    // Dibujar Rutas de los Vehículos con colores distintos
    Qt::GlobalColor colores[] = {Qt::green, Qt::blue, Qt::cyan, Qt::magenta, Qt::yellow, Qt::darkYellow, Qt::darkCyan};
    for (const auto& v : solucion1.vehicles_) {
        if (v.nodes_.size() < 2) continue;

        // Elegir color según el ID del camión
        QPen pen(colores[v.id_ % 7]);
        pen.setWidth(2);

        for (size_t i = 0; i < v.nodes_.size() - 1; ++i) {
            int from_id = v.nodes_[i];
            int to_id = v.nodes_[i+1];

            // Obtener posiciones iniciales y finales
            Node from_node = (from_id == 0) ? current_problem->depot_ : current_problem->nodes_[from_id - 1];
            Node to_node = (to_id == 0) ? current_problem->depot_ : current_problem->nodes_[to_id - 1];

            scene1->addLine(from_node.x_ * 4, from_node.y_ * 4, to_node.x_ * 4, to_node.y_ * 4, pen);
        }
    }

    // =================================================================
    // MOTOR DE DIBUJO USANDO QGraphicsScene (Lienzo Inferior - Algoritmo 2)
    // =================================================================
    if (ui->lienzoAlgoritmo2->scene()) {
        delete ui->lienzoAlgoritmo2->scene();
    }
    QGraphicsScene *scene2 = new QGraphicsScene(this);
    ui->lienzoAlgoritmo2->setScene(scene2);

    // Dibujar Depósito Central
    scene2->addRect(current_problem->depot_.x_ * 4 - 6, current_problem->depot_.y_ * 4 - 6, 12, 12,
                    QPen(Qt::red), QBrush(Qt::red));

    // Dibujar Clientes
    for (const auto& node : current_problem->nodes_) {
        scene2->addEllipse(node.x_ * 4 - 4, node.y_ * 4 - 4, 8, 8, QPen(Qt::blue), QBrush(Qt::blue));
    }

    // Dibujar Rutas del segundo algoritmo
    for (const auto& v : solucion2.vehicles_) {
        if (v.nodes_.size() < 2) continue;

        QPen pen(colores[v.id_ % 7]);
        pen.setWidth(2);

        for (size_t i = 0; i < v.nodes_.size() - 1; ++i) {
            int from_id = v.nodes_[i];
            int to_id = v.nodes_[i+1];

            Node from_node = (from_id == 0) ? current_problem->depot_ : current_problem->nodes_[from_id - 1];
            Node to_node = (to_id == 0) ? current_problem->depot_ : current_problem->nodes_[to_id - 1];

            scene2->addLine(from_node.x_ * 4, from_node.y_ * 4, to_node.x_ * 4, to_node.y_ * 4, pen);
        }
    }

    ui->tablaResultados->setItem(0, 0, new QTableWidgetItem(QString::number(solucion1.total_cost_, 'f', 2)));
    // Celda (1, 0): Tiempo del Algoritmo 1
    ui->tablaResultados->setItem(1, 0, new QTableWidgetItem(QString::number(solucion1.execution_time_ms_, 'f', 3)));

    // Celda (0, 1): Distancia del Algoritmo 2
    ui->tablaResultados->setItem(0, 1, new QTableWidgetItem(QString::number(solucion2.total_cost_, 'f', 2)));
    // Celda (1, 1): Tiempo del Algoritmo 2
    ui->tablaResultados->setItem(1, 1, new QTableWidgetItem(QString::number(solucion2.execution_time_ms_, 'f', 3)));
}