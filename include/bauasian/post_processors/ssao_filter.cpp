#include "ssao_filter.hpp"


using bauasian::SSAOFilter;

SSAOFilter::SSAOFilter(const glm::uvec2& size)
		: AreaFilter(size, "post_processing/ssao_fs.glsl", GL_RGB)
{

}
