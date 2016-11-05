#ifndef BAUASIAN_DEFERRED_RENDERER_HPP
#define BAUASIAN_DEFERRED_RENDERER_HPP

#include "bauasian/renderers/deferred_rendering/geometry_pass.hpp"
#include "deferred_rendering/light_accumulator.hpp"
#include "bauasian/mixins/size_mixin.hpp"
#include "bauasian/post_processors/hdr.hpp"
#include "bauasian/post_processors/bloom.hpp"


namespace bauasian
{
	class DeferredRenderer;
}

class bauasian::DeferredRenderer : public SizeMixin<glm::uvec2>
{
public:
	DeferredRenderer(const glm::uvec2 size);
	virtual ~DeferredRenderer();

	virtual void setSize(const glm::uvec2& size) override;

	void addPostProcessor(PostProcessor* post_processor);
	void clearScreen() const;
	void render(const Scene3D* scene) const;
	float getExposure() const
	{ return m_hdr.getExposure(); }
	void setExposure(float exposure)
	{ m_hdr.setExposure(exposure); }

private:
	std::list<PostProcessor*> m_post_processors;

	std::shared_ptr<RenderBuffer> m_depth_buffer;
	GeometryPass m_geometry_renderer;
	LightAccumulator m_light_accumulator;

	HDR m_hdr;
	Bloom m_bloom;

};

#endif /* BAUASIAN_DEFERRED_RENDERER_HPP */
