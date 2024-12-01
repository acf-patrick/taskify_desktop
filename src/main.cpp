#include <QDir>
#include <QQmlContext>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <memory>

#include "taskify.h"
#include "task/task_state.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

#ifdef QT_DEBUG
    const auto taskifyExecutable = QStringLiteral(TASKIFY_EXECUTABLE);
#else
    const auto workingDir = QCoreApplication::applicationDirPath();
    const auto taskifyExecutable = QDir(workingDir).filePath(TASKIFY_EXECUTABLE_NAME);
#endif

    if (!QFile::exists(taskifyExecutable)) {
        qDebug() << "[ERROR] Unable to find taskify executable";
        return -1;
    }

    qDebug() << "[INFO] taskify executable : " << taskifyExecutable;

    // register meta types
    {
        taskify::Taskify::RegisterType();
        taskify::TaskState::RegisterType();
    }

    QQmlApplicationEngine engine;

    taskify::Taskify taskify(taskifyExecutable);
    engine.rootContext()->setContextProperty("taskify", &taskify);

    {
        const QUrl mainQml(QStringLiteral("qrc:/main.qml"));
        QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
            &app, [mainQml](QObject *obj, const QUrl &objUrl) {
                if (!obj && mainQml == objUrl) {
                    qDebug() << "[ERROR] failed to load main QML";
                    QCoreApplication::exit(-1);
                }
            }, Qt::QueuedConnection);
        engine.load(mainQml);
    }

    return app.exec();
}
