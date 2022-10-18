#include "mainwindow.h"
#include "video_player.h"

#include <QApplication>
#include <QtWidgets/QDesktopWidget>
#include <QSharedMemory>
#include <QMessageBox>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include <QtCore/QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSharedMemory sharedMemory;

    QCoreApplication::setApplicationName("FYI video player");
    QGuiApplication::setApplicationDisplayName(QCoreApplication::applicationName());
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);

    QCommandLineParser parser;

    parser.setApplicationDescription("Qt Video Widget Example");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("url", "The URL of video to open.");
    parser.process(a);

    VideoPlayer player;
    if (!parser.positionalArguments().isEmpty())
    {
        const QUrl url = QUrl::fromUserInput(parser.positionalArguments().constFirst(), QDir::currentPath(), QUrl::AssumeLocalFile);
        player.setUrl(url);
    }

    // https://stackoverflow.com/questions/34445164/qt5-preventing-another-instance-of-the-application-doesnt-work-anymore
    sharedMemory.setKey("fyi-memory-key");
    if (sharedMemory.create(1) == false)
    {
        QMessageBox::warning(NULL, "Info", "Another instance of the app is already running.");
        a.exit();
        return 0;
    }

    const QRect availableSpace = QApplication::desktop()->availableGeometry(&player);
    player.resize(availableSpace.width() * 0.5, availableSpace.height() / 3);
    player.show();

    return a.exec();
}
