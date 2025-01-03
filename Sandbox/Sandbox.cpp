#include <GLBox/Core/EntryPoint.h>
#include "Sandbox.h"

class MyApp : public Application {
public:
    MyApp() : Application({ "GLBox", 960, 540 })
    {
        PushLayer(new SpinLayer());
    }
    ~MyApp() { }
};

Application* CreateApplication() {
    return new MyApp();
}

