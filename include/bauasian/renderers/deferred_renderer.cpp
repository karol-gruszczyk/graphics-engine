#include "deferred_renderer.hpp"
#include "post_processors/hdr.hpp"
#include "bauasian/shaders/buffers/model_matrices_buffer.hpp"
#include "bauasian/shaders/buffers/scene_buffer.hpp"
#include "bauasian/shaders/buffers/directional_light_buffer.hpp"
#include "bauasian/shaders/buffers/point_light_buffer.hpp"
#include "bauasian/shaders/buffers/spot_light_buffer.hpp"


#define ALBEDO_BUFFER 0
#define SPECULAR_BUFFER 1
#define NORMAL_BUFFER 2
#define POSITION_BUFFER 3

using bauasian::DeferredRenderer;

DeferredRenderer::DeferredRenderer(const glm::uvec2 size)
		: SizeInterface(size)
{
	m_albedo_buffer = new Texture(GL_RGB, GL_RGB, size);
	m_specular_buffer = new Texture(GL_RGBA, GL_RGBA, size);
	m_normal_buffer = new Texture(GL_RGB16F, GL_RGB, size);
	m_position_buffer = new Texture(GL_RGB16F, GL_RGB, size);
	m_frame_buffer = new FrameBuffer({ m_albedo_buffer, m_specular_buffer, m_normal_buffer, m_position_buffer },
									 new RenderBuffer(), size);
	auto vs = std::make_unique<Shader>("deferred_rendering/gbuffer_vs.glsl", Shader::VERTEX_SHADER);
	auto fs = std::make_unique<Shader>("deferred_rendering/gbuffer_fs.glsl", Shader::FRAGMENT_SHADER);
	m_geometry_shader = new ShaderProgram({ vs.get(), fs.get() });

	Material::setShaderLocations(m_geometry_shader);
	ModelMatricesBuffer::getInstance().attachUniformBlock(m_geometry_shader, "ModelMatrices");
	SceneBuffer::getInstance().attachUniformBlock(m_geometry_shader, "SceneBuffer");

	initDirectionalLightShader();
	initPointLightShader();
	initSpotLightShader();

	m_screen_quad = new ScreenQuad();
	m_sphere_volume = new SphereVolume();
	m_cone_volume = new ConeVolume();

	addFilter(new HDR());
}

DeferredRenderer::~DeferredRenderer()
{
	delete m_frame_buffer;
	delete m_geometry_shader;
	delete m_dir_light_shader;
	delete m_point_light_shader;
	delete m_spot_light_shader;
	delete m_screen_quad;
	delete m_sphere_volume;
	for (auto& filter : m_filters)
		delete filter;
}

void DeferredRenderer::setSize(const glm::uvec2& size)
{
	SizeInterface::setSize(size);
	m_frame_buffer->setSize(m_size);
	for (auto& filter : m_filters)
		filter->setSize(m_size);
	m_point_light_shader->setUniform(m_location_point_light_screen_size, m_size);
	m_spot_light_shader->setUniform(m_location_spot_light_screen_size, m_size);
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
	geometryPass(scene);

	auto it = m_filters.begin();

	(*it)->bindForRendering();
	m_frame_buffer->copyBuffer(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT, (*it)->getFrameBufferId());

	renderLighting(scene);

	while (true)
	{
		const auto& next = std::next(it);
		if (next == m_filters.end())
			break;

		(*it)->renderToFrameBuffer((*next)->getFrameBufferId());
		it = next;
	}

	(*it)->renderToFrameBuffer();
}

void DeferredRenderer::initDirectionalLightShader()
{
	auto vs = std::make_unique<Shader>("deferred_rendering/directional_vs.glsl", Shader::VERTEX_SHADER);
	auto fs = std::make_unique<Shader>("deferred_rendering/directional_fs.glsl", Shader::FRAGMENT_SHADER);
	m_dir_light_shader = new ShaderProgram({ vs.get(), fs.get() });
	SceneBuffer::getInstance().attachUniformBlock(m_dir_light_shader, "SceneBuffer");
	DirectionalLightBuffer::getInstance().attachUniformBlock(m_dir_light_shader, "DirectionalLightBuffer");
	initLightShaderUniformLocation(m_dir_light_shader);
}

