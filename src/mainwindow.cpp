#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "greedy.hpp"
#include "brute_force.hpp"
#include "local_search_intra.hpp"
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Obliga a las columnas a estirarse uniformemente para ocupar todo el ancho disponible
    ui->tablaResultados->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // Obliga a las filas a hacer lo mismo verticalmente
    ui->tablaResultados->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->btnEjecutar->setStyleSheet("background-color: #2e7d32; color: white;");


}

MainWindow::~MainWindow() {
    delete ui;
    if (current_problem) delete current_problem;
}

void MainWindow::on_btnEjecutar_clicked() {
    int escala = 6;
    int radioNodo = 16;

    // Generar una única instancia para garantizar consistencia comparativa
    if (current_problem) delete current_problem;

    if (!rutaArchivoImportado.isEmpty()) {
        current_problem = new Problem(100, rutaArchivoImportado.toStdString());
        //mostrar los valores leidos del .txt
        ui->spinClientes->setValue(current_problem->noc_);
        ui->spinVehiculos->setValue(current_problem->nov_);
        ui->spinCapacidad->setValue(current_problem->capacity_);
    } else {
        // Capturar parámetros ingresados por el usuario en el panel izquierdo
        int clientes = ui->spinClientes->value();
        int vehiculos = ui->spinVehiculos->value();
        int capacidad = ui->spinCapacidad->value();
        // Usar el constructor aleatorio de siempre
        current_problem = new Problem(clientes, 4, vehiculos, capacidad, 100);
    }

    // 2. Evaluar Algoritmo 1 según selección
    VrpSolution solucion1;
    if (ui->comboAlgoritmo1->currentIndex() == 0) {
        GreedySolution solver(*current_problem);
        solucion1 = solver.Solve();
    } else if (ui->comboAlgoritmo1->currentIndex() == 1) {
        BruteForceSolution solver(*current_problem);
        solucion1 = solver.Solve();
    } else {
        LocalSearchIntraSolution solver(*current_problem);
        solucion1 = solver.Solve();
    }

    // 3. Evaluar Algoritmo 2 según selección
    VrpSolution solucion2;
    if (ui->comboAlgoritmo2->currentIndex() == 0) {
        GreedySolution solver(*current_problem);
        solucion2 = solver.Solve();
    } else if (ui->comboAlgoritmo2->currentIndex() == 1) {
        BruteForceSolution solver(*current_problem);
        solucion2 = solver.Solve();
    } else {
        LocalSearchIntraSolution solver(*current_problem);
        solucion2 = solver.Solve();
    }


    // =================================================================
    // MOTOR DE DIBUJO USANDO QGraphicsScene (Lienzo Algoritmo 1)
    // =================================================================
    if (ui->lienzoAlgoritmo1->scene()) {
        delete ui->lienzoAlgoritmo1->scene();
    }
    // Enviar soluciones a los paneles de visualización del centro
    QGraphicsScene *scene1 = new QGraphicsScene(this);
    ui->lienzoAlgoritmo1->setScene(scene1);

    int depotX = current_problem->depot_.x_ * escala;
    int depotY = current_problem->depot_.y_ * escala;
    scene1->addRect(depotX - 8, depotY - 8, 16, 16, QPen(Qt::red), QBrush(Qt::red));

    // Dibujar las Rutas primero (para que queden por debajo de los círculos)
    Qt::GlobalColor colores[] = {Qt::green, Qt::blue, Qt::cyan, Qt::magenta, Qt::yellow, Qt::darkYellow, Qt::darkCyan};
    for (const auto& v : solucion1.vehicles_) {
        if (v.nodes_.size() < 2) continue;
        QPen pen(colores[v.id_ % 7]);
        pen.setWidth(3); // Grosor equilibrado

        for (size_t i = 0; i < v.nodes_.size() - 1; ++i) {
            int from_id = v.nodes_[i];
            int to_id = v.nodes_[i+1];

            Node from_node = (from_id == 0) ? current_problem->depot_ : current_problem->nodes_[from_id - 1];
            Node to_node = (to_id == 0) ? current_problem->depot_ : current_problem->nodes_[to_id - 1];

            // Conectamos exactamente los centros geométricos
            scene1->addLine(from_node.x_ * escala, from_node.y_ * escala,
                            to_node.x_ * escala, to_node.y_ * escala, pen);
        }
    }

    // 3. Dibujar los Nodos Clientes arriba de las líneas
    for (const auto& node : current_problem->nodes_) {
        int posX = node.x_ * escala;
        int posY = node.y_ * escala;

        // Círculo del cliente
        scene1->addEllipse(posX - radioNodo, posY - radioNodo, radioNodo * 2, radioNodo * 2,
                           QPen(Qt::white, 2), QBrush(Qt::blue));

        // Texto de la demanda al frente de todo
        if (ui->chkMostrarDemandas->isChecked()) {
            QGraphicsTextItem *textoDemanda = scene1->addText(QString::number(node.demand_));
            textoDemanda->setDefaultTextColor(Qt::white);

            QFont font = textoDemanda->font();
            font.setPointSize(11); // Letra grande y legible
            font.setBold(true);
            textoDemanda->setFont(font);

            // Centrado matemático perfecto dentro del círculo azul
            double textWidth = textoDemanda->boundingRect().width();
            double textHeight = textoDemanda->boundingRect().height();
            textoDemanda->setPos(posX - (textWidth / 2), posY - (textHeight / 2));
        }
    }
    // =================================================================
    // MOTOR DE DIBUJO USANDO QGraphicsScene (Lienzo Algoritmo 2)
    // =================================================================
    if (ui->lienzoAlgoritmo2->scene()) {
        delete ui->lienzoAlgoritmo2->scene();
    }
    QGraphicsScene *scene2 = new QGraphicsScene(this);
    ui->lienzoAlgoritmo2->setScene(scene2);

    // 1. Centro real del depósito en Escena 2
    scene2->addRect(depotX - 8, depotY - 8, 16, 16, QPen(Qt::red), QBrush(Qt::red));

    // 2. Dibujar las Rutas de la solución 2
    for (const auto& v : solucion2.vehicles_) {
        if (v.nodes_.size() < 2) continue;
        QPen pen(colores[v.id_ % 7]);
        pen.setWidth(3);

        for (size_t i = 0; i < v.nodes_.size() - 1; ++i) {
            int from_id = v.nodes_[i];
            int to_id = v.nodes_[i+1];

            Node from_node = (from_id == 0) ? current_problem->depot_ : current_problem->nodes_[from_id - 1];
            Node to_node = (to_id == 0) ? current_problem->depot_ : current_problem->nodes_[to_id - 1];

            scene2->addLine(from_node.x_ * escala, from_node.y_ * escala,
                            to_node.x_ * escala, to_node.y_ * escala, pen);
        }
    }

    // 3. Dibujar los Nodos Clientes en Escena 2
    for (const auto& node : current_problem->nodes_) {
        int posX = node.x_ * escala;
        int posY = node.y_ * escala;

        scene2->addEllipse(posX - radioNodo, posY - radioNodo, radioNodo * 2, radioNodo * 2,
                           QPen(Qt::white, 2), QBrush(Qt::blue));

        if (ui->chkMostrarDemandas->isChecked()) {
            QGraphicsTextItem *textoDemanda = scene2->addText(QString::number(node.demand_));
            textoDemanda->setDefaultTextColor(Qt::white);

            QFont font = textoDemanda->font();
            font.setPointSize(11);
            font.setBold(true);
            textoDemanda->setFont(font);

            double textWidth = textoDemanda->boundingRect().width();
            double textHeight = textoDemanda->boundingRect().height();
            textoDemanda->setPos(posX - (textWidth / 2), posY - (textHeight / 2));
        }
    }
    // Celda (0, 0): Distancia del Algoritmo 1
    ui->tablaResultados->setItem(0, 0, new QTableWidgetItem(QString::number(solucion1.total_cost_, 'f', 2)));
    // Celda (1, 0): Tiempo del Algoritmo 1
    ui->tablaResultados->setItem(1, 0, new QTableWidgetItem(QString::number(solucion1.execution_time_ms_, 'f', 3)));

    // Celda (0, 1): Distancia del Algoritmo 2
    ui->tablaResultados->setItem(0, 1, new QTableWidgetItem(QString::number(solucion2.total_cost_, 'f', 2)));
    // Celda (1, 1): Tiempo del Algoritmo 2
    ui->tablaResultados->setItem(1, 1, new QTableWidgetItem(QString::number(solucion2.execution_time_ms_, 'f', 3)));

    //ui->lienzoAlgoritmo1->scale(1.2, 1.2); // Hace un zoom dinámico del 150%
    //ui->lienzoAlgoritmo2->scale(1.2, 1.2);

    rutaArchivoImportado = "";
    ui->btnImportar->setText("Importar Datos (.txt)");
    ui->btnImportar->setStyleSheet(""); // Restaura estilo original
}

void MainWindow::on_btnImportar_clicked() {
    QString ruta = QFileDialog::getOpenFileName(this,
                                                tr("Seleccionar archivo de clientes"), "", tr("Archivos de texto (*.txt)"));

    if (!ruta.isEmpty()) {
        rutaArchivoImportado = ruta;
        // Opcional: Cambiar el texto del botón para mostrar que ya se cargó un archivo
        ui->btnImportar->setText("Archivo Cargado");
        ui->btnImportar->setStyleSheet("background-color: #2e7d32; color: white;"); // Verde éxito
    }
}