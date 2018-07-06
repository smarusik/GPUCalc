uniform lowp float qt_Opacity;
uniform sampler2D picture;
varying highp vec2 vTexCoord;

void main(void)
{
    lowp vec4 p = texture2D(picture, vTexCoord);
    gl_FragColor = p*qt_Opacity;
}
