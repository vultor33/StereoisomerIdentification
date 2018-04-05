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

    void setMolName(const QString &name);

private:
    Ui::MainWindow *ui;

public slots:
    void on_buttonReescale_clicked();
    void setSelAtom(QString selAtom);

signals:
    void reescaleClicked(qreal reescale);


};

#endif // MAINWINDOW_H
