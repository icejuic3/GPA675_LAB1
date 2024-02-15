
#include <QtWidgets/QApplication>

#include "GOLApp.h"
#include "GOLTeamK.h"


int main(int argc, char* argv[])
{
    QApplication application(argc, argv);
    
    GOLApp window;

    window.addEngine(new GOLTeamK);
    window.show();
    return application.exec();
}
