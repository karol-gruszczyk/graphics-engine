#include "deferred_renderer.hpp"


using bauasian::DeferredRenderer;

DeferredRenderer::DeferredRenderer(const glm::uvec2 size)
		: SizeMixin(size), m_depth_buffer(std::make_shared<RenderBuffer>(size)),
		  m_geometry_renderer(size, m_depth_buffer), m_light_accumulator(size, m_depth_buffer),
		  m_hdr(size), m_bloom(size)
{}

DeferredRenderer::~DeferredRenderer()
{
	for (auto& filter : m_post_processors)
		delete filter;
}

void DeferredRenderer::setSize(const glm::uvec2& size)
{
	SizeMixin::setSize(size);
	m_geometry_renderer.setSize(m_size);
	m_light_accumulator.setSize(m_size);
	m_hdr.setSize(size);
	m_bloom.setSize(size);
	for (auto& filter : m_post_processors)
		filter->setSize(m_size);
}

void DeferredRenderer::addPostProcessor(PostProcessor* post_processor)
{
	m_post_processors.push_back(post_processor);
}

void DeferredRenderer::clearScreen() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void DeferredRenderer::render(Scene3D* scene) const
{
	glViewport(0, 0, m_size.x, m_size.y);

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

	m_bloom.process(m_light_accumulator.getTexture());

	m_light_accumulator.getFrameBuffer().bind();
	glEnable(GL_DEPTH_TEST);
	scene->renderSkyBox();
	glDisable(GL_DEPTH_TEST);


	if (m_post_processors.size())
	{
		m_hdr.process(m_light_accumulator.getTexture(), m_bloom.getTexture());
		const Texture* texture = m_hdr.getTexture();
		for (auto it = m_post_processors.begin(); it != --m_post_processors.end(); ++it)
		{
			(*it)->process(texture);
			texture = (*it)->getTexture();
		}
		m_post_processors.back()->processToScreen(texture);
	}
	else
		m_hdr.processToScreen(m_light_accumulator.getTexture(), m_bloom.getTexture());
}

const float& DeferredRenderer::getExposure() const
{
	return m_hdr.getExposure();
}

void DeferredRenderer::setExposure(const float& exposure)
{
	m_hdr.setExposure(exposure);
}
