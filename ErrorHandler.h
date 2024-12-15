#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <QObject>

class ErrorHandler : public QObject
{
    Q_OBJECT
public:
    explicit ErrorHandler(QObject *parent = nullptr);

signals:
    void errorOccurred(const QString &message);

public slots:
    void handleError(const QString &message);
};

#endif // ERRORHANDLER_H
