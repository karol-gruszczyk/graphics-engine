#include "screen_quad.hpp"


using bauasian::ScreenQuad;

ScreenQuad::ScreenQuad()
		: Drawable(GL_TRIANGLE_STRIP, 4)
{
	GLfloat vertices[][2][2] =
			{
					{{ 1.f,  -1.f }, { 1.f, 0.f }},  // bottom - right
					{{ 1.f,  1.f },  { 1.f, 1.f }},  // top - right
					{{ -1.f, -1.f }, { 0.f, 0.f }},  // bottom - left
					{{ -1.f, 1.f },  { 0.f, 1.f }},  // top - left
			};

	updateVertexBuffer(sizeof(vertices), vertices, { 4 }, GL_STATIC_DRAW);
}
