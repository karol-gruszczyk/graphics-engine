#include "deferred_renderer.hpp"


using bauasian::DeferredRenderer;

DeferredRenderer::DeferredRenderer(const glm::uvec2 size)
		: SizeMixin(size), m_depth_buffer(std::make_shared<RenderBuffer>()),
		  m_geometry_renderer(size, m_depth_buffer), m_light_accumulator(size, m_depth_buffer)
{
	m_hdr.setSize(size);
}

DeferredRenderer::~DeferredRenderer()
{
	for (auto& filter : m_filters)
		delete filter;
}

void DeferredRenderer::setSize(const glm::uvec2& size)
{
	SizeMixin::setSize(size);
	m_geometry_renderer.setSize(m_size);
	m_light_accumulator.setSize(m_size);
	for (auto& filter : m_filters)
		filter->setSize(m_size);
}

void DeferredRenderer::addFilter(Filter* filter)
{
	filter->setSize(m_size);
	m_filters.push_back(filter);
}

void DeferredRenderer::clearScreen() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void DeferredRenderer::render(Scene3D* scene) const
{
	glEnable(GL_STENCIL_TEST);  // use stencil test to process lights only on geometry
	glStencilMask(0xFF);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	m_geometry_renderer.render(scene);
	glDisable(GL_DEPTH_TEST);

	glStencilFunc(GL_EQUAL, 1, 0xFF);
	glStencilMask(0x00);
	m_geometry_renderer.bindTextures();
	m_light_accumulator.render(scene);
	glDisable(GL_STENCIL_TEST);

	glEnable(GL_DEPTH_TEST);
	scene->renderSkyBox();
	glDisable(GL_DEPTH_TEST);

	if (m_filters.size())
	{
		m_hdr.process(m_light_accumulator.getTexture(), false);
		const Texture* texture = m_hdr.getTexture();
		for (auto it = m_filters.begin();; it++)
		{
			bool last = *it == m_filters.back();
			(*it)->process(texture, last);
			if (last)
				break;
			texture = (*it)->getTexture();
		}
	}
	else
		m_hdr.process(m_light_accumulator.getTexture());
}

const float& DeferredRenderer::getExposure() const
{
	return m_hdr.getExposure();
}

void DeferredRenderer::setExposure(const float& exposure)
{
	m_hdr.setExposure(exposure);
}
