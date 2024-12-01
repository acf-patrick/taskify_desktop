#ifndef TASKIFY_H
#define TASKIFY_H

#include <QString>
#include <QFileInfo>

#include "task/task_state.h"

namespace taskify {

class Taskify : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString boardName READ boardName WRITE setBoardName NOTIFY boardNameChanged FINAL)
    Q_PROPERTY(QString serializedTasks READ serializedTasks NOTIFY serializedTasksChanged FINAL)

public:
    static void RegisterType()
    {
        qmlRegisterType<taskify::Taskify>("com.example.taskify", 1, 0, "Taskify");
    }

public:
    explicit Taskify(const QString& taskifyExec, QObject* parent = nullptr);
    ~Taskify() = default;

    QString boardName() const;
    void setBoardName(const QString& boardName);

    QString serializedTasks() const;

    Q_INVOKABLE bool changeTaskState(const QFileInfo& file, const QString& taskId, TaskState from, TaskState to);
    Q_INVOKABLE bool removeTask(const QFileInfo& file, const QString& taskId);

signals:
    void boardNameChanged();
    void serializedTasksChanged();

private:
    QString     _boardName;
    QString     _serializedTasks;
    QFileInfo   _taskifyExecutable;
};

}

#endif // TASKIFY_H
