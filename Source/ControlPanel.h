//
// Copyright (c) 2019-2020 David J Albers. All rights reserved.
//

#ifndef PSD_CONTROLPANEL_H
#define PSD_CONTROLPANEL_H

class FControlPanel
{
public:
    explicit FControlPanel(class GLFWwindow*);
    ~FControlPanel();

    void Update();
    void Render() const;
private:
    float* mCameraPosition; // kontrolliert FCamera::mPosition
    float* mClearColor; // kontrolliert PSD::FApplication::mClearColor
    float* mObjectColor; // kontrolliert PSDApplication::mObjectColor
    bool* bIsWireframeEnabled; // kontrolliert PSD::FApplication::bIsWireframeEnabled
    friend class PSDApplication;
};

#endif //PSD_CONTROLPANEL_H
