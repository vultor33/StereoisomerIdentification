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

#include "myorbitcontroller.h"

ShowMolecule::ShowMolecule() :
    molWindow(nullptr),
    mol(nullptr),
    camController(nullptr),
    objectPicker(nullptr)
{
    player = 0;
    atomTypes << "Au" << "P" << "N" << "O" << "C" << "H";
    defaultColors << Qt::yellow << Qt::green << Qt::blue << Qt::red << Qt::gray << Qt::white;

    sphereRadius = 3;
    cylinderRadius = 0.5;
    coordinatesScaleFactor = 7.0e0;
    radiusTolerance = 2.0;
}

ShowMolecule::~ShowMolecule()
{
    delete [] objectPicker;
    delete [] mol;
    delete [] camController;
    delete [] molWindow;
}


Qt3DExtras::Qt3DWindow *ShowMolecule::showMoleculeInitialization(int player_in)
{
    player = player_in;

    molWindow = new Qt3DExtras::Qt3DWindow;

    mol = new Qt3DCore::QEntity;

    createCamera();

    createPicker();

    molWindow->setRootEntity(mol);

    return molWindow;

}

void ShowMolecule::loadMolecule(QString fileName)
{
    cleanMol();

    readMol2Format(fileName);
}

void ShowMolecule::readMol2Format(QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, fileName + " not found", file.errorString());
        return;
    }
    emit molNameDefined(fileName);
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

    createMolecule();

}

void ShowMolecule::createMolecule()
{
    for(int  i = 0; i < nAtoms; i++)
    {
        Qt3DExtras::QSphereMesh *sphereMeshI = new Qt3DExtras::QSphereMesh(mol);
        Qt3DCore::QTransform *sphereTransformI = new Qt3DCore::QTransform(mol);
        Qt3DExtras::QPhongMaterial *sphereMaterialI = new Qt3DExtras::QPhongMaterial(mol);
        createSphere(sphereMeshI,sphereTransformI,sphereMaterialI);
        sphereListMesh << sphereMeshI;
        sphereListTransform << sphereTransformI;
        sphereListMaterial << sphereMaterialI;
        atomsListHighlighted << false;
        setDefaultColor(i);
        sphereListTransform[i]->setTranslation(atomCoordinates[i]);

        if(player == 1)
            sphereListMesh[i]->setEnabled(false);
    }

    if(player == 1)
        return;

    for(int i = 0; i < nBonds; i++)
    {
        Qt3DExtras::QCylinderMesh *cylinderMeshI = new Qt3DExtras::QCylinderMesh(mol);
        Qt3DCore::QTransform *cylinderTransformI = new Qt3DCore::QTransform(mol);
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

void ShowMolecule::cleanMol()
{
    Qt3DCore::QNodeVector listChild =  mol->childNodes();
    for(int i = 3; i < listChild.size(); i++)
    {
        listChild[i]->deleteLater();
    }

    sphereListMaterial.clear();
    sphereListMesh.clear();
    sphereListTransform.clear();
    cylinderListMaterial.clear();
    cylinderListMesh.clear();
    cylinderListTransform.clear();
    atomsListHighlighted.clear();
    nAtomsHighlighted = 0;
    atomLabels.clear();
    atomCoordinates.clear();
    connectionsA.clear();
    connectionsB.clear();
    molName = "";
    nAtoms = 0;
    nBonds = 0;
}




void ShowMolecule::createCamera()
{
    Qt3DRender::QCamera *camera = molWindow->camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 0, 200.0f));
    camera->setViewCenter(QVector3D(0, 0, 0));
    camController = new MyOrbitController(mol);
    camController->setCamera(camera);
    camController->setLinearSpeed( 3000.0f );
    camController->setLookSpeed( 180.0f );

}

void ShowMolecule::setCameraCenter(QVector3D newCenter)
{
    camController->setCameraViewCenterToPos(coordinatesScaleFactor * newCenter);
}

void ShowMolecule::linkOtherCamera(Qt3DExtras::Qt3DWindow *window2)
{
    Qt3DRender::QCamera *camera2 = window2->camera();
    camController->setCamera2(camera2);
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

    connect(objectPicker, SIGNAL(clicked(Qt3DRender::QPickEvent*)), this, SLOT(processTouched(Qt3DRender::QPickEvent*)));

    mol->addComponent(objectPicker);

    if(player == 1)
        objectPicker->setEnabled(false);
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
        if((rApick.length()) < (sphereListMesh[i]->radius() + radiusTolerance))
        {
            if(atomsListHighlighted[i])
            {
                setDefaultColor(i);
                atomsListHighlighted[i] = false;
                nAtomsHighlighted--;
                sendPickMessage();
                return i;
            }
            for(int j = 0; j < atomsListHighlighted.size(); j++)
            {
                if(i == j)
                    continue;
                if(atomsListHighlighted[j])
                {
                    if(nAtomsHighlighted > 1)
                    {
                            setDefaultColor(j);
                            atomsListHighlighted[j] = false;
                            nAtomsHighlighted--;
                    }
                    if(sphereListMesh[i]->isEnabled())
                    {
                        sphereListMaterial[i]->setAmbient(Qt::black);
                        atomsListHighlighted[i] = true;
                        nAtomsHighlighted++;
                        sendPickMessage();
                    }
                    return i;
                }
            }
            if(sphereListMesh[i]->isEnabled())
            {
                sphereListMaterial[i]->setAmbient(Qt::black);
                atomsListHighlighted[i] = true;
                nAtomsHighlighted++;
                sendPickMessage();
            }
            return i;
        }
    }
    return -1;
}

void ShowMolecule::sendPickMessage()
{
    AtomsX atom0;
    bool first = true;
    atom0.label1 = "";
    atom0.label2 = "";

    for(int i = 0; i < atomsListHighlighted.size(); i++)
    {
        if(atomsListHighlighted[i] && first)
        {
            atom0.label1 = atomLabels[i];
            atom0.coord1 = atomCoordinates[i] / coordinatesScaleFactor;
            atom0.atomOrderNumber1 = i;
            first = false;
        }
        else if(atomsListHighlighted[i])
        {
            atom0.label2 = atomLabels[i];
            atom0.coord2 = atomCoordinates[i] / coordinatesScaleFactor;
            atom0.atomOrderNumber2 = i;
        }
    }
    emit atomWasSelected(atom0);
}

void ShowMolecule::setSphereEnabled(int i, bool enabled)
{
    sphereListMesh[i]->setEnabled(enabled);
}







