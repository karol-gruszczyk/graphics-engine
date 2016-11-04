#include "../bindings.glsl"

layout(std140, binding = BUFFER_MATRICES_BINDING) uniform MatricesBuffer
{
    mat4 model_matrix;
    mat4 normal_matrix;
};
