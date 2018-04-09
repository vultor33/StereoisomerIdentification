#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include "showmolecule.h"
#include "openfilewindows.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectWithMol(ShowMolecule *mol_)
{
    connect(mol_, SIGNAL(atomWasSelected(AtomsX)), this, SLOT(setSelAtom(AtomsX)));
    connect(this, SIGNAL(loadMoleculeClicked(QString)),mol_,SLOT(loadMolecule(QString)));
    connect(mol_, SIGNAL(molNameDefined(QString)), this,SLOT(setMolName(QString)));
}


void MainWindow::setMolName(QString fileName){
    QString nameOnly = fileName.mid(fileName.lastIndexOf("/") + 1);
    ui->molName->setText(nameOnly.left(nameOnly.size() - 5));
    AtomsX atom0;
    atom0.label1 = "";
    atom0.label2 = "";
    setSelAtom(atom0);
}

void MainWindow::setSelAtom(AtomsX atom0){
    ui->atomSel->setText("");
    ui->atomLabel->setText("");
    ui->atomX->setText("");
    ui->atomY->setText("");
    ui->atomZ->setText("");
    ui->atomSel_2->setText("");
    ui->atomLabel_2->setText("");
    ui->atomX_2->setText("");
    ui->atomY_2->setText("");
    ui->atomZ_2->setText("");

    if(atom0.label1 != "")
    {
        QString xStr, yStr, zStr;
        xStr.sprintf("%5.3f",atom0.coord1.x());
        yStr.sprintf("%5.3f",atom0.coord1.y());
        zStr.sprintf("%5.3f",atom0.coord1.z());
        ui->atomSel->setText(QString::number(atom0.atomOrderNumber1));
        ui->atomLabel->setText(atom0.label1);
        ui->atomX->setText(xStr);
        ui->atomY->setText(yStr);
        ui->atomZ->setText(zStr);
    }
    if(atom0.label2 != "")
    {
        QString xStr, yStr, zStr;
        xStr.sprintf("%5.3f",atom0.coord2.x());
        yStr.sprintf("%5.3f",atom0.coord2.y());
        zStr.sprintf("%5.3f",atom0.coord2.z());
        ui->atomSel_2->setText(QString::number(atom0.atomOrderNumber2));
        ui->atomLabel_2->setText(atom0.label2);
        ui->atomX_2->setText(xStr);
        ui->atomY_2->setText(yStr);
        ui->atomZ_2->setText(zStr);
    }
}

void MainWindow::on_buttonLoadMolecule_clicked()
{
    OpenFileWindows open;
    QString fileName = open.loadMoleculeWindow();

    emit loadMoleculeClicked(fileName);
}

