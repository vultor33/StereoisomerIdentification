#include "myorbitcontroller.h"

#include <Qt3DCore>
#include <QObject>
#include <Qt3DExtras>

MyOrbitController::MyOrbitController(Qt3DCore::QNode *parent)
    : QAbstractCameraController(parent)
{
    in_zoom_limit = 20.0;
}

MyOrbitController::~MyOrbitController()
{
}

void MyOrbitController::moveCamera(const InputState &state, float dt)
{
    Qt3DRender::QCamera *theCamera = camera();

    if (theCamera == nullptr)
        return;
    const QVector3D upVector(0.0f, 1.0f, 0.0f);

    if (state.leftMouseButtonActive)
    {
        if(((theCamera->position() - theCamera->viewCenter()).length() < in_zoom_limit) && (state.ryAxisValue > 0))
                return;
        else
        {
            theCamera->translate(QVector3D(0, 0, state.ryAxisValue * lookSpeed() / 10.0), theCamera->DontTranslateViewCenter);
            return;
        }
    }
    else if (state.rightMouseButtonActive) {
        // Orbit
        theCamera->panAboutViewCenter((state.rxAxisValue * lookSpeed()) * dt, upVector);
        theCamera->tiltAboutViewCenter((state.ryAxisValue * lookSpeed()) * dt);
        return;
    }

    /*  QOrbitCameraController
    Qt3DRender::QCamera *theCamera = camera();
    if (theCamera == nullptr)
        return;
    const QVector3D upVector(0.0f, 1.0f, 0.0f);
    // Mouse input
    if (state.leftMouseButtonActive) {
        if (state.rightMouseButtonActive) {
            if ( zoomDistance(camera()->position(), theCamera->viewCenter()) > d->m_zoomInLimit * d->m_zoomInLimit) {
                // Dolly up to limit
                theCamera->translate(QVector3D(0, 0, state.ryAxisValue), theCamera->DontTranslateViewCenter);
            } else {
                theCamera->translate(QVector3D(0, 0, -0.5), theCamera->DontTranslateViewCenter);
            }
        } else {
            // Translate
            theCamera->translate(QVector3D(clampInputs(state.rxAxisValue, state.txAxisValue) * linearSpeed(),
                                          clampInputs(state.ryAxisValue, state.tyAxisValue) * linearSpeed(),
                                          0) * dt);
        }
        return;
    }
    // Keyboard Input
    if (state.altKeyActive) {
        // Orbit
        theCamera->panAboutViewCenter((state.txAxisValue * lookSpeed()) * dt, upVector);
        theCamera->tiltAboutViewCenter((state.tyAxisValue * lookSpeed()) * dt);
    } else if (state.shiftKeyActive) {
        if (zoomDistance(camera()->position(), theCamera->viewCenter()) > d->m_zoomInLimit * d->m_zoomInLimit) {
            // Dolly
            theCamera->translate(QVector3D(0, 0, state.tyAxisValue * linearSpeed() * dt), theCamera->DontTranslateViewCenter);
        } else {
            theCamera->translate(QVector3D(0, 0, -0.5), theCamera->DontTranslateViewCenter);
        }
    } else {
        // Translate
        theCamera->translate(QVector3D(clampInputs(state.leftMouseButtonActive ? state.rxAxisValue : 0, state.txAxisValue) * linearSpeed(),
                                      clampInputs(state.leftMouseButtonActive ? state.ryAxisValue : 0, state.tyAxisValue) * linearSpeed(),
                                      state.tzAxisValue * linearSpeed()) * dt);
    }
*/

}


void MyOrbitController::setCameraViewCenterToPos(QVector3D pos)
{
    Qt3DRender::QCamera *theCamera = camera();
    theCamera->setViewCenter(pos);
}


