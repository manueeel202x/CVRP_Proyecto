#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QPen>
#include <QBrush>
#include <QMainWindow>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include "vrp_base.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnEjecutar_clicked(); // Slot conectado al botón de acción
    void on_btnImportar_clicked();

private:
    Ui::MainWindow *ui;
    // La instancia del problema compartido para evaluar ambos algoritmos sobre los mismos datos
    Problem *current_problem = nullptr;
    QString rutaArchivoImportado = "";
};

#endif // MAINWINDOW_HPP