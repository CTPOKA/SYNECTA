#include "GraphRenderer.h"

#include <QPainter>
#include <cmath>

GraphRenderer::GraphRenderer(QQuickItem *parent) :
    QQuickPaintedItem(parent),
    m_color(Qt::blue)
{

}

void GraphRenderer::setGraphData(const QVector<double> &X, const QVector<double> &Y)
{
    this->X = X;
    this->Y = Y;

    xMin = *std::min_element(X.begin(), X.end());
    xMax = *std::max_element(X.begin(), X.end());
    yMin = *std::min_element(Y.begin(), Y.end());
    yMax = *std::max_element(Y.begin(), Y.end());

    m_xSteps = (xMax - xMin) / 10;
    double xScale = pow(10, floor(log10(m_xSteps)));
    m_xSteps = floor(m_xSteps / xScale) * xScale;

    m_ySteps = (yMax - yMin) / 10;
    double yScale = pow(10, floor(log10(m_ySteps)));
    m_ySteps = floor(m_ySteps / yScale) * yScale;

    update();
}

QColor GraphRenderer::color() const
{
    return m_color;
}

double GraphRenderer::xSteps() const
{
    return m_xSteps;
}

double GraphRenderer::ySteps() const
{
    return m_ySteps;
}

void GraphRenderer::setColor(QColor color)
{
    if (m_color == color)
        return;

    m_color = color;
    update();
    emit colorChanged(m_color);
}

void GraphRenderer::setXSteps(double xDivisions)
{
    if (m_xSteps == xDivisions)
        return;

    m_xSteps = xDivisions;
    update();
    emit xStepsChanged(m_xSteps);
}

void GraphRenderer::setYSteps(double yDivisions)
{
    if (m_ySteps == yDivisions)
        return;

    m_ySteps = yDivisions;
    update();
    emit yStepsChanged(m_ySteps);
}

void GraphRenderer::paint(QPainter *painter)
{
    if (X.isEmpty() || Y.isEmpty())
        return;

    QRectF rect = boundingRect();

    drawGrid(painter, rect);

    QPen graphPen(m_color);
    graphPen.setWidth(2);
    painter->setPen(graphPen);

    double x1, y1, x2, y2;
    for (int i = 0; i < X.size(); ++i) {
        x1 = XNormalization(X[i], rect);
        y1 = YNormalization(Y[i], rect);

        if (i >= 0)
            painter->drawLine(x1, y1, x2, y2);

        x2 = x1;
        y2 = y1;
    }
}

void GraphRenderer::drawGrid(QPainter *painter, const QRectF &rect)
{
    QPen gridPen(Qt::lightGray);
    gridPen.setStyle(Qt::DashLine);
    gridPen.setWidth(2);
    painter->setPen(gridPen);

    double xStart = floor(xMin / m_xSteps) * m_xSteps;
    double yStart = floor(yMin / m_ySteps) * m_ySteps;

    for (double x = xStart; x < xMax; x+=m_xSteps) {
        double xNorm = XNormalization(x, rect);
        painter->drawLine(xNorm, rect.top(), xNorm, rect.bottom());
    }

    for (double y = yStart; y < yMax; y+=m_ySteps) {
        double yNorm = YNormalization(y, rect);
        painter->drawLine(rect.left(), yNorm, rect.right(), yNorm);
    }

    QPen axisPen(Qt::black);

    QFont font = painter->font();
    font.setPointSize(10);
    painter->setFont(font);
    painter->setPen(axisPen);

    for (double x = xStart; x < xMax; x+=m_xSteps) {
        double xNorm = XNormalization(x, rect);
        QString label = QString::number(x, 'e', 2);
        painter->drawText(xNorm + 15, rect.bottom() - 15, label);
    }

    for (double y = yStart; y < yMax; y+=m_ySteps) {
        double yNorm = YNormalization(y, rect);
        QString label = QString::number(y, 'f', 2);
        painter->drawText(rect.left() + 15, yNorm + 15, label);
    }
}

double GraphRenderer::XNormalization(double x, const QRectF &rect)
{
    return rect.left() + (x - xMin) / (xMax - xMin) * rect.width();
}

double GraphRenderer::YNormalization(double y, const QRectF &rect)
{
    return rect.bottom() - (y - yMin) / (yMax - yMin) * rect.height();
}

