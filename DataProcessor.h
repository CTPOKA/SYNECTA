#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <QObject>
#include <complex>

class DataProcessor : public QObject
{
    Q_OBJECT
public:
    explicit DataProcessor(QObject *parent = nullptr);
    Q_INVOKABLE QVector<double> calculateLogMag(const QVector<std::complex<double>>& s11Data) const;

signals:

};

#endif // DATAPROCESSOR_H
