#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "showmolecule.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void connectWithMol(ShowMolecule *mol_, ShowMolecule *mol2_);


private:
    Ui::MainWindow *ui;

    AtomsX selectedAtomsLeft;


public slots:
    void setSelAtom(AtomsX atom0);
    void setMolName(QString fileName);
    void on_buttonLoadMolecule_clicked();
    void on_buttonDefineMetal_clicked();
    void on_buttonDefineMono_clicked();
    void on_buttonDefineBi_clicked();


signals:
    void loadMoleculeClicked(QString fileName);
    void cameraCentralize(QVector3D newCenter);
    void enableDisableAtom(int i, bool enabled);



};

#endif // MAINWINDOW_H
