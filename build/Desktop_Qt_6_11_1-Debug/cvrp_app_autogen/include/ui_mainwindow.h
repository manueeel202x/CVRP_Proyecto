/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QWidget *panelIzquierdo;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSpinBox *spinClientes;
    QLabel *label_2;
    QSpinBox *spinVehiculos;
    QLabel *label_3;
    QSpinBox *spinCapacidad;
    QComboBox *comboAlgoritmo1;
    QComboBox *comboAlgoritmo2;
    QCheckBox *chkMostrarDemandas;
    QPushButton *btnEjecutar;
    QWidget *contenedorDerecho;
    QVBoxLayout *verticalLayout_2;
    QWidget *panelSuperior;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *lienzoAlgoritmo1;
    QGraphicsView *lienzoAlgoritmo2;
    QWidget *panelInferior;
    QHBoxLayout *horizontalLayout_3;
    QTableWidget *tablaResultados;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1225, 643);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        panelIzquierdo = new QWidget(centralwidget);
        panelIzquierdo->setObjectName("panelIzquierdo");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(panelIzquierdo->sizePolicy().hasHeightForWidth());
        panelIzquierdo->setSizePolicy(sizePolicy);
        panelIzquierdo->setMaximumSize(QSize(200, 16777215));
        verticalLayout = new QVBoxLayout(panelIzquierdo);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(panelIzquierdo);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        spinClientes = new QSpinBox(panelIzquierdo);
        spinClientes->setObjectName("spinClientes");

        verticalLayout->addWidget(spinClientes);

        label_2 = new QLabel(panelIzquierdo);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        spinVehiculos = new QSpinBox(panelIzquierdo);
        spinVehiculos->setObjectName("spinVehiculos");

        verticalLayout->addWidget(spinVehiculos);

        label_3 = new QLabel(panelIzquierdo);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        spinCapacidad = new QSpinBox(panelIzquierdo);
        spinCapacidad->setObjectName("spinCapacidad");

        verticalLayout->addWidget(spinCapacidad);

        comboAlgoritmo1 = new QComboBox(panelIzquierdo);
        comboAlgoritmo1->addItem(QString());
        comboAlgoritmo1->addItem(QString());
        comboAlgoritmo1->addItem(QString());
        comboAlgoritmo1->setObjectName("comboAlgoritmo1");

        verticalLayout->addWidget(comboAlgoritmo1);

        comboAlgoritmo2 = new QComboBox(panelIzquierdo);
        comboAlgoritmo2->addItem(QString());
        comboAlgoritmo2->addItem(QString());
        comboAlgoritmo2->addItem(QString());
        comboAlgoritmo2->setObjectName("comboAlgoritmo2");

        verticalLayout->addWidget(comboAlgoritmo2);

        chkMostrarDemandas = new QCheckBox(panelIzquierdo);
        chkMostrarDemandas->setObjectName("chkMostrarDemandas");

        verticalLayout->addWidget(chkMostrarDemandas);

        btnEjecutar = new QPushButton(panelIzquierdo);
        btnEjecutar->setObjectName("btnEjecutar");

        verticalLayout->addWidget(btnEjecutar);


        horizontalLayout_2->addWidget(panelIzquierdo);

        contenedorDerecho = new QWidget(centralwidget);
        contenedorDerecho->setObjectName("contenedorDerecho");
        verticalLayout_2 = new QVBoxLayout(contenedorDerecho);
        verticalLayout_2->setObjectName("verticalLayout_2");
        panelSuperior = new QWidget(contenedorDerecho);
        panelSuperior->setObjectName("panelSuperior");
        panelSuperior->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(panelSuperior->sizePolicy().hasHeightForWidth());
        panelSuperior->setSizePolicy(sizePolicy1);
        panelSuperior->setMaximumSize(QSize(16777215, 16777215));
        horizontalLayout = new QHBoxLayout(panelSuperior);
        horizontalLayout->setObjectName("horizontalLayout");
        lienzoAlgoritmo1 = new QGraphicsView(panelSuperior);
        lienzoAlgoritmo1->setObjectName("lienzoAlgoritmo1");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lienzoAlgoritmo1->sizePolicy().hasHeightForWidth());
        lienzoAlgoritmo1->setSizePolicy(sizePolicy2);
        lienzoAlgoritmo1->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(lienzoAlgoritmo1);

        lienzoAlgoritmo2 = new QGraphicsView(panelSuperior);
        lienzoAlgoritmo2->setObjectName("lienzoAlgoritmo2");
        sizePolicy2.setHeightForWidth(lienzoAlgoritmo2->sizePolicy().hasHeightForWidth());
        lienzoAlgoritmo2->setSizePolicy(sizePolicy2);
        lienzoAlgoritmo2->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(lienzoAlgoritmo2);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 1);

        verticalLayout_2->addWidget(panelSuperior);

        panelInferior = new QWidget(contenedorDerecho);
        panelInferior->setObjectName("panelInferior");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(panelInferior->sizePolicy().hasHeightForWidth());
        panelInferior->setSizePolicy(sizePolicy3);
        panelInferior->setMinimumSize(QSize(0, 0));
        panelInferior->setMaximumSize(QSize(16777215, 16777215));
        horizontalLayout_3 = new QHBoxLayout(panelInferior);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        tablaResultados = new QTableWidget(panelInferior);
        if (tablaResultados->columnCount() < 2)
            tablaResultados->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tablaResultados->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tablaResultados->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (tablaResultados->rowCount() < 2)
            tablaResultados->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tablaResultados->setVerticalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tablaResultados->setVerticalHeaderItem(1, __qtablewidgetitem3);
        tablaResultados->setObjectName("tablaResultados");
        tablaResultados->setMinimumSize(QSize(550, 0));
        tablaResultados->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_3->addWidget(tablaResultados, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);


        verticalLayout_2->addWidget(panelInferior);

        verticalLayout_2->setStretch(0, 2);
        verticalLayout_2->setStretch(1, 1);

        horizontalLayout_2->addWidget(contenedorDerecho);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Clientes", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Vehiculos", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Capacidad", nullptr));
        comboAlgoritmo1->setItemText(0, QCoreApplication::translate("MainWindow", "Greedy", nullptr));
        comboAlgoritmo1->setItemText(1, QCoreApplication::translate("MainWindow", "Fuerza Bruta", nullptr));
        comboAlgoritmo1->setItemText(2, QCoreApplication::translate("MainWindow", "Busqueda Local (Intra-vehiculo)", nullptr));

        comboAlgoritmo2->setItemText(0, QCoreApplication::translate("MainWindow", "Greedy", nullptr));
        comboAlgoritmo2->setItemText(1, QCoreApplication::translate("MainWindow", "Fuerza Bruta", nullptr));
        comboAlgoritmo2->setItemText(2, QCoreApplication::translate("MainWindow", "Busqueda Local (Intra - vehiculo)", nullptr));

        chkMostrarDemandas->setText(QCoreApplication::translate("MainWindow", "Mostrar Demandas", nullptr));
        btnEjecutar->setText(QCoreApplication::translate("MainWindow", "Ejecutar", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tablaResultados->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Algoritmo1", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tablaResultados->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Algoritmo2", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tablaResultados->verticalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Distancia total (km)", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tablaResultados->verticalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Tiempo de ejecuci\303\263n (ms)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
