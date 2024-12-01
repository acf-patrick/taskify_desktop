#include <QDir>
#include <QFile>
#include <QProcess>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

#ifdef QT_DEBUG
    const auto taskifyExecutable = QStringLiteral(TASKIFY_EXECUTABLE);
#else
    const auto workingDir = QCoreApplication::applicationDirPath();
    const auto taskifyExecutable = QDir(workingDir).filePath(TASKIFY_EXECUTABLE_NAME);

    if (!QFile::exists(taskifyExecutable)) {
        qDebug() << "[ERROR] Unable to find taskify executable";
        return -1;
    }
#endif

    qDebug() << "TASKIFY_EXECUTABLE : " << taskifyExecutable;

    QStringList taskifyArguments;
    taskifyArguments << "serve";

    QProcess taskify;
    taskify.start(taskifyExecutable, taskifyArguments);

    if (taskify.waitForStarted()) {
        qDebug() << "[INFO] Taskify server started";
    } else {
        qDebug() << "[ERROR] Failed to start taskify server";
        return -1;
    }

    QQmlApplicationEngine engine;
    const QUrl mainQml(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [mainQml](QObject *obj, const QUrl &objUrl) {
                         if (!obj && mainQml == objUrl)
                             QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);

    engine.load(mainQml);

    return app.exec();
}
