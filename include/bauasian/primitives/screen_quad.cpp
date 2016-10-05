#include "screen_quad.hpp"


using bauasian::ScreenQuad;

ScreenQuad::ScreenQuad()
		: Entity()
{
	GLfloat vertices[] =
			{
					-1.f, -1.f, 0.f, 0.f,
					1.f, -1.f, 1.f, 0.f,
					1.f, 1.f, 1.f, 1.f,
					-1.f, 1.f, 0.f, 1.f
			};
	GLushort indices[] =
			{
					1, 0, 2, 3
			};

	setupRendering(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT);

	glBindVertexArray(m_vao_id);
	createBufferObject(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);
	glEnableVertexAttribArray(0);

	createBufferObject(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
}
