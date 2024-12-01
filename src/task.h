#ifndef TASK_H
#define TASK_H

#include <optional>
#include <QDateTime>
#include <QStringList>

namespace taskify {

struct Task {

    enum class State {
        TODO,
        READY,
        TESTING,
        DONE
    };

    struct Author {
        QString email;
        QString name;
    };

    struct Info {
        QString filename;
        unsigned int startLine, endLine;
        std::optional<QDateTime> date;
        std::optional<Author> author;
    };

    QString title;
    QString description;
    State state;
    QStringList tags;           // describes with hash inside user comments
    QString raw;                // unique base64 ID
    Info info;
};

}

#endif // TASK_H
