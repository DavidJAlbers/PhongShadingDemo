#include <memory>

#include "PSD.h"
#include "ControlPanel.h"

class PSDApplication : public PSD::FApplication
{
public:
    PSDApplication() : FApplication("Phong Shading Demo") {}

    void OnStart() override
    {
        mControlPanel = std::make_unique<PSD::FControlPanel>(GetWindow());
        mControlPanel->mClearColor = GetClearColor();
        mControlPanel->mObjectColor = mObjectColor;
        mControlPanel->bIsWireframeEnabled = IsWireframeEnabled();

        mTestShader = std::make_unique<PSD::FShader>("Test");
        mQuadMesh = std::make_unique<PSD::FVertexArray>();

        constexpr unsigned int Indices[]{
                0, 1, 2,
                0, 2, 3
        };
        mQuadMesh->SetIndexBuffer(Indices, sizeof(Indices) / sizeof(unsigned int));

        constexpr float Positions[]{
                0.8f, 0.8f, 0.0f,
                -0.8f, 0.8f, 0.0f,
                -0.8f, -0.8f, 0.0f,
                0.8f, -0.8f, 0.0f
        };
        mQuadMesh->AddVertexBuffer(Positions, sizeof(Positions) / sizeof(float));

        mSphereMesh = PSD::LoadMesh("SphereMediumPoly");
    }

    void OnUpdate() override
    {
        mControlPanel->Update();
    }

    void OnRender() override
    {
        mTestShader->SetVector3f("VertexColor", mObjectColor);
        mTestShader->Bind();
        //mQuadMesh->SimpleDraw();
        mSphereMesh->SimpleDraw();

        mControlPanel->Render();
    }

private:
    float mObjectColor[3] = { 1.0f, 1.0f, 0.0f };

    std::unique_ptr<PSD::FShader> mTestShader;
    std::unique_ptr<PSD::FVertexArray> mQuadMesh;
    std::unique_ptr<PSD::FControlPanel> mControlPanel;

    std::unique_ptr<PSD::FVertexArray> mSphereMesh;
};

int main()
{
    PSD::SetApplication(new PSDApplication())->Start();
}