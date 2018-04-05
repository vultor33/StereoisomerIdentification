#include "showmolecule.h"

#include <QObject>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DCore/QAspectEngine>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DRender>
#include <Qt3DRender/QRenderAspect>
#include <QObjectPicker>
#include <QPickEvent>
#include <QQuaternion>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QComponentVector>

ShowMolecule::ShowMolecule() :
    molWindow(nullptr),
    mol(nullptr),
    objectPicker(nullptr)
{
    atomTypes << "Au" << "P" << "N" << "O";
    defaultColors << Qt::yellow << Qt::green << Qt::blue << Qt::red;

    sphereRadius = 3;
    cylinderRadius = 0.5;
    coordinatesScaleFactor = 8.0e0;

}

Qt3DExtras::Qt3DWindow *ShowMolecule::loadMolecule(QString &fileName)
{
    molWindow = new Qt3DExtras::Qt3DWindow;

    readMol2Format(fileName);

    createMolecule();

    createCamera();

    createPicker();

    molWindow->setRootEntity(mol);

    return molWindow;

}



void ShowMolecule::readMol2Format(QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }
    QTextStream in(&file);
    while(!in.atEnd())
    {
        QString line = in.readLine();
        QTextStream convert(&line);
        QString flagRead;
        convert >> flagRead;
        if(flagRead == "@<TRIPOS>MOLECULE")
        {
            QString line2 = in.readLine();
            QTextStream convert2(&line2);
            convert2 >> molName;
            QString line3 = in.readLine();
            QTextStream convert3(&line3);
            convert3 >> nAtoms >> nBonds;
        }
        else if(flagRead == "@<TRIPOS>ATOM")
        {
            for(int i = 0; i < nAtoms; i++)
            {
                QString dum1, dum2, label;
                qreal x,y,z;
                QString lineI = in.readLine();
                QTextStream convertI(&lineI);
                convertI >> dum1 >> dum2 >> x >> y >> z >> label;
                x *= coordinatesScaleFactor;
                y *= coordinatesScaleFactor;
                z *= coordinatesScaleFactor;
                QVector3D auxVecPositions = QVector3D(x,y,z);
                atomCoordinates << auxVecPositions;
                atomLabels << label;
            }
        }
        else if(flagRead == "@<TRIPOS>BOND")
        {
            for(int i = 0; i < nBonds; i++)
            {
                QString dum1, dum2;
                int atomB1, atomB2;
                QString lineI = in.readLine();
                QTextStream convertI(&lineI);
                convertI >> dum1 >> atomB1 >> atomB2 >> dum2;
                connectionsA << (atomB1-1);
                connectionsB << (atomB2-1);
            }
        }
    }

    /* Reding check
    qDebug() << "ATOMS";
    for(int i = 0; i < nAtoms; i++)
    {
        qDebug() << atomLabels[i] << "  "
                 << xCoordinates[i] << "  "
                 << yCoordinates[i] << "  "
                 << zCoordinates[i] << "  ";
    }
    qDebug() << "BONDS";
    for(int i = 0; i < nBonds; i++)
    {
        qDebug() << atomConnections1[i]
                 << atomConnections2[i];
    }
    */

    file.close();
}

void ShowMolecule::createMolecule()
{
    mol = new Qt3DCore::QEntity;

    for(int  i = 0; i < nAtoms; i++)
    {
        Qt3DExtras::QSphereMesh *sphereMeshI = new Qt3DExtras::QSphereMesh;
        Qt3DCore::QTransform *sphereTransformI = new Qt3DCore::QTransform;
        Qt3DExtras::QPhongMaterial *sphereMaterialI = new Qt3DExtras::QPhongMaterial(mol);
        createSphere(sphereMeshI,sphereTransformI,sphereMaterialI);
        sphereListMesh << sphereMeshI;
        sphereListTransform << sphereTransformI;
        sphereListMaterial << sphereMaterialI;
        atomsListHighlighted << false;
        setDefaultColor(i);
        sphereListTransform[i]->setTranslation(atomCoordinates[i]);
    }

    for(int i = 0; i < nBonds; i++)
    {
        Qt3DExtras::QCylinderMesh *cylinderMeshI = new Qt3DExtras::QCylinderMesh;
        Qt3DCore::QTransform *cylinderTransformI = new Qt3DCore::QTransform;
        Qt3DExtras::QPhongMaterial *cylinderMaterialI = new Qt3DExtras::QPhongMaterial(mol);
        createCylinder(cylinderMeshI,cylinderTransformI,cylinderMaterialI);
        cylinderListMesh << cylinderMeshI;
        cylinderListTransform << cylinderTransformI;
        cylinderListMaterial << cylinderMaterialI;

        atomsConnections(connectionsA[i], connectionsB[i], i);
    }
}

