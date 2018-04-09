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
    connect(mol_, SIGNAL(atomWasSelected(AtomX)), this, SLOT(setSelAtom(AtomX)));
    connect(this, SIGNAL(loadMoleculeClicked(QString)),mol_,SLOT(loadMolecule(QString)));
    connect(mol_, SIGNAL(molNameDefined(QString)), this,SLOT(setMolName(QString)));
}


void MainWindow::setMolName(QString fileName){
    QString nameOnly = fileName.mid(fileName.lastIndexOf("/") + 1);
    ui->molName->setText(nameOnly.left(nameOnly.size() - 5));
    AtomX atom0;
    atom0.label = "";
    setSelAtom(atom0);
}

void MainWindow::setSelAtom(AtomX atom0){

    if(atom0.label == "")
    {
        ui->atomSel->setText("");
        ui->atomLabel->setText("");
        ui->atomX->setText("");
        ui->atomY->setText("");
        ui->atomZ->setText("");
    }
    else
    {
        QString xStr, yStr, zStr;
        xStr.sprintf("%5.3f",atom0.coord.x());
        yStr.sprintf("%5.3f",atom0.coord.y());
        zStr.sprintf("%5.3f",atom0.coord.z());
        ui->atomSel->setText(QString::number(atom0.atomOrderNumber));
        ui->atomLabel->setText(atom0.label);
        ui->atomX->setText(xStr);
        ui->atomY->setText(yStr);
        ui->atomZ->setText(zStr);
    }
}

void MainWindow::on_buttonLoadMolecule_clicked()
{
    OpenFileWindows open;
    QString fileName = open.loadMoleculeWindow();

    emit loadMoleculeClicked(fileName);
}

