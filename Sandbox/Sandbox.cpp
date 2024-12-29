#include <Core/EntryPoint.h>
#include <ExampleLayers/VerletInstancingLayer.h>
#include "Sandbox.h"

class MyApp : public Application {
public:
    MyApp() : Application({ "GLBox", 1920, 1080 })
    {
        PushLayer(new OtherLayer());
        // PushLayer(new VerletInstanced());
    }
    ~MyApp() { }
};

Application* CreateApplication() {
    return new MyApp();
}

