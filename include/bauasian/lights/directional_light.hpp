#ifndef BAUASIAN_DIRECTIONAL_LIGHT_HPP
#define BAUASIAN_DIRECTIONAL_LIGHT_HPP

#include "light.hpp"
#include "mixins/direction_mixin.hpp"
#include "bauasian/uniform_buffers/directional_light_buffer.hpp"
#include "bauasian/renderers/shadow_renderer.hpp"


namespace bauasian
{
	class DirectionalLight;
}

class bauasian::DirectionalLight final : public Light, public DirectionMixin
{
public:
	DirectionalLight(const glm::vec3& direction);

	virtual void setDiffuseColor(const glm::vec3& color) override;
	virtual void setSpecularColor(const glm::vec3& color) override;
	virtual void setDirection(const glm::vec3& direction) override;

	void bind() const;
	void enableShadows(unsigned size, float distance);
	void disableShadows();
	void updateShadowMap(const Scene3D* scene);

private:
	DirectionalLightBuffer m_buffer;
	std::unique_ptr<ShadowRenderer> m_shadow_renderer;

};

#endif /* BAUASIAN_DIRECTIONAL_LIGHT_HPP */
