#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "model.h"

class MainWindow : public QWidget
{
    Q_OBJECT

    public:
        MainWindow();
        virtual ~MainWindow();

        Model *model;

    public slots:
        void run();

    private:
        QGroupBox   *globalParamBox;
        QLabel      *numOfLanesLabel;
        QSpinBox    *numOfLanesSpinBox;
        QLabel      *numOfCellsLabel;
        QLineEdit   *numOfCellsLineEdit;
        QLabel      *numOfCarsLabel;
        QLineEdit   *numOfCarsLineEdit;
        QLabel      *numOfTimeStepsLabel;
        QLineEdit   *numOfTimeStepsLineEdit;

        QGroupBox   *carParamBox;
        QLabel      *maxVelLabel;
        QSpinBox    *maxVelSpinBox;
        QLabel      *brakeLabel;
        QLineEdit   *brakeLineEdit;
        QLabel      *truckLabel;
        QLineEdit   *truckLineEdit;

        QPushButton *runButton;
        QVBoxLayout *hLayout;
        QHBoxLayout *vLayout;
};

#endif // MAINWINDOW_H
