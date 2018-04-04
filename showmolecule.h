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

    void createMolecule(QString &fileName);

    Qt3DCore::QEntity *getMolecule();


private:
    Qt3DCore::QEntity * mol;

    //molecule characteristics
    void readMol2Format(QString &fileName);
    QString molName;
    int nAtoms, nBonds;
    QList<QString> atomLabels;
    QList<QVector3D> atomCoordinates;
    QList<int> connectionsA;
    QList<int> connectionsB;

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
    void createPicker();
    QList<bool> atomsListHighlighted;
    Qt3DRender::QObjectPicker *objectPicker;
    int atomPicked(QVector3D &worldInter);

    //emitir um sinal com atompicked e o numero que foi selecionado



public slots:
    void processTouched(Qt3DRender::QPickEvent *event);

};

#endif // SHOWMOLECULE_H


// run qmkae resets builds and correct some errors.
