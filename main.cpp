#include "mainwindow.h"

#include <QApplication>
#include <QSharedMemory>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSharedMemory sharedMemory;

    QCoreApplication::setApplicationName("FYI video player");
    QGuiApplication::setApplicationDisplayName(QCoreApplication::applicationName());
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);

    // https://stackoverflow.com/questions/34445164/qt5-preventing-another-instance-of-the-application-doesnt-work-anymore
    sharedMemory.setKey("fyi-memory-key");
    if (sharedMemory.create(1) == false)
    {
        QMessageBox::warning(NULL, "Info", "Another instance of the app is already running.");
        a.exit();
        return 0;
    }

    MainWindow w;
    w.resize(800, 600);
    w.show();
    return a.exec();
}
