#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "greedy.hpp"
#include "brute_force.hpp"
#include "local_search_intra.hpp"
#include <QFileDialog>
#include <QTextStream>
#include <QTimer>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Obliga a las columnas a estirarse uniformemente para ocupar todo el ancho disponible
    ui->tablaResultados->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // Obliga a las filas a hacer lo mismo verticalmente
    ui->tablaResultados->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->btnEjecutar->setStyleSheet("background-color: #2e7d32; color: white;");
    connect(ui->btnExportar, &QPushButton::clicked, this, &MainWindow::on_btnExportar_clicked);
}

MainWindow::~MainWindow() {
    delete ui;
    if (current_problem) delete current_problem;
}

void MainWindow::on_btnEjecutar_clicked() {
    int escala = 6;
    int radioNodo = 16;

    // Guardamos la capacidad que el usuario ha digitado libremente en la pantalla
    int capacidadUsuario = ui->spinCapacidad->value();

    if (current_problem) delete current_problem;

    if (!rutaArchivoImportado.isEmpty()) {
        current_problem = new Problem(100, rutaArchivoImportado.toStdString());

        // Sincronizamos clientes y vehículos del archivo
        ui->spinClientes->setValue(current_problem->noc_);
        ui->spinVehiculos->setValue(current_problem->nov_);

        // Si el usuario especificó una capacidad válida en la pantalla, la usamos, si es 0 usamos la del archivo
        if (capacidadUsuario > 0) {
            current_problem->capacity_ = capacidadUsuario;
        } else {
            ui->spinCapacidad->setValue(current_problem->capacity_);
        }
    } else {
        int clientes = ui->spinClientes->value();
        int vehiculos = ui->spinVehiculos->value();

        if (clientes <= 0) { clientes = 10; ui->spinClientes->setValue(10); }
        if (vehiculos <= 0) { vehiculos = 3; ui->spinVehiculos->setValue(3); }
        if (capacidadUsuario <= 0) { capacidadUsuario = 50; ui->spinCapacidad->setValue(50); }

        // Usar el constructor aleatorio seguro de manera 100% libre
        current_problem = new Problem(clientes, 10, vehiculos, capacidadUsuario, 100);
    }




    // =================================================================
    // ─── NUEVO BLOQUE: CÁLCULO DE DEMANDA VS CAPACIDAD TOTAL ───
    // =================================================================
    int demandaTotal = 0;
    for (const auto& node : current_problem->nodes_) {
        demandaTotal += node.demand_; // Sumamos el pedido de cada cliente
    }

    // Capacidad de la flota = Número de camiones × Capacidad de cada uno
    int capacidadTotalFlota = current_problem->nov_ * current_problem->capacity_;

    // Imprimimos los resultados directamente en los nuevos labels de la UI
    ui->lblDemandaTotal->setText(QString::number(demandaTotal));
    ui->lblCapacidadFlota->setText(QString::number(capacidadTotalFlota));

    // Opcional: Alerta visual en color rojo si la demanda supera la capacidad de la flota
    if (demandaTotal > capacidadTotalFlota) {
        ui->lblDemandaTotal->setStyleSheet("color: #d32f2f; font-weight: bold;"); // Rojo advertencia
        ui->lblCapacidadFlota->setStyleSheet("color: #d32f2f; font-weight: bold;");
    } else {
        ui->lblDemandaTotal->setStyleSheet("color: white; font-weight: bold;"); // Color normal (o el que use tu tema)
        ui->lblCapacidadFlota->setStyleSheet("color: white; font-weight: bold;");
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
    QGraphicsScene *scene1 = new QGraphicsScene(this);
    ui->lienzoAlgoritmo1->setScene(scene1);

    int depotX = current_problem->depot_.x_ * escala;
    int depotY = current_problem->depot_.y_ * escala;
    scene1->addRect(depotX - 8, depotY - 8, 16, 16, QPen(Qt::red), QBrush(Qt::red));

    Qt::GlobalColor colores[] = {Qt::green, Qt::blue, Qt::cyan, Qt::magenta, Qt::yellow, Qt::darkYellow, Qt::darkCyan};
    for (const auto& v : solucion1.vehicles_) {
        if (v.nodes_.size() < 2) continue;
        QPen pen(colores[v.id_ % 7]);
        pen.setWidth(3);

        for (size_t i = 0; i < v.nodes_.size() - 1; ++i) {
            int from_id = v.nodes_[i];
            int to_id = v.nodes_[i+1];

            Node from_node = (from_id == 0) ? current_problem->depot_ : current_problem->nodes_[from_id - 1];
            Node to_node = (to_id == 0) ? current_problem->depot_ : current_problem->nodes_[to_id - 1];

            scene1->addLine(from_node.x_ * escala, from_node.y_ * escala,
                            to_node.x_ * escala, to_node.y_ * escala, pen);
        }
    }

    for (const auto& node : current_problem->nodes_) {
        int posX = node.x_ * escala;
        int posY = node.y_ * escala;

        scene1->addEllipse(posX - radioNodo, posY - radioNodo, radioNodo * 2, radioNodo * 2,
                           QPen(Qt::white, 2), QBrush(Qt::blue));

        if (ui->chkMostrarDemandas->isChecked()) {
            QGraphicsTextItem *textoDemanda = scene1->addText(QString::number(node.demand_));
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

    // =================================================================
    // MOTOR DE DIBUJO USANDO QGraphicsScene (Lienzo Algoritmo 2)
    // =================================================================
    if (ui->lienzoAlgoritmo2->scene()) {
        delete ui->lienzoAlgoritmo2->scene();
    }
    QGraphicsScene *scene2 = new QGraphicsScene(this);
    ui->lienzoAlgoritmo2->setScene(scene2);

    scene2->addRect(depotX - 8, depotY - 8, 16, 16, QPen(Qt::red), QBrush(Qt::red));

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

    ui->tablaResultados->setItem(0, 0, new QTableWidgetItem(QString::number(solucion1.total_cost_, 'f', 2)));
    ui->tablaResultados->setItem(1, 0, new QTableWidgetItem(QString::number(solucion1.execution_time_ms_, 'f', 3)));
    ui->tablaResultados->setItem(0, 1, new QTableWidgetItem(QString::number(solucion2.total_cost_, 'f', 2)));
    ui->tablaResultados->setItem(1, 1, new QTableWidgetItem(QString::number(solucion2.execution_time_ms_, 'f', 3)));

    rutaArchivoImportado = "";
    ui->btnImportar->setText("Importar Datos (.txt)");
    ui->btnImportar->setStyleSheet("");
}

void MainWindow::on_btnImportar_clicked() {
    QString ruta = QFileDialog::getOpenFileName(this,
                                                tr("Seleccionar archivo de clientes"), "", tr("Archivos de texto (*.txt)"));

    if (!ruta.isEmpty()) {
        rutaArchivoImportado = ruta;
        ui->btnImportar->setText("Archivo Cargado");
        ui->btnImportar->setStyleSheet("background-color: #2e7d32; color: white;");
    }
}

void MainWindow::on_btnExportar_clicked() {
    // Si no se ha generado o importado ningún problema, no hay nada que exportar
    if (!current_problem) {
        return;
    }

    // Abre el diálogo nativo del sistema operativo para guardar el archivo
    QString rutaGuardar = QFileDialog::getSaveFileName(this,
                                                       tr("Exportar Instancia Actual"),
                                                       "",
                                                       tr("Archivos de texto (*.txt)"));

    if (rutaGuardar.isEmpty()) {
        return; // El usuario canceló la ventana de guardado
    }

    QFile archivo(rutaGuardar);
    if (archivo.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&archivo);

        // 1. Primera fila: Número de clientes, número de vehículos y capacidad
        out << current_problem->noc_ << " "
            << current_problem->nov_ << " "
            << current_problem->capacity_ << "\n";

        // 2. Siguientes filas: Solo las coordenadas X, Y y la Demanda de cada cliente
        // Se omite por completo el ID y los datos del depósito
        for (const auto& node : current_problem->nodes_) {
            out << node.x_ << " "
                << node.y_ << " "
                << node.demand_ << "\n";
        }

        archivo.close();

        // Animación temporal para confirmar el éxito en la interfaz
        ui->btnExportar->setText("¡Instancia Guardada!");
        QTimer::singleShot(2000, this, [this]() {
            ui->btnExportar->setText("Exportar Instancia (.txt)");
        });
    }
}