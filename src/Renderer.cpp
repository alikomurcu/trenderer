#include "Renderer.h"

namespace TRenderer
{

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::renderScene(Scene::Scene* scene)
{
    for (auto model : scene->models)
    {
        model->draw();
    }
}
}// namespace TRenderer