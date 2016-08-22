#ifndef MOSAICVIEW_H
#define MOSAICVIEW_H

#include <QtQuick/QQuickItem>
#include <QtQuick/QQuickWindow>
#include <memory>

class MoMosaicModel;
class MoMosaicViewRenderer;


class MoMosaicView : public QQuickItem {
    Q_OBJECT
public:
    MoMosaicView();
    ~MoMosaicView();
    std::shared_ptr<MoMosaicModel> getModel() const;

signals:

public slots:
    void setModel(std::shared_ptr<MoMosaicModel> model);
    void sync();
    void cleanup();

private slots:
    void handleWindowChanged(QQuickWindow *win);

private:
    bool initialized;
    MoMosaicViewRenderer* renderer_;

    void initGL();

    Q_DISABLE_COPY(MoMosaicView)
};

#endif // MOSAICVIEW_H