void ShowMolecule::createSphere(
        Qt3DExtras::QSphereMesh *sphereMeshI,
        Qt3DCore::QTransform *sphereTransformI,
        Qt3DExtras::QPhongMaterial *sphereMaterialI)
{
    Qt3DCore::QEntity *sphereEntityI = new Qt3DCore::QEntity(mol);
    sphereMeshI->setRadius(3);
    sphereTransformI->setTranslation(QVector3D(0,0,0));
    sphereMaterialI->setAmbient(Qt::green);
    sphereEntityI->addComponent(sphereMeshI);
    sphereEntityI->addComponent(sphereTransformI);
    sphereEntityI->addComponent(sphereMaterialI);
}

void ShowMolecule::createCylinder(
        Qt3DExtras::QCylinderMesh *cylinderMeshI,
        Qt3DCore::QTransform *cylinderTransformI,
        Qt3DExtras::QPhongMaterial *cylinderMaterialI)
{
    Qt3DCore::QEntity *cylinderEntityI = new Qt3DCore::QEntity(mol);
    cylinderMeshI->setRadius(cylinderRadius);
    cylinderMeshI->setLength(1);
    cylinderTransformI->setTranslation(QVector3D(0,0,0));
    cylinderMaterialI->setAmbient(Qt::gray);
    cylinderEntityI->addComponent(cylinderMeshI);
    cylinderEntityI->addComponent(cylinderTransformI);
    cylinderEntityI->addComponent(cylinderMaterialI);
}

void ShowMolecule::atomsConnections(int atomA, int atomB, int bondI)
{
    QVector3D rAB = sphereListTransform[atomA]->translation()-sphereListTransform[atomB]->translation();
    cylinderListTransform[bondI]->setRotation(QQuaternion::rotationTo(QVector3D(0,1,0), rAB));
    cylinderListMesh[bondI]->setLength(rAB.length());
    cylinderListTransform[bondI]->setTranslation(QVector3D(
                                                 sphereListTransform[atomB]->translation()+rAB/2.0e0));
}

void ShowMolecule::setDefaultColor(int atomI)
{
    for(int i = 0; i <atomTypes.size(); i++)
    {
        if(atomLabels[atomI] == atomTypes[i])
        {
            sphereListMaterial[atomI]->setAmbient(defaultColors[i]);
            return;
        }
    }
    sphereListMaterial[atomI]->setAmbient(Qt::gray);
}



void ShowMolecule::createCamera()
{
    Qt3DRender::QCamera *camera = molWindow->camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 0, 80.0f));
    camera->setViewCenter(QVector3D(0, 0, 0));
    Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(mol);
    camController->setLinearSpeed( 50.0f );
    camController->setLookSpeed( 180.0f );
    camController->setCamera(camera);
}



void ShowMolecule::createPicker()
{
    objectPicker = new Qt3DRender::QObjectPicker(mol);
    objectPicker->setHoverEnabled(false);
    objectPicker->setDragEnabled(false);
    Qt3DRender::QRenderSettings *renderSettingsComponent = new Qt3DRender::QRenderSettings(mol);
    Qt3DExtras::QForwardRenderer *forwardRenderer = molWindow->defaultFrameGraph();
    renderSettingsComponent->setActiveFrameGraph(forwardRenderer);
    Qt3DRender::QPickingSettings *pickingSettings = renderSettingsComponent->pickingSettings();
    pickingSettings->setPickResultMode(Qt3DRender::QPickingSettings::NearestPick);
    pickingSettings->setPickMethod(Qt3DRender::QPickingSettings::TrianglePicking);

    connect(
               objectPicker,
               SIGNAL(clicked(Qt3DRender::QPickEvent*)),
               this,
               SLOT(processTouched(Qt3DRender::QPickEvent*)));

    mol->addComponent(objectPicker);
}



// SLOTS
void ShowMolecule::processTouched(Qt3DRender::QPickEvent *event)
{
    QVector3D inter = event->localIntersection();

    atomPicked(inter);

    event->setAccepted(true);
}

int ShowMolecule::atomPicked(QVector3D &worldInter)
{
    for(int i = 0; i < sphereListTransform.size(); i++)
    {
        QVector3D rApick = worldInter - sphereListTransform[i]->translation();
        if((rApick.length()) < (sphereListMesh[i]->radius() + 5.0e0))
        {
            //selects just one
            for(int j = 0; j < atomsListHighlighted.size(); j++)
            {
                if(atomsListHighlighted[j])
                {
                    if(i == j)
                    {
                        setDefaultColor(j);
                        atomsListHighlighted[j] = false;
                        emit atomWasSelected(" ");
                        return i;
                    }
                    else
                    {
                        setDefaultColor(j);
                        atomsListHighlighted[j] = false;
                        sphereListMaterial[i]->setAmbient(Qt::black);
                        atomsListHighlighted[i] = true;
                        emit atomWasSelected(QString::number(i));
                        return i;
                    }
                }
            }
            sphereListMaterial[i]->setAmbient(Qt::black);
            atomsListHighlighted[i] = true;
            emit atomWasSelected(QString::number(i));
            return i;
        }
    }
    return -1;
}


void ShowMolecule::reescaleReceiving(qreal reescale)
{
    for(int i = 0; i < nAtoms; i++)
        sphereListMesh[i]->setRadius(reescale);

}

