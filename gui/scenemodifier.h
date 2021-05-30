#ifndef SCENEMODIFIER_H
#define SCENEMODIFIER_H

#include <QtCore/QObject>

#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qtransform.h>

#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QPhongMaterial>

#include <QTimer>

#include "../utils/particle.h"
#include "plane.h"
#include "sphere.h"


class SceneModifier : public QObject
{
    Q_OBJECT

public:
    explicit SceneModifier(Qt3DCore::QEntity *rootEntity, Particle* part);
    ~SceneModifier();

private slots:
    void timerAlarm();
private:
    QTimer *timer;
    Qt3DCore::QEntity *rootEntity;
    Sphere* sphere;
    Plane* plane;
    Plane* plane2;
};

#endif // SCENEMODIFIER_H

