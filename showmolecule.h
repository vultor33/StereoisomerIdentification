#ifndef SHOWMOLECULE_H
#define SHOWMOLECULE_H

#include <Qt3DCore>
#include <Qt3DExtras>

class ShowMolecule
{
public:
    ShowMolecule();

    void createMolecule();

    Qt3DCore::QEntity *getMolecule();

    void moveMolecule(qreal x);



private:
    Qt3DCore::QEntity * mol;

    Qt3DCore::QTransform *sphereTransform;

};

#endif // SHOWMOLECULE_H
