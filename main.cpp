#include "mainwindow.h"

#include <QApplication>
#include <Qt3DExtras>
#include <QWidget>
#include <QMdiArea>
#include <QLCDNumber>
#include <QMainWindow>
#include <QMdiSubWindow>
#include <QObjectPicker>
#include <Qt3DRender>
#include <QCamera>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QMessageBox>
#include <sstream>
#include <fstream>
#include <string>
#include <QViewport>
#include <QObject>
#include <QFileDialog>

#include "showmolecule.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow w;
    w.setWindowTitle("Complex Identification");
    QMdiArea *centralWidget = new QMdiArea;

    //molecule
    ShowMolecule mol_;
    QString fileName = "C:\\Users\\basta\\Documents\\Visual Studio 2015\\Projects\\Qt-Projects\\visual-3\\t4-isomer.mol2";
    //Qt3DExtras::Qt3DWindow *view = mol_.loadMolecule(fileName);
    Qt3DExtras::Qt3DWindow *view = mol_.showMoleculeInitialization();
    QWidget *molBox = QWidget::createWindowContainer(view);
    centralWidget->addSubWindow(molBox);

    //in
    MainWindow interface;
    centralWidget->addSubWindow(&interface);
    interface.setMolName(mol_.getMolName());
    interface.setSelAtom("");

    interface.connectWithMol(&mol_);

    //molecule2
    ShowMolecule mol2_;
    Qt3DExtras::Qt3DWindow *view2 = mol2_.showMoleculeInitialization();
    QWidget *molBox2 = QWidget::createWindowContainer(view2);
    centralWidget->addSubWindow(molBox2);


    QList<QMdiSubWindow *> subList = centralWidget->subWindowList();
    subList[0]->setFixedHeight(600);
    subList[0]->setFixedWidth(400);
    subList[0]->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    subList[1]->setFixedHeight(600);
    subList[1]->setFixedWidth(400);
    subList[1]->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    subList[2]->setFixedHeight(600);
    subList[2]->setFixedWidth(400);
    subList[2]->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    w.setCentralWidget(centralWidget);
    w.setFixedHeight(600);
    w.setFixedWidth(1200);

    w.show();

    return a.exec();
}


/*
 *QOrbitCameraController
 *  -  Tem que usar o botao direito do mouse para rodar.
 *  -  Talvez eu devesse adicionar um botao de reset view e/ou desativar o uso do botao esquerdo.
 *
 *
 *
 *
 *
 *
 *
 */



