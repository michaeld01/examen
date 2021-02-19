#include "imc.h"

#include <QApplication>
#include <QTranslator>
#include <QInputDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator T;
    QStringList langs;
    langs << "Español" <<"Italiano";
    const QString lang = QInputDialog::getItem(NULL,"Languaje", "Select a languaje", langs);
    if (lang == "Italiano"){
        T.load(":/italiano.qm");
    }
    if(lang != "Español"){
        a.installTranslator(&T);
    }
    a.setStyle("fusion");
    IMC w;
    w.show();
    return a.exec();
}
