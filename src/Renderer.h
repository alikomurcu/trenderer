#include "Scene.h"

namespace TRenderer
{
class Renderer
{
public:
    Renderer();
    ~Renderer();

    void init();

    void renderScene(Scene::Scene* scene);
    Scene::Scene* scene;
    std::vector<Shader*> shaders;

};
} // namespace TRenderer