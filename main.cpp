#include <QProcess>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    const auto taskifyExecutable = QStringLiteral(TASKIFY_EXECUTABLE);
    QStringList taskifyArguments;
    taskifyArguments << "serve";

    QProcess taskify;
    taskify.start(taskifyExecutable, taskifyArguments);

    if (taskify.waitForStarted()) {
        qDebug() << "Taskify server started";
    } else {
        qDebug() << "Failed to start taskify server";
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
