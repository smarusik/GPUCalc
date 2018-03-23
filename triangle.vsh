attribute highp vec4 pos;

uniform highp mat4 qt_Matrix;

void main(void)
{
    vec4 adjustedPos = pos;
    gl_Position = qt_Matrix * adjustedPos;
}
