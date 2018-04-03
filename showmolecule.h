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



private:
    Qt3DCore::QEntity * mol;

    Qt3DCore::QTransform *sphereTransform;
    Qt3DExtras::QPhongMaterial *material2;

    Qt3DRender::QObjectPicker *objectPicker;

public slots:
    void processTouched(Qt3DRender::QPickEvent *event);

    void empty(){}

signals:
    void testaSinal(Qt3DRender::QPickEvent*);

};

#endif // SHOWMOLECULE_H


// run qmkae resets builds and correct some errors.
