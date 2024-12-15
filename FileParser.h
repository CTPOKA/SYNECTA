#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <QObject>
#include <QString>
#include <QVector>
#include <complex>

class FileParser : public QObject
{
    Q_OBJECT
public:
    explicit FileParser(QObject *parent = nullptr);
    Q_INVOKABLE bool loadFile(const QString& filePath);

signals:
    void errorOccurred(const QString& error);
    void dataReady(const QVector<double>& frequencies, const QVector<double> &logMagValues);

private:
    QVector<double> frequencies;
    QVector<std::complex<double>> s11Values;

    bool parseLine(const QString& line, double& freq, std::complex<double>& s11);

};

#endif // FILEPARSER_H
