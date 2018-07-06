#ifndef TEXTURENODE_H
#define TEXTURENODE_H

#include <QSGNode>
#include <QSGTextureProvider>
#include <QSGSimpleMaterialShader>
#include <QOpenGLFunctions>
#include <QPointer>

struct TextureData
{
    QSGTexture *texture;
};

class TextureNodeMaterial: public QSGSimpleMaterialShader<TextureData>
{
    QSG_DECLARE_SIMPLE_SHADER(TextureNodeMaterial, TextureData)

public:
    TextureNodeMaterial()
    {
        setShaderSourceFile(QOpenGLShader::Vertex, ":/texture.vsh");
        setShaderSourceFile(QOpenGLShader::Fragment, ":/texture.fsh");
    }

    QList<QByteArray> attributes() const
    {
        return QList<QByteArray>() << "pos"<<"texturePos";
    }

    virtual void updateState(const TextureData *state, const TextureData *oldState) override
    {
        if(state!=oldState)
        {
            QOpenGLFunctions *f=QOpenGLContext::currentContext()->functions();

            f->glActiveTexture(GL_TEXTURE0);
            state->texture->bind();
        }
    }

    void resolveUniforms()
    {
        program()->setUniformValue("picture",0);
    }
};

class TextureNode : public QSGGeometryNode
{
public:
    TextureNode(QSGTexture *tp):
        geom(new QSGGeometry(QSGGeometry::defaultAttributes_TexturedPoint2D(),0))
    {
        mat=TextureNodeMaterial::createMaterial();
        mat->state()->texture=tp;
        mat->setFlag(QSGMaterial::Blending);
        setMaterial(mat);
        setFlag(QSGNode::OwnsMaterial);
        setGeometry(geom);
        geom->setDrawingMode(GL_QUADS);
        setFlag(QSGNode::OwnsGeometry);
    }

    void setRect(const QRectF &rect, const QRectF &rect1)
    {
        geom->allocate(8);
        QSGGeometry::TexturedPoint2D *vertices=(QSGGeometry::TexturedPoint2D *)geom->vertexData();

        qreal x0,y0,x1,y1;
        rect.getCoords(&x0,&y0,&x1,&y1);

        vertices[0].set(x0,y0,0,0);
        vertices[1].set(x1,y0,1,0);
        vertices[2].set(x1,y1,1,1);
        vertices[3].set(x0,y1,0,1);

        rect1.getCoords(&x0,&y0,&x1,&y1);

        vertices[4].set(x0,y0,0,0);
        vertices[5].set(x1,y0,1,0);
        vertices[6].set(x1,y1,1,1);
        vertices[7].set(x0,y1,0,1);


        markDirty(QSGNode::DirtyGeometry);
    }

    QRectF viewport;
    QSGSimpleMaterial<TextureData> *mat;
    QSGGeometry *geom;
};

#endif // TEXTURENODE_H
