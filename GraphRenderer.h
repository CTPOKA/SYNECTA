#ifndef GRAPHRENDERER_H
#define GRAPHRENDERER_H

#include <QQuickPaintedItem>

class GraphRenderer : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(double xSteps READ xSteps WRITE setXSteps NOTIFY xStepsChanged)
    Q_PROPERTY(double ySteps READ ySteps WRITE setYSteps NOTIFY yStepsChanged)

public:
    GraphRenderer(QQuickItem *parent = NULL);
    Q_INVOKABLE void setGraphData(const QVector<double>& X, const QVector<double>& Y);

    QColor color() const;

    double xSteps() const;

    double ySteps() const;

public slots:
    void setColor(QColor color);

    void setXSteps(double xSteps);

    void setYSteps(double ySteps);

signals:
    void colorChanged(QColor color);

    void xStepsChanged(double xSteps);

    void yStepsChanged(double ySteps);

protected:
    void paint(QPainter* painter) override;

private:
    QVector<double> X;
    QVector<double> Y;

    double xMin, xMax, yMin, yMax;

    QColor m_color;
    double m_xSteps;
    double m_ySteps;

    void drawGrid(QPainter *painter, const QRectF &rect);
    double XNormalization(double x, const QRectF &rect);
    double YNormalization(double y, const QRectF &rect);
};

#endif // GRAPHRENDERER_H
