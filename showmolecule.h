#ifndef SHOWMOLECULE_H
#define SHOWMOLECULE_H

#include <QObject>
#include <Qt3DCore>
#include <Qt3DExtras>
#include <Qt3DRender>
#include <QDebug>

class ShowMolecule : QObject
{
    Q_OBJECT

public:
    ShowMolecule();

    void createMolecule();

    void createPicker();

    Qt3DCore::QEntity *getMolecule();

    void moveMolecule(qreal x);


    void repositionAtoms();


private:
    Qt3DCore::QEntity * mol;

    // Solids definitions
    QList<Qt3DExtras::QSphereMesh*> sphereListMesh;
    QList<Qt3DCore::QTransform*> sphereListTransform;
    QList<Qt3DExtras::QPhongMaterial*> sphereListMaterial;
    void createSphere(
            Qt3DExtras::QSphereMesh *sphereMeshI,
            Qt3DCore::QTransform *sphereTransformI,
            Qt3DExtras::QPhongMaterial *sphereMaterialI);
    QList<Qt3DExtras::QCylinderMesh*> cylinderListMesh;
    QList<Qt3DCore::QTransform*> cylinderListTransform;
    QList<Qt3DExtras::QPhongMaterial*> cylinderListMaterial;
    void createCylinder(
            Qt3DExtras::QCylinderMesh *cylinderMeshI,
            Qt3DCore::QTransform *cylinderTransformI,
            Qt3DExtras::QPhongMaterial *cylindermaterialI);
    void atomsConnections(int atomA, int atomB, int bondI);

    // Picker functions
    QList<bool> atomsListHighlighted;
    Qt3DRender::QObjectPicker *objectPicker;
    int atomPicked(QVector3D &worldInter);






public slots:
    void processTouched(Qt3DRender::QPickEvent *event);

    void empty(){}

signals:
    void testaSinal(Qt3DRender::QPickEvent*);

};

#endif // SHOWMOLECULE_H


// run qmkae resets builds and correct some errors.
