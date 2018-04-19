#include "mainwindow.h"

#include <QApplication>
#include <Qt3DExtras>
#include <QWidget>
#include <QMdiArea>
#include <QLCDNumber>
#include <QMainWindow>
#include <QMdiSubWindow>
#include <QObjectPicker>
#include <Qt3DRender>
#include <QCamera>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QMessageBox>
#include <sstream>
#include <fstream>
#include <string>
#include <QViewport>
#include <QObject>
#include <QFileDialog>

#include "complexidentificationmanager.h"
#include "showmolecule.h"
#include "custommolecule.h"

// MEU CLIENTE QUER CONFIGURACAO ABSOLUTA. - vou avisar que o mol2 correto e necessario e confiar nele.
// MEU CLIENTE GOSTARIA QUE FUNCIONASSE EM METALLOCAGES TAMBEM.

// a camera esta lenta aqui verificar o q e depois

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /* Complex identfication */
    QMainWindow w;
    ComplexIdentificationManager cpm_;
    cpm_.startComplexIdentification(w);
    w.show();

    CustomMolecule customMol_;
    Qt3DExtras::Qt3DWindow *view = customMol_.showMoleculeInitialization();
    customMol_.loadMolecule("C:\\Users\\frederico\\source\\repos\\QtProjects\\StereoisomerIdentification\\t4-isomer.mol2");
    view->show();


    return a.exec();
}


/*
 *QOrbitCameraController
 *  -  Tem que usar o botao direito do mouse para rodar.
 *  -  Talvez eu devesse adicionar um botao de reset view e/ou desativar o uso do botao esquerdo.
 *
 *PERIGOS
 * Warning:
 * No shader program found for DNA
 * - acho que acontece pq meu void ShowMolecule::cleanMol()
 *   usa deleteLater para limpar a memoria.
 *
 *
 */



