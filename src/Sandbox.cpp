#include "Sandbox.h"


Scene::Scene* CreateScene() {
    return new Scene::VerletInstanced();
}
