#include "DataProcessor.h"

DataProcessor::DataProcessor(QObject *parent) : QObject(parent)
{

}

QVector<double> DataProcessor::calculateLogMag(const QVector<std::complex<double>>& s11Values) const
{
    QVector<double> logMagValues;
    for (const auto& s11 : s11Values) {
        double magnitude = std::abs(s11);
        double logMag = 20 * std::log10(magnitude);
        logMagValues.append(logMag);
    }
    return logMagValues;
}
