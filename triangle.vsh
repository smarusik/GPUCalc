attribute highp vec4 pos;
uniform highp mat4 qt_Matrix;
uniform highp mat4 transform;
uniform highp vec4 offset;

void main(void)
{
    vec4 trPos=transform*pos+offset;
    gl_Position = qt_Matrix*trPos;
}
