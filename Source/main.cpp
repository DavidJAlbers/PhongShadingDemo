#include <memory>

#include "PSD.h"
#include "GeometryObject.h"

#include "ControlPanel.h"
#include "Camera.h"

#include "glm/glm.hpp"
#include "glm/ext.hpp"

class PSDApplication : public PSD::FApplication
{
public:
    PSDApplication() : FApplication("Phong Shading Demo") {}

    void OnStart() override
    {
        mCamera = std::make_unique<FCamera>(GetWindow(), glm::vec3(0.0f, 0.0f, 5.0f));

        mControlPanel = std::make_unique<FControlPanel>(GetWindow());
        mControlPanel->mClearColor = GetClearColor();
        mControlPanel->mObjectColor = mObjectColor;
        mControlPanel->bIsWireframeEnabled = IsWireframeEnabled();
        mControlPanel->mCameraPosition = mCamera->GetPosition();

        mTestShader = std::make_unique<PSD::FShader>("Test");
        mSphere = std::make_unique<FGeometryObject>(
                PSD::LoadMesh("Cube"),
                glm::vec3(0.0f, 0.0f, 0.0f)
        );
    }

    void OnUpdate() override
    {
        mCamera->Update();
        mControlPanel->Update();
    }

    void OnRender() override
    {
        mTestShader->SetMatrix4f("ProjectionMatrix", mCamera->GetProjectionMatrix());
        mTestShader->SetMatrix4f("ViewMatrix", mCamera->GetViewMatrix());
        mTestShader->SetMatrix4f("ModelMatrix", glm::translate(glm::mat4(1.0f), mSphere->GetPosition()));
        mTestShader->SetVector3f("VertexColor", mObjectColor);
        mTestShader->Bind();
        mSphere->Draw();

        mControlPanel->Render();
    }

private:
    float mObjectColor[3] = { 1.0f, 1.0f, 0.0f };

    std::unique_ptr<FGeometryObject> mSphere;
    std::unique_ptr<FCamera> mCamera;

    std::unique_ptr<PSD::FShader> mTestShader;
    std::unique_ptr<FControlPanel> mControlPanel;
};

int main()
{
    PSD::SetApplication(new PSDApplication())->Start();
}