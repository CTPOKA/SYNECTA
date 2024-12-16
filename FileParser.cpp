#include "FileParser.h"
#include "FileParser.h"
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QUrl>
#include <cmath>

FileParser::FileParser(QObject *parent) : QObject(parent)
{

}

Q_INVOKABLE bool FileParser::loadFile(const QString &filePath)
{
    QUrl url(filePath);
    QFile file(url.toLocalFile());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        emit errorOccurred("Не удалось открыть файл: " + filePath);
        return false;
    }

    frequencies.clear();
    s11Values.clear();

    QTextStream in(&file);

    QString header = in.readLine().trimmed();
    if (!header.startsWith('#')) {
        emit errorOccurred("Файл не содержит заголовка.");
        return false;
    }

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();

        if (line.startsWith('!') || line.isEmpty()) {
            continue;
        }

        double freq = 0.0;
        std::complex<double> s11;

        if (!parseLine(line, freq, s11)) {
            emit errorOccurred("Некорректный формат строки: " + line);
            return false;
        }

        frequencies.append(freq);
        s11Values.append(s11);
    }

    if (frequencies.isEmpty() || s11Values.isEmpty()) {
        emit errorOccurred("Файл не содержит данных.");
        return false;
    }

    emit dataReady(frequencies, s11Values);

    return true;
}

bool FileParser::parseLine(const QString &line, double &freq, std::complex<double> &s11)
{
    QStringList parts = line.split(QRegExp("\\s+"), Qt::SkipEmptyParts);
    if (parts.size() != 3) {
        return false;
    }

    bool ok1, ok2, ok3;
    freq = parts[0].toDouble(&ok1);
    double real = parts[1].toDouble(&ok2);
    double imag = parts[2].toDouble(&ok3);

    if (!(ok1 && ok2 && ok3)) {
        return false;
    }

    s11 = std::complex<double>(real, imag);
    return true;
}
