attribute highp vec4 pos;
attribute highp vec2 texturePos;
uniform highp mat4 qt_Matrix;
varying highp vec2 vTexCoord;

void main(void)
{
    vTexCoord=texturePos;
    gl_Position = qt_Matrix*pos;
}
