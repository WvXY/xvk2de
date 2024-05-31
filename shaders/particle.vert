#version 460

layout(push_constant) uniform Particle {
  vec2 position;
  float life;
  float size;
  vec3 color;
} p;

void main() {
  gl_Position = vec4(p.position, 0.0, 1.0);
}
