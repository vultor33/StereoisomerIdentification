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
    connect(mol_, SIGNAL(atomWasSelected(QString)), this, SLOT(setSelAtom(QString)));
    connect(this, SIGNAL(reescaleClicked(qreal)),mol_,SLOT(reescaleReceiving(qreal)));
    connect(this, SIGNAL(loadMoleculeClicked(QString)),mol_,SLOT(loadMolecule(QString)));
}



void MainWindow::setMolName(const QString &name){
    //ui->molName->setText(name);
}

void MainWindow::setSelAtom(QString selAtom){
    ui->atomSel->setText(selAtom);
}

void MainWindow::on_buttonReescale_clicked()
{
    emit reescaleClicked(ui->lineReescale->text().toFloat());
}

void MainWindow::on_buttonLoadMolecule_clicked()
{
    OpenFileWindows open;
    QString fileName = open.loadMoleculeWindow();

    emit loadMoleculeClicked(fileName);
}




