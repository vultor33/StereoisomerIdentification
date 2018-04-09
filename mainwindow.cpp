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
    connect(this, SIGNAL(loadMoleculeClicked(QString)),mol_,SLOT(loadMolecule(QString)));
    connect(mol_, SIGNAL(molNameDefined(QString)), this,SLOT(setMolName(QString)));
}


void MainWindow::setMolName(QString fileName){
    QString nameOnly = fileName.mid(fileName.lastIndexOf("/") + 1);
    ui->molName->setText(nameOnly.left(nameOnly.size() - 5));
    ui->atomSel->setText("");
}

void MainWindow::setSelAtom(QString selAtom){
    ui->atomSel->setText(selAtom);
}

void MainWindow::on_buttonLoadMolecule_clicked()
{
    OpenFileWindows open;
    QString fileName = open.loadMoleculeWindow();

    emit loadMoleculeClicked(fileName);
}

