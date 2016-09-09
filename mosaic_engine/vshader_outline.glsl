#version 130
in float x;
in float y;
in float width;
in float height;
in float rotation;
uniform float targetWidth = 1.0f;
uniform float targetHeight = 1.0f;
uniform float numTiles = 10.0f;

const vec2 pos[] = vec2[4](
  vec2(-0.5f,  0.5f),
  vec2(-0.5f, -0.5f),
  vec2( 0.5f,  0.5f),
  vec2( 0.5f, -0.5f)
);

void main(void)
{
    vec2 offset = pos[gl_VertexID];
    float c = cos(rotation);
    float s = sin(rotation);
    float x_ = (x + width * offset.x) / targetWidth;
    float y_ = (y + height * offset.y) / targetHeight;
    gl_Position = vec4(c * x_ - s * y_,
                       s * x_ + c * y_,
                       (gl_InstanceID - numTiles) / numTiles,
                       1.0f);
}
