#ifndef MYORBITCONTROLLER_H
#define MYORBITCONTROLLER_H

#include <Qt3DCore>
#include <QObject>
#include <Qt3DExtras>
#include <Qt3DRender>

class MyOrbitController : public Qt3DExtras::QAbstractCameraController
{
    Q_OBJECT

public:
    MyOrbitController(Qt3DCore::QNode *parent = nullptr);
    ~MyOrbitController();

    void setCamera2(Qt3DRender::QCamera *camera);

    void setCameraViewCenterToPos(QVector3D pos);


private:
    void moveCamera(const InputState &state, float dt);

    bool camera2Enabled;
    Qt3DRender::QCamera *camera2;


    qreal in_zoom_limit;

};

#endif // MYORBITCONTROLLER_H
