#include "deferred_renderer.hpp"
#include "bauasian/lights/directional_light.hpp"


using bauasian::DeferredRenderer;

DeferredRenderer::DeferredRenderer(const glm::uvec2 size)
		: m_depth_buffer(std::make_shared<RenderBuffer>(size)),
		  m_geometry_renderer(size, m_depth_buffer), m_light_accumulator(size, m_depth_buffer),
		  m_hdr(size), m_bloom(size)
{
	SizeMixin::setSize(size);
}

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

void DeferredRenderer::render(const Scene3D* scene) const
{
	for (const auto& light : scene->getDirectionalLights())
		light->updateShadowMap(scene);

	glViewport(0, 0, m_size.x, m_size.y);

	glEnable(GL_DEPTH_TEST);
	m_geometry_renderer.render(scene);
	glDisable(GL_DEPTH_TEST);

	m_light_accumulator.render(scene);

	if (m_bloom_enabled)
		m_bloom.process();

	m_light_accumulator.getFrameBuffer().bind();  // render sky-box after bloom
	glEnable(GL_DEPTH_TEST);
	scene->renderSkyBox();
	glDisable(GL_DEPTH_TEST);

	if (m_post_processors.size())
	{
		m_hdr.process();
		for (auto it = m_post_processors.begin(); it != --m_post_processors.end(); ++it)
		{
			(*it)->process();
		}
		m_post_processors.back()->processToScreen();
	}
	else
		m_hdr.processToScreen();
}

void DeferredRenderer::enableSSAO()
{
	m_light_accumulator.enableSSAO();
}

void DeferredRenderer::disableSSAO()
{
	m_light_accumulator.disableSSAO();
}
