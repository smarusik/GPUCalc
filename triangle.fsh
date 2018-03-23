uniform lowp vec4 color;
uniform lowp float qt_Opacity;

void main(void)
{
    gl_FragColor = color * qt_Opacity;
}
