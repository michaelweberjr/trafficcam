/*
    ResultWindow.cpp - (c) Michael Weber, Jr. (2012)

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

#include "ResultWindow.h"
#include <stdio.h>

ResultWindow::ResultWindow(QWidget *parent)
    : QWidget(parent)
{
    model = Model::instance;

    tickLabel = new QLabel("Current Time Step:");
    tickCountLabel = new QLabel(QString("%1").arg(model->currentTick+1));
    tickLayout = new QHBoxLayout();
    tickLayout->addStretch();
    tickLayout->addWidget(tickLabel);
    tickLayout->addWidget(tickCountLabel);
    tickLayout->addStretch();

    plot = new QCustomPlot();
    plot->xAxis->setLabel("Time Step");
    plot->yAxis->setLabel("Number of Cars");

    lane1 = new QCPCurve(plot->xAxis, plot->yAxis);
    lane1->setData(model->time_count, model->lane1_use);
    lane1->setPen(QPen(Qt::red));
    plot->addPlottable(lane1);

    lane2 = new QCPCurve(plot->xAxis, plot->yAxis);
    lane2->setData(model->time_count, model->lane2_use);
    lane2->setPen(QPen(Qt::blue));
    plot->addPlottable(lane2);

    mainLayout = new QVBoxLayout();
    mainLayout->addLayout(tickLayout);
    mainLayout->addWidget(plot);
    setLayout(mainLayout);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
    //timer->start(1);
}

ResultWindow::~ResultWindow()
{
    delete timer;
    delete plot;
    delete lane1;
    delete lane2;
    delete tickLabel;
    delete tickCountLabel;
    delete tickLayout;
    delete mainLayout;
}

void ResultWindow::tick()
{
    tickCountLabel->setText(QString("%1").arg(model->currentTick+1));
    model->tick();
    if(model->currentTick == model->numberofTimeSteps)
        timer->stop();
}
