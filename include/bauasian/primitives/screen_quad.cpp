#include "screen_quad.hpp"


using bauasian::ScreenQuad;

ScreenQuad::ScreenQuad()
		: Renderable(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT)
{
	GLfloat vertices[] =
			{
					1.f, -1.f, 1.f, 0.f,
					-1.f, -1.f, 0.f, 0.f,
					1.f, 1.f, 1.f, 1.f,
					-1.f, 1.f, 0.f, 1.f
			};
	GLushort indices[] =
			{
					0, 1, 2, 3
			};

	glBindVertexArray(m_vao_id);
	createVertexBuffer(sizeof(vertices), vertices, { 4 }, GL_STATIC_DRAW);
	createIndexBuffer(sizeof(indices), indices);
}
