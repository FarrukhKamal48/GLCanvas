#include <Core/EntryPoint.h>
#include <ExampleLayers/VerletInstancingLayer.h>
#include "Sandbox.h"

class MyApp : public Application {
public:
    MyApp() {
        PushLayer(new VerletInstanced());
        PushLayer(new OtherLayer());
    }
    ~MyApp() { }
};

Application* CreateApplication() {
    return new MyApp();
}

