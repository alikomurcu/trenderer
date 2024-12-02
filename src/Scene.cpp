#include "Scene.h"

namespace Scene
{
Scene::Scene()
{
}

Scene::~Scene()
{
    for (auto e : models)
        delete e;
}

void Scene::addModel(Model* model)
{
    models.push_back(model);
}

} // namespace Scene