void DeferredRenderer::initPointLightShader()
{
	auto vs = std::make_unique<Shader>("deferred_rendering/point_vs.glsl", Shader::VERTEX_SHADER);
	auto fs = std::make_unique<Shader>("deferred_rendering/point_fs.glsl", Shader::FRAGMENT_SHADER);
	m_point_light_shader = new ShaderProgram({ vs.get(), fs.get() });
	m_location_point_light_projection_view_matrix = m_point_light_shader->getUniformLocation("projection_view_matrix");
	m_location_point_light_screen_size = m_point_light_shader->getUniformLocation("screen_size");
	SceneBuffer::getInstance().attachUniformBlock(m_point_light_shader, "SceneBuffer");
	PointLightBuffer::getInstance().attachUniformBlock(m_point_light_shader, "PointLightBuffer");
	initLightShaderUniformLocation(m_point_light_shader);
	m_point_light_shader->setUniform(m_location_point_light_screen_size, m_size);
}

void DeferredRenderer::initSpotLightShader()
{
	auto vs = std::make_unique<Shader>("deferred_rendering/spot_vs.glsl", Shader::VERTEX_SHADER);
	auto fs = std::make_unique<Shader>("deferred_rendering/spot_fs.glsl", Shader::FRAGMENT_SHADER);
	m_spot_light_shader = new ShaderProgram({ vs.get(), fs.get() });
	m_location_spot_light_screen_size = m_spot_light_shader->getUniformLocation("screen_size");
	m_location_spot_light_projection_view_matrix = m_spot_light_shader->getUniformLocation("projection_view_matrix");
	SceneBuffer::getInstance().attachUniformBlock(m_spot_light_shader, "SceneBuffer");
	SpotLightBuffer::getInstance().attachUniformBlock(m_spot_light_shader, "SpotLightBuffer");
	initLightShaderUniformLocation(m_spot_light_shader);
	m_spot_light_shader->setUniform(m_location_spot_light_screen_size, m_size);
}

void DeferredRenderer::initLightShaderUniformLocation(ShaderProgram* shader) const
{
	shader->setUniform(shader->getUniformLocation("albedo_buffer"), ALBEDO_BUFFER);
	shader->setUniform(shader->getUniformLocation("specular_buffer"), SPECULAR_BUFFER);
	shader->setUniform(shader->getUniformLocation("normal_buffer"), NORMAL_BUFFER);
	shader->setUniform(shader->getUniformLocation("position_buffer"), POSITION_BUFFER);
}

void DeferredRenderer::geometryPass(Scene3D* scene) const
{
	m_frame_buffer->bind();
	m_frame_buffer->clear();
	m_geometry_shader->use();
	glEnable(GL_STENCIL_TEST);
	glStencilMask(0xFF);
	glClear(GL_STENCIL_BUFFER_BIT);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	scene->render();
}

void DeferredRenderer::renderLighting(Scene3D* scene) const
{
	m_albedo_buffer->bind(ALBEDO_BUFFER);
	m_specular_buffer->bind(SPECULAR_BUFFER);
	m_normal_buffer->bind(NORMAL_BUFFER);
	m_position_buffer->bind(POSITION_BUFFER);

	glStencilFunc(GL_EQUAL, 1, 0xFF);
	glStencilMask(0x00);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);  // setup additive blending
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);

	directionalLightPass(scene);

	glCullFace(GL_FRONT);
	pointLightPass(scene);
	spotLightPass(scene);
	glCullFace(GL_BACK);

	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);  // enable writing to depth buffer
	glEnable(GL_DEPTH_TEST);

	glDisable(GL_STENCIL_TEST);

	scene->renderSkyBox();
}

void DeferredRenderer::directionalLightPass(Scene3D* scene) const
{
	m_dir_light_shader->use();
	for (const auto& light : scene->getDirectionalLights())
	{
		DirectionalLightBuffer::getInstance().setData(light);
		m_screen_quad->render();
	}
}

void DeferredRenderer::pointLightPass(Scene3D* scene) const
{
	m_point_light_shader->use();
	m_point_light_shader->setUniform(m_location_point_light_projection_view_matrix,
									 scene->getCamera()->getProjectionViewMatrix());
	for (const auto& light : scene->getPointLights())
	{
		PointLightBuffer::getInstance().setData(light);
		m_sphere_volume->render();
	}
}

void DeferredRenderer::spotLightPass(Scene3D* scene) const
{
	m_spot_light_shader->use();
	m_spot_light_shader->setUniform(m_location_spot_light_projection_view_matrix,
									scene->getCamera()->getProjectionViewMatrix());
	for (const auto& light : scene->getSpotLights())
	{
		SpotLightBuffer::getInstance().setData(light);
		m_cone_volume->render();
	}
}
