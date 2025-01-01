#include <GLBox/Core/EntryPoint.h>
#include <ExampleLayers/VerletInstancingLayer.h>
#include "Sandbox.h"

class MyApp : public Application {
public:
    MyApp() : Application({ "GLBox", 960, 540 })
    {
        // PushLayer(new VerletInstanced());
        PushLayer(new SpinLayer());
        // PushLayer(new DynamicLayer());
    }
    ~MyApp() { }
};

Application* CreateApplication() {
    return new MyApp();
}

