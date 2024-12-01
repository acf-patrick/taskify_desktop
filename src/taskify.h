#ifndef TASKIFY_H
#define TASKIFY_H

#include "service.h"

namespace taskify {

class Taskify : public IService {
    Q_OBJECT
public:
    explicit Taskify(const QString& taskifyExec, QObject* parent = nullptr) : IService(parent) {}

    QString getBoardName() override { return QString(); }
    QVector<Task> getTasks() override { return QVector<Task>(); }

    bool changeTaskState(const QFileInfo& file, const QString& taskId, Task::State from, Task::State to) override { return true; }
    bool removeTask(const QFileInfo& file, const QString& taskId) { return true; }
};

}

#endif // TASKIFY_H
