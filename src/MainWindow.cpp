#include "MainWindow.h"
#include <stdio.h>

MainWindow::MainWindow()
{
    QVBoxLayout *hGroupLayout = new QVBoxLayout();
    QHBoxLayout *vTempLayout = new QHBoxLayout();

    numOfLanesLabel = new QLabel("Number of Lanes:");
    numOfLanesSpinBox = new QSpinBox();
    numOfLanesSpinBox->setValue(2);
    vTempLayout->addWidget(numOfLanesLabel);
    vTempLayout->addWidget(numOfLanesSpinBox);
    hGroupLayout->addLayout(vTempLayout);

    numOfCellsLabel = new QLabel("Number of Cells:");
    numOfCellsLineEdit = new QLineEdit();
    numOfCellsLineEdit->setText("100000");
    vTempLayout = new QHBoxLayout();
    vTempLayout->addWidget(numOfCellsLabel);
    vTempLayout->addWidget(numOfCellsLineEdit);
    hGroupLayout->addLayout(vTempLayout);

    numOfCarsLabel = new QLabel("Number of Cars:");
    numOfCarsLineEdit = new QLineEdit();
    numOfCarsLineEdit->setText("1000");
    vTempLayout = new QHBoxLayout();
    vTempLayout->addWidget(numOfCarsLabel);
    vTempLayout->addWidget(numOfCarsLineEdit);
    hGroupLayout->addLayout(vTempLayout);

    numOfTimeStepsLabel = new QLabel("Number of Time Steps:");
    numOfTimeStepsLineEdit = new QLineEdit();
    numOfTimeStepsLineEdit->setText("100000");
    vTempLayout = new QHBoxLayout();
    vTempLayout->addWidget(numOfTimeStepsLabel);
    vTempLayout->addWidget(numOfTimeStepsLineEdit);
    hGroupLayout->addLayout(vTempLayout);

    globalParamBox = new QGroupBox();
    globalParamBox->setTitle("Global Model Options");
    globalParamBox->setLayout(hGroupLayout);

    hGroupLayout = new QVBoxLayout();

    maxVelLabel = new QLabel("Maximum Car Velocity:");
    maxVelSpinBox = new QSpinBox();
    maxVelSpinBox->setValue(6);
    vTempLayout = new QHBoxLayout();
    vTempLayout->addWidget(maxVelLabel);
    vTempLayout->addWidget(maxVelSpinBox);
    hGroupLayout->addLayout(vTempLayout);

    brakeLabel = new QLabel("Propability of Braking:");
    brakeLineEdit = new QLineEdit();
    brakeLineEdit->setText("0.02");
    vTempLayout = new QHBoxLayout();
    vTempLayout->addWidget(brakeLabel);
    vTempLayout->addWidget(brakeLineEdit);
    hGroupLayout->addLayout(vTempLayout);

    truckLabel = new QLabel("Percentage of Trucks:");
    truckLineEdit = new QLineEdit();
    truckLineEdit->setText("0.1");
    vTempLayout = new QHBoxLayout();
    vTempLayout->addWidget(truckLabel);
    vTempLayout->addWidget(truckLineEdit);
    hGroupLayout->addLayout(vTempLayout);

    carParamBox = new QGroupBox();
    carParamBox->setTitle("Car Options");
    carParamBox->setLayout(hGroupLayout);

    runButton = new QPushButton("Run Model");
    connect(runButton, SIGNAL(clicked()), this, SLOT(run()));
    vLayout = new QHBoxLayout();
    vLayout->addWidget(globalParamBox);
    vLayout->addWidget(carParamBox);
    hLayout = new QVBoxLayout;
    hLayout->addLayout(vLayout);
    hLayout->addWidget(runButton);

    setLayout(hLayout);
}

void MainWindow::run()
{

}

MainWindow::~MainWindow()
{
    /*if(globalParamBox)          delete globalParamBox;
    if(numOfLanesLabel)         delete numOfLanesLabel;
    if(numOfLanesSpinBox)       delete numOfLanesSpinBox;
    if(numOfCellsLabel)         delete numOfCellsLabel;
    if(numOfCellsLineEdit)      delete numOfCellsLineEdit;
    if(numOfCarsLabel)          delete numOfCarsLabel;
    if(numOfCarsLineEdit)       delete numOfCarsLineEdit;
    if(numOfTimeStepsLabel)     delete numOfTimeStepsLabel;
    if(numOfTimeStepsLineEdit)  delete numOfTimeStepsLineEdit;

    if(carParamBox)             delete carParamBox;
    if(maxVelLabel)             delete maxVelLabel;
    if(maxVelSpinBox)           delete maxVelSpinBox;
    if(brakeLabel)              delete brakeLabel;
    if(brakeLineEdit)           delete brakeLineEdit;
    if(truckLabel)              delete truckLabel;
    if(truckLineEdit)           delete truckLineEdit;

    if(runButton)               delete runButton;*/
}
