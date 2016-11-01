#include "ssao_blur.hpp"


using bauasian::SSAOBlur;
using bauasian::Texture;

SSAOBlur::SSAOBlur(const glm::uvec2& size)
		: AreaFilter(size, "post_processing/ssao_blur_fs.glsl", GL_RED)
{}
