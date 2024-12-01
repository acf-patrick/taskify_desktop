#include <QDir>
#include <QQmlContext>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <memory>

#include "taskify.h"

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

    qDebug() << "[INFO] taskify executable : " << taskifyExecutable;

    qmlRegisterType<taskify::Taskify>("com.example.taskify", 1, 0, "Taskify");
    std::shared_ptr<taskify::IService> mainService = std::make_shared<taskify::Taskify>(taskifyExecutable);

    QQmlApplicationEngine engine;
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

    engine.rootContext()->setContextProperty("taskify", mainService.get());

    return app.exec();
}
