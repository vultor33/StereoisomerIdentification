#include "mainwindow.h"

#include <QApplication>
#include <Qt3DExtras>
#include <QWidget>
#include <QMdiArea>
#include <QLCDNumber>
#include <QMainWindow>

#include "showmolecule.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow w;
    //w.show();

    ShowMolecule mol_;
    mol_.createMolecule();
    mol_.moveMolecule(60);
    Qt3DExtras::Qt3DWindow view;
    Qt3DCore::QEntity *scene = mol_.getMolecule();
    Qt3DRender::QCamera *camera = view.camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 0, 80.0f));
    camera->setViewCenter(QVector3D(0, 0, 0));
    Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(scene);
    camController->setLinearSpeed( 50.0f );
    camController->setLookSpeed( 180.0f );
    camController->setCamera(camera);
    view.setRootEntity(scene);
    view.show();
    QWidget *molBox = QWidget::createWindowContainer(&view);

    QMdiArea *centralWidget = new QMdiArea;
    QLCDNumber *lcd = new QLCDNumber;
    lcd->display(1337);
    lcd->setMinimumSize(250, 100);
    centralWidget->addSubWindow(lcd);
    centralWidget->addSubWindow(molBox);
    w.setCentralWidget(centralWidget);
    //w.resize(800, 600);
    w.show();

    mol_.moveMolecule(10);

    return a.exec();
}


/*
 *QOrbitCameraController
 *  -  Tem que usar o botao direito do mouse para rodar.
 *  -  Talvez eu devesse adicionar um botao de reset view e/ou desativar o uso do botao direito.
 *
 *
 *
 *
 *
 *
 *
 */



