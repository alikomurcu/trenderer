#include "Model.h"
#include "Shader.h"
#include "Camera.h"
#include <vector>

namespace Scene
{
class Scene
{
public:
    Scene();
    ~Scene();
    void addModel(Model* model);

    std::vector<Model*> models;
    Camera* mainCamera;
};
}