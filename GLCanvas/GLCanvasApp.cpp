#include <GLBox/Core/EntryPoint.h>
#include "GLCanvas/GLCanvasLayer.h"

class MyApp : public Application {
public:
    MyApp() : Application({ "GLBox", 960, 540 })
    {
        PushLayer(new MainLayer());
    }
    ~MyApp() { }
};

Application* CreateApplication() {
    return new MyApp();
}

