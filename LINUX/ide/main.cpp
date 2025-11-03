#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Configuración de la aplicación
    app.setApplicationName("IDE Agricultura");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("Universidad");
    
    MainWindow window;
    window.show();
    
    return app.exec();
}
