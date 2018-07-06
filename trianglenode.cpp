#include "trianglenode.h"

#include <QtGui/QColor>
#include <QtQuick/QSGSimpleMaterial>
#include <cmath>

struct TraceMaterial
{
    QColor color;
    QMatrix4x4 matrix;
    QVector4D offset;
};

class TraceShader : public QSGSimpleMaterialShader<TraceMaterial>
{
    QSG_DECLARE_SIMPLE_SHADER(TraceShader, TraceMaterial)

public:
    TraceShader() : id_color(-1)
    {
        setShaderSourceFile(QOpenGLShader::Vertex, ":/triangle.vsh");
        setShaderSourceFile(QOpenGLShader::Fragment, ":/triangle.fsh");
    }

    QList<QByteArray> attributes() const {  return QList<QByteArray>() << "pos"; }

    void updateState(const TraceMaterial *m, const TraceMaterial *) {
        program()->setUniformValue(id_color, m->color);
        program()->setUniformValue(id_matrix, m->matrix);
        program()->setUniformValue(id_offset, m->offset);
    }

    void resolveUniforms() {
        id_color = program()->uniformLocation("color");
        id_matrix = program()->uniformLocation("transform");
        id_offset = program()->uniformLocation("offset");
    }

private:
    int id_color;
    int id_matrix;
    int id_offset;
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

TriangleNode::TriangleNode(const QColor &color)
    : m_geometry(attributes(), 0)
{
    setGeometry(&m_geometry);
    m_geometry.setDrawingMode(GL_QUADS);
    m_geometry.setLineWidth(2);

    QSGSimpleMaterial<TraceMaterial> *m = TraceShader::createMaterial();
    m->state()->color = color;
    m->state()->matrix=QMatrix4x4(1,0,0,0,
                                  0,1,0,0,
                                  0,0,1,0,
                                  0,0,0,1);
    m->state()->offset=QVector4D(0,0,0,0);

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
    m_geometry.allocate(4);

    float x = bounds.x();
    float y = bounds.y();
    float w = bounds.width();
    float h = bounds.height();

    LineVertex *v = (LineVertex *) m_geometry.vertexData();

    v[0].set(x, y);
    v[1].set(x, y+h);
    v[2].set(x+w, y+h);
    v[3].set(x+w, y);

    markDirty(QSGNode::DirtyGeometry);
}
