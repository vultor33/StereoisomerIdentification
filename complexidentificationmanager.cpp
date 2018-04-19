#include "complexidentificationmanager.h"

#include <QMainWindow>
#include <Qt3DCore>
#include <Qt3DExtras>
#include <QWidget>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QList>

#include "showmolecule.h"
#include "mainwindow.h"

ComplexIdentificationManager::ComplexIdentificationManager(){}

void ComplexIdentificationManager::startComplexIdentification(QMainWindow &w)
{
    w.setWindowTitle("Complex Identification");
    QMdiArea *centralWidget = new QMdiArea;

    //molecule
    Qt3DExtras::Qt3DWindow *view = mol_.showMoleculeInitialization();
    QWidget *molBox = QWidget::createWindowContainer(view);

    //molecule2
    Qt3DExtras::Qt3DWindow *view2 = mol2_.showMoleculeInitialization(1);
    QWidget *molBox2 = QWidget::createWindowContainer(view2);


    mol_.linkOtherCamera(view2);
    mol2_.linkOtherCamera(view);

    // conectar as duas cameras?

    //interface
    interface.setMolName(mol_.getMolName());
    //interface.setSelAtom("");
    interface.connectWithMol(&mol_, &mol2_);

    centralWidget->addSubWindow(molBox);
    centralWidget->addSubWindow(&interface);
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

}

