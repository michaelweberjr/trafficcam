/*
    ResultWindow.h - (c) Michael Weber, Jr. (2012)

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

#ifndef RESULTWINDOW_H
#define RESULTWINDOW_H

#include <QtGui>
#include "qcustomplot.h"
#include "model.h"

class ResultWindow : public QWidget
{
    Q_OBJECT

    public:
        ResultWindow(QWidget *parent);
        virtual ~ResultWindow();

    public slots:
        void tick();

    private:
        QTimer *timer;
        QCustomPlot *plot;
        Model *model;
        QCPCurve *lane1;
        QCPCurve *lane2;
        QLabel *tickLabel;
        QLabel *tickCountLabel;
        QHBoxLayout *tickLayout;
        QVBoxLayout *mainLayout;
};

#endif
