#ifndef COMPLEXIDENTIFICATIONMANAGER_H
#define COMPLEXIDENTIFICATIONMANAGER_H

#include <QMainWindow>
#include <QMainWindow>
#include <Qt3DCore>
#include <Qt3DExtras>
#include <QWidget>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QList>

#include "showmolecule.h"
#include "mainwindow.h"

class ComplexIdentificationManager
{
public:
    ComplexIdentificationManager();

    void startComplexIdentification(QMainWindow &w);

private:
    ShowMolecule mol_,mol2_;
    MainWindow interface;

};

#endif // COMPLEXIDENTIFICATIONMANAGER_H
