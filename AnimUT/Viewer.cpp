#include <QWheelEvent>
#include <QTimeLine>

#include "GraphicsItem.h"
#include "Viewer.h"

Viewer::Viewer(QWidget *parent_): QGraphicsView(parent_)
{
    scene = new QGraphicsScene(this);
    setScene(scene);
    setRenderHint(QPainter::Antialiasing);
}


Viewer::~Viewer()
{
    delete scene;
}

/**
 * @brief Viewer::addItem Add an item to the graphic view
 * @param item - QGraphicsItem - Item you want to add
 */
void Viewer::addItem(QGraphicsItem *item)
{
    scene->addItem(item);
}

/**
 * @brief Viewer::getScene Get the scene of the graphic view
 * @return scene - QGraphicsScene - The scene of the graphic view
 */
QGraphicsScene *Viewer::getScene()
{
    return scene;
}

/**
 * @brief Viewer::setSceneRect Method to easily define and draw the borders
 * @param x - qreal - X coordinate of the scene
 * @param y - qreal - Y coordinate of the scene
 * @param w - qreal - Scene width
 * @param h - qreal - Scene height
 * @param myPen - qreal - Pen to define how to draw the borders
 */
void Viewer::setSceneRect(qreal x, qreal y, qreal w, qreal h, QPen myPen){
    scene->setSceneRect(x,y,w,h); // define scene rectangle for QT
    QLineF topLine(scene->sceneRect().topLeft(), scene->sceneRect().topRight()); // create a line to draw the border
    QLineF leftLine(scene->sceneRect().topLeft(), scene->sceneRect().bottomLeft());
    QLineF rightLine(scene->sceneRect().topRight(),  scene->sceneRect().bottomRight());
    QLineF bottomLine(scene->sceneRect().bottomLeft(), scene->sceneRect().bottomRight());
    scene->addLine(topLine, myPen);
    scene->addLine(leftLine, myPen);
    scene->addLine(rightLine, myPen);
    scene-> addLine(bottomLine, myPen);
}


/*
 * Smooth zooming feature, code from:
 * https://wiki.qt.io/Smooth_Zoom_In_QGraphicsView
 * */
void Viewer::wheelEvent(QWheelEvent * event)
{
    int numDegrees = event->delta() / 8;
    int numSteps = numDegrees / 15; // see QWheelEvent documentation
    _numScheduledScalings += numSteps;
    if (_numScheduledScalings * numSteps < 0) // if user moved the wheel in another direction, we reset previously scheduled scalings
        _numScheduledScalings = numSteps;

    QTimeLine *anim = new QTimeLine(350, this);
    anim->setUpdateInterval(20);

    connect(anim, SIGNAL(valueChanged(qreal)), SLOT(scalingTime(qreal)));
    connect(anim, SIGNAL(finished()), SLOT(animFinished()));
    anim->start();
}

void Viewer::scalingTime(qreal /* unused */)
{
    qreal factor = 1.0+ qreal(_numScheduledScalings) / 300.0;
    scale(factor, factor);
}

void Viewer::animFinished()
{
    if (_numScheduledScalings > 0)
        _numScheduledScalings--;
    else
        _numScheduledScalings++;
    sender()->~QObject();
}


