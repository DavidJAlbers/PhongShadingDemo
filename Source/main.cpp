#include <memory>

#include "PSD.h"

#include "GeometryObject.h"
#include "ControlPanel.h"
#include "Renderer.h"
#include "Camera.h"

#include "glm/glm.hpp"

class PSDApplication : public PSD::FApplication
{
public:
    PSDApplication() : FApplication("Phong Shading Demo") {}

    void OnStart() override
    {
        mSphere = std::make_unique<FGeometryObject>(
                PSD::LoadMesh("SphereMediumPoly"),
                glm::vec3(0.0f, 0.0f, 0.0f),
                1.0f,
                glm::vec3(1.0f, 0.0f, 0.0f)
        );
        mSphere2 = std::make_shared<FGeometryObject>(
                PSD::LoadMesh("SphereHighPoly"),
                glm::vec3(0.0f, 0.0f, -10.0f),
                2.0f,
                glm::vec3(0.0f, 0.0f, 1.0f)
        );
        mSphere3 = std::make_shared<FGeometryObject>(
                PSD::LoadMesh("SphereLowPoly"),
                glm::vec3(5.0f, 0.0f, -8.0f),
                0.5f,
                glm::vec3(0.0f, 1.0f, 0.0f)
        );
        mTestShader = std::make_shared<PSD::FShader>("Phong");
        mCamera = std::make_shared<FCamera>(ExposeNativeWindow(), glm::vec3(0.0f, 0.0f, 5.0f));

        mRenderer = std::make_unique<FRenderer>();

        mControlPanel = std::make_unique<FControlPanel>(ExposeNativeWindow());
        mControlPanel->mClearColor = GetClearColor();
        mControlPanel->bIsWireframeEnabled = IsWireframeEnabled();
        mControlPanel->mCameraPosition = mCamera->GetPosition();
        mControlPanel->mLightDirection = mLightDirection;
    }

    void OnUpdate() override
    {
        mCamera->Update(this, GetDeltaTime());
        mControlPanel->Update();
    }

    void OnRender() override
    {
        mTestShader->SetVector3f("LightDirection", mLightDirection);

        mRenderer->BeginScene(mTestShader, mCamera);
        mRenderer->DrawSingle(mSphere);
        mRenderer->DrawSingle(mSphere2);
        mRenderer->DrawSingle(mSphere3);
        mRenderer->EndScene();

        mControlPanel->Render();
    }

private:
    float mLightDirection[3] =  { -0.5f, -1.0f, 0.0f };

    std::shared_ptr<FGeometryObject> mSphere;
    std::shared_ptr<FGeometryObject> mSphere2;
    std::shared_ptr<FGeometryObject> mSphere3;
    std::shared_ptr<FCamera> mCamera;
    std::shared_ptr<PSD::FShader> mTestShader;

    std::unique_ptr<FRenderer> mRenderer;

    std::unique_ptr<FControlPanel> mControlPanel;
};

int main()
{
    PSD::SetApplication(new PSDApplication())->Start();
}