#include "mainwindow.h"

#include <QApplication>
#include <QSharedMemory>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSharedMemory sharedMemory;

    // https://stackoverflow.com/questions/34445164/qt5-preventing-another-instance-of-the-application-doesnt-work-anymore
    sharedMemory.setKey("fyi-memory-key");
    if (sharedMemory.create(1) == false)
    {
        QMessageBox::warning(NULL, "Info", "Another instance of the app is already running.");
        a.exit();
        return 0;
    }

    MainWindow w;
    w.show();
    return a.exec();
}
