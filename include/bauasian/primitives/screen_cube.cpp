#include "screen_cube.hpp"


using bauasian::ScreenCube;

ScreenCube::ScreenCube()
		: IndexedDrawable(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT)
{
	GLfloat vertices[][3] = {
			{ -1.f, -1.f, -1.f },
			{ -1.f, -1.f, 1.f },
			{ 1.f,  -1.f, 1.f },
			{ 1.f,  -1.f, -1.f },

			{ -1.f, 1.f,  -1.f },
			{ -1.f, 1.f,  1.f },
			{ 1.f,  1.f,  1.f },
			{ 1.f,  1.f,  -1.f },
	};
	GLushort indices[] = {
			// left
			5, 1, 0, 0, 4, 5,
			// right
			3, 2, 6, 3, 6, 7,
	        // front
			7, 4, 0, 3, 7, 0,
			// back
			1, 6, 2, 5, 6, 1,
	        // up
	        6, 5, 4, 7, 6, 4,
			// bottom
			0, 1, 3, 1, 2, 3,
	};

	updateVertexBuffer(sizeof(vertices), vertices, { 3 }, GL_STATIC_DRAW);
	updateIndexBuffer(sizeof(indices), indices, GL_STATIC_DRAW);
}
