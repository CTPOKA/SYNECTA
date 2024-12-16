#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <QObject>
#include <complex>

class DataProcessor : public QObject
{
    Q_OBJECT
public:
    explicit DataProcessor(QObject *parent = nullptr);
    Q_INVOKABLE QVector<double> calculateLogMag(const QVector<double>& frequencies, const QVector<std::complex<double>>& s11Data);

signals:
    void dataReady(const QVector<double>& X, const QVector<double>& Y);
};

#endif // DATAPROCESSOR_H
