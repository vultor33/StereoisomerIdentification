#include "showmolecule.h"

#include <QObject>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DCore/QAspectEngine>

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
    sphereTransform(nullptr),
    material2(nullptr),
    objectPicker(nullptr)
{

}


void ShowMolecule::createMolecule()
{
    // Root entity
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity;

    // Material
    Qt3DRender::QMaterial *material = new Qt3DExtras::QPhongMaterial(rootEntity);

    // Torus
    /*
    Qt3DCore::QEntity *torusEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DExtras::QTorusMesh *torusMesh = new Qt3DExtras::QTorusMesh;
    torusMesh->setRadius(10);
    torusMesh->setMinorRadius(1);
    torusMesh->setRings(100);
    torusMesh->setSlices(20);

    Qt3DCore::QTransform *torusTransform = new Qt3DCore::QTransform;
    torusTransform->setScale3D(QVector3D(1.5, 1, 0.5));
    torusTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), 45.0f));

    torusEntity->addComponent(torusMesh);
    torusEntity->addComponent(torusTransform);
    torusEntity->addComponent(material);
*/

    // Cyllineter
    Qt3DCore::QEntity *cyllinderEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DExtras::QCylinderMesh *cyllinderMesh = new Qt3DExtras::QCylinderMesh;
    cyllinderMesh->setRadius(0.5);
    cyllinderMesh->setLength(7);
    Qt3DCore::QTransform *cylinderTransform = new Qt3DCore::QTransform;
    QVector3D qVec = QVector3D(2,3,4);
    cylinderTransform->setTranslation(qVec);
    cylinderTransform->setRotationX(40);
    cylinderTransform->setRotationY(20);
    Qt3DExtras::QPhongMaterial *material3 = new Qt3DExtras::QPhongMaterial(rootEntity);
    material3->setAmbient(Qt::green);

    cyllinderEntity->addComponent(cyllinderMesh);
    cyllinderEntity->addComponent(cylinderTransform);
    cyllinderEntity->addComponent(material3);


    // Sphere
    Qt3DCore::QEntity *sphereEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DExtras::QSphereMesh *sphereMesh = new Qt3DExtras::QSphereMesh;
    sphereMesh->setRadius(3);
    sphereTransform = new Qt3DCore::QTransform;
    sphereTransform->setTranslation(QVector3D(20,2,0));
    material2 = new Qt3DExtras::QPhongMaterial(rootEntity);
    material2->setAmbient(Qt::red);

    sphereEntity->addComponent(sphereMesh);
    sphereEntity->addComponent(sphereTransform);
    sphereEntity->addComponent(material2);

    mol = rootEntity;


}

void ShowMolecule::moveMolecule(qreal x)
{
    sphereTransform->setTranslation(QVector3D(20,x,0));
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
    material2->setAmbient(Qt::blue);
    qDebug() << "tile touched";
    event->setAccepted(true);
}


