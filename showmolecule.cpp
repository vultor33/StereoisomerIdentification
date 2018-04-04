#include "showmolecule.h"

#include <QObject>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DCore/QAspectEngine>
#include <QQuaternion>

#include <Qt3DRender/QRenderAspect>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DRender>
#include <QObjectPicker>
#include <QPickEvent>


ShowMolecule::ShowMolecule() :
    mol(nullptr),
    objectPicker(nullptr)
{

}


void ShowMolecule::createMolecule()
{
    mol = new Qt3DCore::QEntity;

    for(size_t  i =0; i < 3; i++)
    {
        Qt3DExtras::QSphereMesh *sphereMeshI = new Qt3DExtras::QSphereMesh;
        Qt3DCore::QTransform *sphereTransformI = new Qt3DCore::QTransform;
        Qt3DExtras::QPhongMaterial *sphereMaterialI = new Qt3DExtras::QPhongMaterial(mol);
        createSphere(sphereMeshI,sphereTransformI,sphereMaterialI);
        sphereListMesh << sphereMeshI;
        sphereListTransform << sphereTransformI;
        sphereListMaterial << sphereMaterialI;

        Qt3DExtras::QCylinderMesh *cylinderMeshI = new Qt3DExtras::QCylinderMesh;
        Qt3DCore::QTransform *cylinderTransformI = new Qt3DCore::QTransform;
        Qt3DExtras::QPhongMaterial *cylinderMaterialI = new Qt3DExtras::QPhongMaterial(mol);
        createCylinder(cylinderMeshI,cylinderTransformI,cylinderMaterialI);
        cylinderListMesh << cylinderMeshI;
        cylinderListTransform << cylinderTransformI;
        cylinderListMaterial << cylinderMaterialI;
    }
    sphereListTransform[0]->setTranslation(QVector3D(-15,5,12));
    sphereListTransform[1]->setTranslation(QVector3D(15,5,-4));
    sphereListTransform[2]->setTranslation(QVector3D(0,1,-20));

    sphereListMesh[0]->setRadius(9);
    sphereListMaterial[1]->setAmbient(Qt::green);

    cylinderListTransform[0]->setTranslation(QVector3D(0,0,-15));
    cylinderListTransform[1]->setTranslation(QVector3D(0,0,500));

    atomsConnections(0,1,0);
    atomsConnections(0,2,2);

    cylinderListMaterial[0]->setAmbient(Qt::blue);


}

void ShowMolecule::createSphere(
        Qt3DExtras::QSphereMesh *sphereMeshI,
        Qt3DCore::QTransform *sphereTransformI,
        Qt3DExtras::QPhongMaterial *sphereMaterialI)
{
    Qt3DCore::QEntity *sphereEntityI = new Qt3DCore::QEntity(mol);
    sphereMeshI->setRadius(3);
    sphereTransformI->setTranslation(QVector3D(0,0,0));
    sphereMaterialI->setAmbient(Qt::black);
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
    cylinderMeshI->setRadius(1);
    cylinderMeshI->setLength(10);
    cylinderTransformI->setTranslation(QVector3D(0,0,0));
    cylinderMaterialI->setAmbient(Qt::black);
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




void ShowMolecule::moveMolecule(qreal x)
{
    //sphereTransform->setTranslation(QVector3D(20,x,0));
}

Qt3DCore::QEntity *ShowMolecule::getMolecule()
{
    return mol;
}

void ShowMolecule::createPicker()
{
    objectPicker = new Qt3DRender::QObjectPicker(mol);
    objectPicker->setHoverEnabled(false);
    objectPicker->setDragEnabled(false);
    connect(
               objectPicker,
               SIGNAL(clicked(Qt3DRender::QPickEvent*)),
               //this,
                //SIGNAL(testaSinal(Qt3DRender::QPickEvent*)),
                this,
                SLOT(processTouched(Qt3DRender::QPickEvent*)));
                //SLOT(empty()));
    mol->addComponent(objectPicker);
}



// SLOTS
/* */
void ShowMolecule::processTouched(Qt3DRender::QPickEvent *event)
{
    //Ignore pick events if the entity is disabled
//    if (!isEnabled()) {
//        event->setAccepted(false);
//        return;
//    }

    //inform that the tile has been touched
    //material2->setAmbient(Qt::blue);
    qDebug() << "tile touched";
    event->setAccepted(true);
}


