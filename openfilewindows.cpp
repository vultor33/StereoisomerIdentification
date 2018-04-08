#include "openfilewindows.h"

#include <QFileDialog>
#include <QWidget>
#include <QString>
#include <QApplication>

OpenFileWindows::OpenFileWindows(){}

QString OpenFileWindows::loadMoleculeWindow()
{
    QString fileName =  QFileDialog::getOpenFileName(
          this,
          "Load molecule",
          QCoreApplication::applicationDirPath(),
          "mol2 - Sybil Mol2 format - (*.mol2)");
    return fileName;
}
