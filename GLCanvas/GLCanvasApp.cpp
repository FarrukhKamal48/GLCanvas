#include <GLBox/Core/EntryPoint.h>
#include "GLCanvas/CanvasLayer.h"

class MyApp : public Application {
public:
    MyApp() : Application({ "GLBox", 960, 540 })
    {
        PushLayer(new CanvasLayer());
    }
    ~MyApp() { }
};

Application* CreateApplication() {
    return new MyApp();
}

