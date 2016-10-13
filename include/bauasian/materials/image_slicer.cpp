#include "image_slicer.hpp"

#include <tuple>
#include <cstring>


using bauasian::ImageSlicer;

ImageSlicer::ImageSlicer(const glm::uvec2& image_size, unsigned char* image_pixels, const unsigned& bytes_per_pixel)
		: m_image_size(image_size), m_image_pixels(image_pixels), m_bytes_per_pixel(bytes_per_pixel)
{}

ImageSlicer::~ImageSlicer()
{
	for (auto& ptr : m_ptrs)
		delete ptr;
}

std::tuple<std::vector<glm::uvec2>, std::vector<unsigned char*>> ImageSlicer::getCubeTextureFaces()
{
	std::vector<glm::uvec2> sizes;
	std::vector<unsigned char*> pixel_ptrs;
	glm::vec2 face_size(m_image_size.x / 4, m_image_size.y / 3);

	pixel_ptrs.push_back(getSubImage(face_size, { 2 * face_size.x, 1 * face_size.y }));  // right
	pixel_ptrs.push_back(getSubImage(face_size, { 0 * face_size.x, 1 * face_size.y }));  // left
	pixel_ptrs.push_back(getSubImage(face_size, { 1 * face_size.x, 0 * face_size.y }));  // up
	pixel_ptrs.push_back(getSubImage(face_size, { 1 * face_size.x, 2 * face_size.y }));  // down
	pixel_ptrs.push_back(getSubImage(face_size, { 1 * face_size.x, 1 * face_size.y }));  // front
	pixel_ptrs.push_back(getSubImage(face_size, { 3 * face_size.x, 1 * face_size.y }));  // back

	for (unsigned i = 0; i < pixel_ptrs.size(); i++)
		sizes.push_back(face_size);
	return std::make_tuple(sizes, pixel_ptrs);
}

unsigned char* ImageSlicer::getSubImage(const glm::uvec2& sub_image_size, const glm::uvec2& sub_image_position)
{
	assert(sub_image_position.x + sub_image_size.x <= m_image_size.x &&
	       sub_image_position.y + sub_image_size.y <= m_image_size.y);

	const unsigned bytes_per_row = sub_image_size.x * m_bytes_per_pixel;
	unsigned char* sub_image_pixels = new unsigned char[sub_image_size.y * bytes_per_row];

	unsigned char* src_ptr = m_image_pixels + (sub_image_position.x + sub_image_position.y * m_image_size.x)
	                                          * m_bytes_per_pixel;
	for (unsigned row = 0; row < sub_image_size.y; row++)
	{
		std::memcpy(sub_image_pixels + row * bytes_per_row, src_ptr, bytes_per_row);
		src_ptr += row * m_image_size.x * m_bytes_per_pixel;
	}
	m_ptrs.push_back(sub_image_pixels);
	return sub_image_pixels;
}
