#ifndef SHOWMOLECULE_H
#define SHOWMOLECULE_H

#include <QObject>
#include <Qt3DCore>
#include <Qt3DExtras>
#include <Qt3DRender>
#include <Qt3DExtras>
#include <QColor>

class ShowMolecule : public QObject
{
    Q_OBJECT

public:
    ShowMolecule();

    QString getMolName(){ return molName; }

    Qt3DExtras::Qt3DWindow *showMoleculeInitialization();


private:
    Qt3DExtras::Qt3DWindow *molWindow;
    Qt3DCore::QEntity * mol;

    //Molecule characterstics
    void readMol2Format(QString &fileName);
    QString molName;
    int nAtoms, nBonds;
    QList<QString> atomLabels;
    QList<QVector3D> atomCoordinates;
    QList<int> connectionsA;
    QList<int> connectionsB;

    //Shapes that appear on screen
    void createMolecule();
    qreal sphereRadius, cylinderRadius, coordinatesScaleFactor;
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
    QList<QColor> defaultColors;
    QList<QString> atomTypes;
    void setDefaultColor(int atomI);

    //Camera
    void createCamera();

    //Mouse clicker functions
    void createPicker();
    QList<bool> atomsListHighlighted;
    Qt3DRender::QObjectPicker *objectPicker;
    int atomPicked(QVector3D &worldInter);
    qreal radiusTolerance;

public slots:
    void loadMolecule(QString fileName);

    void processTouched(Qt3DRender::QPickEvent *event);

    void reescaleReceiving(qreal reescale);

signals:
    void atomWasSelected(QString selAtom);


};

#endif // SHOWMOLECULE_H


// run qmkae resets builds and correct some errors.
