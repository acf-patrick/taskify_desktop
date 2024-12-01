#include "taskify.h"

namespace taskify {

Taskify::Taskify(const QString& taskifyExec, QObject* parent)
    : QObject(parent), _taskifyExecutable(taskifyExec)
{

}

QString Taskify::boardName() const
{
    return _boardName;
}

void Taskify::setBoardName(const QString& boardName)
{
    // how to set board name using taskify API/CLI ?

    _boardName = boardName;
    emit boardNameChanged();
}

QString Taskify::serializedTasks() const
{
    QString tasks = R"([
    {
      "title": "Write the implementation",
      "description": "Add the two values provided\nto the function",
      "state": "TODO",
      "tags": [],
      "info": {
        "filename": "test.cpp",
        "start_line": 3,
        "end_line": 7,
        "date": null,
        "author": null
      },
      "raw": "LyoKICBbVE9ET106IFdyaXRlIHRoZSBpbXBsZW1lbnRhdGlvbgogIEFkZCB0aGUgdHdvIHZhbHVlcyBwcm92aWRlZAogIHRvIHRoZSBmdW5jdGlvbiAKKi8K"
    },
    {
      "title": "Use `add` function into main",
      "description": null,
      "state": "TODO",
      "tags": [],
      "info": {
        "filename": "test.cpp",
        "start_line": 15,
        "end_line": 17,
        "date": null,
        "author": null
      },
      "raw": "LyoKICBbVE9ET106IFVzZSBgYWRkYCBmdW5jdGlvbiBpbnRvIG1haW4KKi8K"
    }
  ])";

    return tasks;
}

bool Taskify::changeTaskState(const QFileInfo& file, const QString& taskId, TaskState from, TaskState to)
{
    return true;
}

bool Taskify::removeTask(const QFileInfo& file, const QString& taskId)
{
    return true;
}

}
