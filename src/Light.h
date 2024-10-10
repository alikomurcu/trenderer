#include <glm.hpp>
#include "Shader.h"

class Light
{
public:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    Light(const glm::vec3 ambient = glm::vec3(0.1f),
          const glm::vec3 diffuse = glm::vec3(0.5f),
          const glm::vec3 specular = glm::vec3(1.0f));

    virtual void setLight(Shader& shader, const int index = 0) const = 0;
    virtual ~Light() = default;
};

class PointLight : public Light
{
public:
    glm::vec3 position;

    float constant;
    float linear;
    float quadratic;
    PointLight(const glm::vec3 position,
               const glm::vec3 ambient = glm::vec3(0.1f),
               const glm::vec3 diffuse = glm::vec3(0.5f),
               const glm::vec3 specular = glm::vec3(1.0f),
               float constant = 1.0f,
               float linear = 0.09f,
               float quadratic = 0.032f);
    void setLight(Shader& shader, const int index = 0) const override;
};

class DirectionalLight : public Light
{
public:
    glm::vec3 direction;
    DirectionalLight(const glm::vec3 direction,
                     const glm::vec3 ambient = glm::vec3(0.1f),
                     const glm::vec3 diffuse = glm::vec3(0.5f),
                     const glm::vec3 specular = glm::vec3(1.0f));
    void setLight(Shader& shader, const int index = 0) const override;
};

class SpotLight : public Light
{
public:
    glm::vec3 position;
    glm::vec3 direction;

    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;
    SpotLight(const glm::vec3 position,
              const glm::vec3 direction,
              float cutOff,
              float outerCutOff,
              const glm::vec3 ambient = glm::vec3(0.1f),
              const glm::vec3 diffuse = glm::vec3(0.5f),
              const glm::vec3 specular = glm::vec3(1.0f),
              float constant = 1.0f,
              float linear = 0.09f,
              float quadratic = 0.032f);
    void setLight(Shader& shader, const int index = 0) const override;
};