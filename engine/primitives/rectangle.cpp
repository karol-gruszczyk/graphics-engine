#include "rectangle.h"


namespace engine
{
	Rectangle::Rectangle(GLfloat width, GLfloat length)
	{
		initialize(width, length);
	}

	void Rectangle::initialize(GLfloat width, GLfloat length)
	{
		m_width = width;
		m_length = length;

		GLfloat vertices[] = {
			0.f, 0.f,
			width, 0.f,
			width, length,
			0.f, length,
		};

		glGenBuffers(1, &m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vao);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	}

	void Rectangle::render()
	{
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, m_vao);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	}
}
