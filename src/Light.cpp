#include "Light.h"

Light::Light(const glm::vec3 ambient, const glm::vec3 diffuse, const glm::vec3 specular)
    : ambient(ambient), diffuse(diffuse), specular(specular) {}

PointLight::PointLight(const glm::vec3 position, const glm::vec3 ambient, const glm::vec3 diffuse, const glm::vec3 specular, float constant, float linear, float quadratic)
    : Light(ambient, diffuse, specular), position(position), constant(constant), linear(linear), quadratic(quadratic) {}

void PointLight::setLight(Shader& shader, const int index) const
{
    shader.use();
    shader.setVec3("pointLights[" + std::to_string(index) + "].position", position);
    shader.setVec3("pointLights[" + std::to_string(index) + "].ambient", ambient);
    shader.setVec3("pointLights[" + std::to_string(index) + "].diffuse", diffuse);
    shader.setVec3("pointLights[" + std::to_string(index) + "].specular", specular);
    shader.setFloat("pointLights[" + std::to_string(index) + "].constant", constant);
    shader.setFloat("pointLights[" + std::to_string(index) + "].linear", linear);
    shader.setFloat("pointLights[" + std::to_string(index) + "].quadratic", quadratic);
}

DirectionalLight::DirectionalLight(const glm::vec3 direction, const glm::vec3 ambient, const glm::vec3 diffuse, const glm::vec3 specular)
    : Light(ambient, diffuse, specular), direction(direction) {}

void DirectionalLight::setLight(Shader& shader, const int index) const
{
    shader.use();
    shader.setVec3("directionalLight.direction", direction);
    shader.setVec3("directionalLight.ambient", ambient);
    shader.setVec3("directionalLight.diffuse", diffuse);
    shader.setVec3("directionalLight.specular", specular);
}

SpotLight::SpotLight(const glm::vec3 position, const glm::vec3 direction, float cutOff, float outerCutOff, const glm::vec3 ambient, const glm::vec3 diffuse, const glm::vec3 specular, float constant, float linear, float quadratic)
    : Light(ambient, diffuse, specular), position(position), direction(direction), cutOff(cutOff), outerCutOff(outerCutOff), constant(constant), linear(linear), quadratic(quadratic) {}

void SpotLight::setLight(Shader& shader, const int index) const
{
    shader.use();
    shader.setVec3("spotLight.position", position);
    shader.setVec3("spotLight.direction", direction);
    shader.setVec3("spotLight.ambient", ambient);
    shader.setVec3("spotLight.diffuse", diffuse);
    shader.setVec3("spotLight.specular", specular);
    shader.setFloat("spotLight.cutOff", cutOff);
    shader.setFloat("spotLight.outerCutOff", outerCutOff);
    shader.setFloat("spotLight.constant", constant);
    shader.setFloat("spotLight.linear", linear);
    shader.setFloat("spotLight.quadratic", quadratic);
}