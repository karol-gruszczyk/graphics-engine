#ifndef GRAPHICS_ENGINE_BASICMATERIAL_HPP
#define GRAPHICS_ENGINE_BASICMATERIAL_HPP

#include <glm/glm.hpp>

#include "texture.hpp"
#include "../shaders/shader_program.hpp"


namespace engine
{
    class BasicMaterial;
}

class engine::BasicMaterial
{
public:
    BasicMaterial(ShaderProgram* shader);

    void setDiffuse(const glm::vec3& color);
    void setDiffuse(Texture* texture);

    virtual void bind() const;
    virtual void unbind() const;

protected:
    ShaderProgram* m_shader;

    glm::vec3 m_diffuse_color = { 1.f, 1.f, 1.f };
    Texture* m_diffuse_texture;
};


#endif //GRAPHICS_ENGINE_BASICMATERIAL_HPP
