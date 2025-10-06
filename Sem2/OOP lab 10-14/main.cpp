#include <QtWidgets/QApplication>
#include <QLabel>
#include "ProductGUI.h"
#include "CosGUI.h"
#include <iostream>
#include "teste.h"

int main(int argc, char* argv[])
{
    Tests t;
    t.testDomain();
    t.testMap();
    t.testMap2();
    t.testReadAllFromFile();
    t.testRepoCos();
    t.testRepoProduse();
    t.testService();
    t.testServiceCos();
    t.testUndo();
    t.testValidator();
    t.testWriteToFile();
    {
        QApplication a(argc, argv);
        RepoFileProduse repo("produse.txt");
        RepoCos rcos;
        ServiceProd service(repo, rcos);
        ProductGUI gui(service);
        //CosGUI gui2(service);

        gui.setWindowTitle("Magazin");
        gui.show();
        /*gui2.setWindowTitle("Cos");
        gui2.show();*/
        return QApplication::exec();
    }
}
