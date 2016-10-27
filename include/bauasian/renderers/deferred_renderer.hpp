#ifndef BAUASIAN_DEFERRED_RENDERER_HPP
#define BAUASIAN_DEFERRED_RENDERER_HPP

#include "deferred_rendering/geometry_renderer.hpp"
#include "deferred_rendering/light_accumulator.hpp"
#include "bauasian/post_processors/filter.hpp"
#include "bauasian/interfaces/size_interface.hpp"
#include "bauasian/post_processors/hdr.hpp"


namespace bauasian
{
	class DeferredRenderer;
}

class bauasian::DeferredRenderer : public SizeInterface
{
public:
	DeferredRenderer(const glm::uvec2 size);
	virtual ~DeferredRenderer();

	virtual void setSize(const glm::uvec2& size) override;

	void addFilter(Filter* filter);
	void clearScreen() const;
	void render(Scene3D* scene) const;
	const float& getExposure() const;
	void setExposure(const float& exposure);

private:
	HDR m_hdr;
	std::list<Filter*> m_filters;

	std::shared_ptr<RenderBuffer> m_depth_buffer;
	GeometryRenderer m_geometry_renderer;
	LightAccumulator m_light_accumulator;

};

#endif /* BAUASIAN_DEFERRED_RENDERER_HPP */
