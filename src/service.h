#ifndef SERVICE_H
#define SERVICE_H

#include <QFileInfo>

#include "task.h"

namespace taskify {

class IService {
protected:
    virtual ~IService() = default;

    virtual QString getBoardName() = 0;
    virtual QVector<Task> getTasks() = 0;

    virtual bool changeTaskState(const QFileInfo& file, const QString& taskId, Task::State from, Task::State to) = 0;
    virtual bool removeTask(const QFileInfo& file, const QString& taskId) = 0;
};

}

#endif // SERVICE_H
