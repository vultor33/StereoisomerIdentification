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

#include "showmolecule.h"

class Counter : public QObject
{
    Q_OBJECT

public:
    Counter() { m_value = 0; }

    int value() const { return m_value; }

public slots:
    void setValue(int value){ m_value = value;}

signals:
    void valueChanged(int newValue)
    {
        if (newValue != m_value) {
            m_value = newValue;
            emit valueChanged(newValue);
        }
    }

private:
    int m_value;
};





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
    //

    QWidget *molBox = QWidget::createWindowContainer(&view);

    QMdiArea *centralWidget = new QMdiArea;
    QLCDNumber *lcd = new QLCDNumber;
    lcd->display(1337);
    lcd->setMinimumSize(250, 100);
    centralWidget->addSubWindow(lcd);
    centralWidget->addSubWindow(molBox);
    QList<QMdiSubWindow *> subList = centralWidget->subWindowList();
    subList[1]->setFixedHeight(200);
    subList[1]->setFixedWidth(200);
    subList[1]->move(QPoint(100,100));
    subList[1]->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);



    //Input
//    addComponent(objectPicker);




    w.setCentralWidget(centralWidget);
    //w.resize(800, 600);
    view.show();
    w.show();

    mol_.moveMolecule(10);
    mol_.createPicker();

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



