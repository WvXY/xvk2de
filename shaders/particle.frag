#version 460

layout(push_constant) uniform Particle {
  vec2 position;
  float life;
  float size;
  vec3 color;
} p;

layout(location = 0) out vec4 fragColor;

void main() {
  vec2 pc = (gl_PointCoord - vec2(0.5)) * p.size;
  if (length(pc) > 0.5) { discard; }
  fragColor = vec4(p.color,  1.0);
}
