#version 460

layout(location = 0) in vec3 fColor;

layout(location = 0) out vec4 outColor;

layout(push_constant) uniform Push {
    mat2 transform;
    vec2 offset;
    vec3 color;
} push;

void main() {
    if (push.color == vec3(0.0)) {
        outColor = vec4(fColor, 1.0);
    } else {
        outColor = vec4(push.color, 1.0);
    }
}