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

    ShowMolecule mol_;
    QString fileName = "C:\\Users\\basta\\Documents\\Visual Studio 2015\\Projects\\Qt-Projects\\visual-3\\t4-isomer.mol2";
    mol_.createMolecule(fileName);
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
//    view.show();
//    return a.exec();

    QWidget *molBox = QWidget::createWindowContainer(&view);

    QMdiArea *centralWidget = new QMdiArea;
    QLCDNumber *lcd = new QLCDNumber;
    lcd->display(1337);
    lcd->setMinimumSize(250, 100);
    centralWidget->addSubWindow(lcd);
    centralWidget->addSubWindow(molBox);
    QList<QMdiSubWindow *> subList = centralWidget->subWindowList();
    subList[1]->setFixedHeight(600);
    subList[1]->setFixedWidth(600);
    //subList[1]->move(QPoint(100,100));
    subList[1]->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);


    Qt3DRender::QRenderSettings *renderSettingsComponent = new Qt3DRender::QRenderSettings(scene);
    Qt3DExtras::QForwardRenderer *forwardRenderer = view.defaultFrameGraph();
    renderSettingsComponent->setActiveFrameGraph(forwardRenderer);
    Qt3DRender::QPickingSettings *pickingSettings = renderSettingsComponent->pickingSettings();
    pickingSettings->setPickResultMode(Qt3DRender::QPickingSettings::NearestPick);
    pickingSettings->setPickMethod(Qt3DRender::QPickingSettings::TrianglePicking);

    scene->addComponent(renderSettingsComponent);
    qDebug() << "components:  " << scene->components();




    w.setCentralWidget(centralWidget);
    //w.resize(800, 600);
    view.show();
    w.show();

//    mol_.readMol2Format(fileName);

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



