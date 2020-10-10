//
// Copyright (c) 2019-2020 David J Albers. All rights reserved.
//

#ifndef PSD_CONTROLPANEL_H
#define PSD_CONTROLPANEL_H

class GLFWwindow;
class PSDApplication;

namespace PSD
{

    class FControlPanel
    {
    public:
        explicit FControlPanel(GLFWwindow*);
        ~FControlPanel();

        void Update();
        void Render() const;
    private:
        float* mClearColor; // kontrolliert PSD::Application::mClearColor
        float* mObjectColor; // kontrolliert PSDApplication::mObjectColor
        bool* bIsWireframeEnabled; // kontrolliert PSD::Application::bIsWireframeEnabled
        friend PSDApplication;
    };

}

#endif //PSD_CONTROLPANEL_H
