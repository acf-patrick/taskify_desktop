#ifndef ENUMS_H
#define ENUMS_H

#include <QObject>
#include <QQmlApplicationEngine>

namespace taskify {

class TaskState: public QObject {
    Q_OBJECT


public:
    enum TaskStateEnum {
        TODO,
        READY,
        TESTING,
        DONE
    };

    Q_ENUM(TaskStateEnum)

    TaskState() = default;
    TaskState(const TaskState&) {}
    TaskState(TaskState&&) {}

    static void RegisterType() {
        qmlRegisterUncreatableType<TaskState>("taskify", 1, 0, "TaskState", "TaskState");
    }
};

}

#endif // ENUMS_H
