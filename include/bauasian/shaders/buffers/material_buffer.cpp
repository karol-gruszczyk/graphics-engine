#include "material_buffer.hpp"


using bauasian::MaterialBuffer;

MaterialBuffer::MaterialBuffer()
	: UniformBuffer(sizeof(GlslMaterial), UniformBuffer::MATERIAL)
{}

MaterialBuffer& MaterialBuffer::getInstance()
{
	static MaterialBuffer instance;
	return instance;
}
