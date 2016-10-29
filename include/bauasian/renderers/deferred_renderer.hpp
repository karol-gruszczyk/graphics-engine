#ifndef BAUASIAN_DEFERRED_RENDERER_HPP
#define BAUASIAN_DEFERRED_RENDERER_HPP

#include "deferred_rendering/geometry_renderer.hpp"
#include "deferred_rendering/light_accumulator.hpp"
#include "bauasian/mixins/size_mixin.hpp"
#include "bauasian/post_processors/ssao.hpp"
#include "bauasian/post_processors/hdr.hpp"
#include "bauasian/post_processors/bloom.hpp"


namespace bauasian
{
	class DeferredRenderer;
}

class bauasian::DeferredRenderer : public SizeMixin
{
public:
	DeferredRenderer(const glm::uvec2 size);
	virtual ~DeferredRenderer();

	virtual void setSize(const glm::uvec2& size) override;

	void addPostProcessor(PostProcessor* post_processor);
	void clearScreen() const;
	void render(Scene3D* scene) const;
	const float& getExposure() const;
	void setExposure(const float& exposure);

private:
	std::list<PostProcessor*> m_post_processors;

	std::shared_ptr<Texture> m_depth_buffer;
	GeometryRenderer m_geometry_renderer;
	LightAccumulator m_light_accumulator;

	SSAO m_ssao;
	HDR m_hdr;
	Bloom m_bloom;

};

#endif /* BAUASIAN_DEFERRED_RENDERER_HPP */
