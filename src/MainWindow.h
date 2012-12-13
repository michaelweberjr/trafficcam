/*
    MainWindow.h - (c) Michael Weber, Jr. (2012)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "ResultWindow.h"
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
        QSpinBox    *voffSpinBox;

        QPushButton *runButton;
        QVBoxLayout *hLayout;
        QHBoxLayout *vLayout;
};

#endif // MAINWINDOW_H
