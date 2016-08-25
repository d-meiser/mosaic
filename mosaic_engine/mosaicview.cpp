#include <mosaicview.h>

#include <QDebug>

#include <mosaicviewrenderer.h>


MoMosaicView::MoMosaicView() :
    renderer_(new MoMosaicViewRenderer) {
    qDebug() << ">>>>>>>>>>> In MoMosaicView ctor";
    connect(this, &QQuickItem::windowChanged,
            this, &MoMosaicView::handleWindowChanged);
}

MoMosaicView::~MoMosaicView() {
}

void MoMosaicView::setModel(std::shared_ptr<MoMosaicModel> model) {
    qDebug() << "In MoMosaicView::setModel.";
    renderer_->setModel(model);
    this->update();
}

std::shared_ptr<MoMosaicModel> MoMosaicView::getModel() const {
    return renderer_->getModel();
}

QQuickFramebufferObject::Renderer *MoMosaicView::createRenderer() const {
    return new MoMosaicViewRenderer;
}

void MoMosaicView::handleWindowChanged(QQuickWindow *win) {
    if (win) {
        connect(win, &QQuickWindow::sceneGraphInvalidated, this, &MoMosaicView::cleanup, Qt::DirectConnection);
        win->setClearBeforeRendering(false);
    }
   qDebug() << "in MoMosaicView::handleWindowChanged";
}

void MoMosaicView::cleanup() {
    renderer_.reset(nullptr);
}
