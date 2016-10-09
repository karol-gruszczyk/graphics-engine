#include "basic_material_buffer.hpp"


using bauasian::BasicMaterialBuffer;

BasicMaterialBuffer& BasicMaterialBuffer::getInstance()
{
	static BasicMaterialBuffer instance;
	return instance;
}

BasicMaterialBuffer::BasicMaterialBuffer()
		: UniformBuffer(sizeof(GlslBasicMaterial), UniformBuffer::BASIC_MATERIAL)
{}
