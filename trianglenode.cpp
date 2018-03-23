#include "trianglenode.h"

#include <QtGui/QColor>

#include <QtQuick/QSGSimpleMaterial>

struct LineMaterial
{
    QColor color;
};

class LineShader : public QSGSimpleMaterialShader<LineMaterial>
{
    QSG_DECLARE_SIMPLE_SHADER(LineShader, LineMaterial)

public:
    LineShader() : id_color(-1)
    {
        setShaderSourceFile(QOpenGLShader::Vertex, ":/triangle.vsh");
        setShaderSourceFile(QOpenGLShader::Fragment, ":/triangle.fsh");
    }

    QList<QByteArray> attributes() const {  return QList<QByteArray>() << "pos"; }

    void updateState(const LineMaterial *m, const LineMaterial *) {
        program()->setUniformValue(id_color, m->color);
    }

    void resolveUniforms() {
        id_color = program()->uniformLocation("color");
    }

private:
    int id_color;
};

struct LineVertex {
    float x;
    float y;
    inline void set(float xx, float yy) { x = xx; y = yy;}
};

static const QSGGeometry::AttributeSet &attributes()
{
    static QSGGeometry::Attribute attr[] = {
        QSGGeometry::Attribute::create(0, 2, GL_FLOAT, true)
    };
    static QSGGeometry::AttributeSet set = { 1, 2 * sizeof(float), attr };
    return set;
}

TriangleNode::TriangleNode(float size, const QColor &color)
    : m_geometry(attributes(), 0)
{
    setGeometry(&m_geometry);
    m_geometry.setDrawingMode(GL_TRIANGLE_STRIP);

    QSGSimpleMaterial<LineMaterial> *m = LineShader::createMaterial();
    m->state()->color = color;
    m->setFlag(QSGMaterial::Blending);
    setMaterial(m);
    setFlag(OwnsMaterial);
}

/*
 * Assumes that samples have values in the range of 0 to 1 and scales them to
 * the height of bounds. The samples are stretched out horizontally along the
 * width of the bounds.
 *
 * The position of each pair of points is identical, but we use the third value
 * "t" to shift the point up or down and to add antialiasing.
 */
void TriangleNode::updateGeometry(const QRectF &bounds)
{
    m_geometry.allocate(3);

    float x = bounds.x();
    float y = bounds.y();
    float w = bounds.width();
    float h = bounds.height();

    LineVertex *v = (LineVertex *) m_geometry.vertexData();

    v[0].set(x+10, y+10);
    v[1].set(x+10,h-10);
    v[2].set(w-10,h-10);

    markDirty(QSGNode::DirtyGeometry);
}
