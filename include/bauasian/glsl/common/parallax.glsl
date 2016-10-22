vec2 getParallaxTextureCoords(sampler2D displacement_texture, vec2 texture_coord, vec3 view_dir)
{
    const float min_layers = 8;
    const float max_layers = 16;
    const float height_scale = 0.1f;

    float num_layers = mix(max_layers, min_layers, abs(dot(vec3(0.f, 0.f, 1.f), view_dir)));
    float layer_depth = 1.f / num_layers;
    float current_layer_depth = 0.f;

    vec2 p = view_dir.xy * height_scale;
    vec2 delta_texture_coord = p / num_layers;
    vec2 current_texture_coord = texture_coord;
    float previous_depth_map_value;
    float current_depth_map_value = texture(displacement_texture, current_texture_coord).r;
    while (current_layer_depth < current_depth_map_value)
    {
        current_texture_coord -= delta_texture_coord;
        previous_depth_map_value = current_depth_map_value;
        current_depth_map_value = texture(displacement_texture, current_texture_coord).r;
        current_layer_depth += layer_depth;
    }

    vec2 previous_texture_coord = current_texture_coord + delta_texture_coord;

    float before_depth = previous_depth_map_value - current_layer_depth + layer_depth;
    float after_depth = current_depth_map_value - current_layer_depth;

    float weight = after_depth / (after_depth - before_depth);
    return previous_texture_coord * weight + current_texture_coord * (1.f - weight);
}
