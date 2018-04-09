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

    void connectWithMol(ShowMolecule *mol_);


private:
    Ui::MainWindow *ui;

public slots:
    void on_buttonLoadMolecule_clicked();
    void setSelAtom(AtomX atom0);
    void setMolName(QString fileName);

signals:
    void loadMoleculeClicked(QString fileName);



};

#endif // MAINWINDOW_H
