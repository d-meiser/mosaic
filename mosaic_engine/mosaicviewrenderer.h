#ifndef MOMOSAICVIEWRENDERER_H
#define MOMOSAICVIEWRENDERER_H

#include <QObject>
#include <QQuickFramebufferObject>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <mosaicmodel.h>

#include <memory>


class MoMosaicModel;
class QQuickWindow;


class MoMosaicViewRenderer :
        public QQuickFramebufferObject::Renderer,
        protected QOpenGLFunctions
{
public:
    MoMosaicViewRenderer();
    ~MoMosaicViewRenderer();

    void render() Q_DECL_OVERRIDE;
    void synchronize(QQuickFramebufferObject* item) Q_DECL_OVERRIDE;
    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) Q_DECL_OVERRIDE;

    void setModel(std::shared_ptr<MoMosaicModel> model);
    MoMosaicModel getModel() const;
    void setViewportSize(const QSize &size);
    void setWindow(QQuickWindow *window);


public slots:
    void setShowOutlines(bool yesNo);
    bool showOutlines() const;

private:
    bool showOutlines_;
    std::unique_ptr<QOpenGLShaderProgram> program_;
    QSize viewportSize_;
    QQuickWindow *window_;

    MoMosaicModel model_;

    std::vector<float> xH_;
    std::vector<float> yH_;
    std::vector<float> zH_;
    std::vector<float> widths_;
    std::vector<float> heights_;

    int xD_;
    int yD_;
    int zD_;

    void initGL();
    void initShaders();
    QString vshaderFileName() const;
    QString fshaderFileName() const;
};

#endif // MOMOSAICVIEWRENDERER_H
