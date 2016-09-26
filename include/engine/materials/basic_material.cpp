#include "basic_material.hpp"

using engine::BasicMaterial;
using engine::ShaderProgram;


BasicMaterial::BasicMaterial(ShaderProgram* shader)
        : m_shader(shader)
{}

void BasicMaterial::setDiffuse(const glm::vec3& color)
{
    m_diffuse_color = color;
}

void BasicMaterial::setDiffuse(Texture* texture)
{
    m_diffuse_texture = texture;
}

void BasicMaterial::bind() const
{
    if (m_diffuse_texture)
    {
        m_shader->setUniformFloat("material.use_diffuse_texture", true);
        m_diffuse_texture->bind();
    }
    else
        m_shader->setUniformFloat("material.use_diffuse_texture", false);
    m_shader->setUniformVector3("material.diffuse_color", m_diffuse_color);
}

void BasicMaterial::unbind() const
{
    m_shader->setUniformFloat("material.use_diffuse_texture", false);
    if (m_diffuse_texture)
        m_diffuse_texture->unbind();
}
