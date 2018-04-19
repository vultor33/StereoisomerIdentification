#ifndef SHOWMOLECULE_H
#define SHOWMOLECULE_H

#include <QObject>
#include <Qt3DCore>
#include <Qt3DExtras>
#include <Qt3DRender>
#include <Qt3DExtras>
#include <QColor>

#include "myorbitcontroller.h"

struct AtomsX
{
    int atomOrderNumber1;
    QString label1;
    QVector3D coord1;
    int atomOrderNumber2;
    QString label2;
    QVector3D coord2;
};

class ShowMolecule : public QObject
{
    Q_OBJECT

public:
    ShowMolecule();

    ~ShowMolecule();

    QString getMolName(){ return molName; }

    Qt3DExtras::Qt3DWindow *showMoleculeInitialization(int player_in = 0);

    void linkOtherCamera(Qt3DExtras::Qt3DWindow *molWindow2);

protected:
    QList<Qt3DExtras::QSphereMesh*> sphereListMesh;
    QList<Qt3DCore::QTransform*> sphereListTransform;
    QList<Qt3DExtras::QPhongMaterial*> sphereListMaterial;
    QList<Qt3DExtras::QCylinderMesh*> cylinderListMesh;
    QList<Qt3DCore::QTransform*> cylinderListTransform;
    QList<Qt3DExtras::QPhongMaterial*> cylinderListMaterial;

private:
    int player;
    Qt3DExtras::Qt3DWindow *molWindow;
    Qt3DCore::QEntity *mol;

    //default mol properties
    qreal sphereRadius, cylinderRadius, coordinatesScaleFactor;
    QList<QColor> defaultColors;
    QList<QString> atomTypes;

    //Molecule characterstics
    int nAtoms, nBonds;
    QString molName;
    QList<QString> atomLabels;
    QList<QVector3D> atomCoordinates;
    QList<int> connectionsA;
    QList<int> connectionsB;
    void readMol2Format(QString &fileName);
    void cleanMol();

    //Shapes that appear on screen
    void createMolecule();
    void createSphere(
            Qt3DExtras::QSphereMesh *sphereMeshI,
            Qt3DCore::QTransform *sphereTransformI,
            Qt3DExtras::QPhongMaterial *sphereMaterialI);
    void createCylinder(
            Qt3DExtras::QCylinderMesh *cylinderMeshI,
            Qt3DCore::QTransform *cylinderTransformI,
            Qt3DExtras::QPhongMaterial *cylindermaterialI);
    void atomsConnections(int atomA, int atomB, int bondI);
    void setDefaultColor(int atomI);

    //Camera
    void createCamera();
    MyOrbitController *camController;


    //Mouse clicker functions
    int nAtomsHighlighted;
    QList<bool> atomsListHighlighted;
    Qt3DRender::QObjectPicker *objectPicker;
    qreal radiusTolerance;
    void createPicker();
    int atomPicked(QVector3D &worldInter);
    void sendPickMessage();

public slots:
    void loadMolecule(QString fileName);
    void processTouched(Qt3DRender::QPickEvent *event);
    void setCameraCenter(QVector3D newCenter);
    void setSphereEnabled(int i, bool enabled);


signals:
    void atomWasSelected(AtomsX);
    void molNameDefined(QString molName);

};

#endif // SHOWMOLECULE_H


// run qmkae resets builds and correct some errors.
