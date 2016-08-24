#include <maindriver.h>
#include <QDir>
#include <QAbstractListModel>
#include <QString>
#include <QDebug>
#include <QThread>
#include <algorithm>

#include <tile.h>
#include <targetimage.h>
#include <sourceimages.h>
#include <mosaicmodel.h>
#include <evolutionrunner.h>
#include <mosaicupdatedelay.h>


MoMainDriver::MoMainDriver(QObject *parent) :
    QObject(parent),
    sourceImages_(0) {
}

MoMainDriver::~MoMainDriver() {
    shutDownEvolutionRunner();
}

static MoTile loadTile(QString fn) {
    qDebug() << "loadTile(fn), fn == " << fn;
    QImage image(fn);
    MoTile tile(image);
    return tile;
}

void MoMainDriver::setSourceImages(QAbstractListModel *sourceImages) {
    sourceImages_ = sourceImages;
}

void MoMainDriver::start(QUrl targetUrl) {
    QImage img(QDir::toNativeSeparators(targetUrl.toLocalFile()));
    MoTargetImage targetImage(img, img.size());

    std::vector<QString> inputFiles = getFileNames(sourceImages_);
    std::vector<MoTile> tiles;
    std::transform(inputFiles.cbegin(), inputFiles.cend(),
                   std::back_inserter(tiles),
                   loadTile);

    evolution_.constructInitialState(targetImage, tiles);
    evolution_.addUpdate(std::unique_ptr<MoMosaicUpdate>(
                             new MoMosaicUpdateDelay));

    if (evolutionRunner_) {
        evolutionRunner_->terminate();
    }
    evolutionRunner_.reset(new MoEvolutionRunner);
    evolutionRunner_->setEvolution(&evolution_);
    connect(evolutionRunner_.get(), &MoEvolutionRunner::modelChanged,
            this, &MoMainDriver::setCurrentModel);
    evolutionRunner_->start();
}

void MoMainDriver::shutDownEvolutionRunner()
{
    if (evolutionRunner_) {
        evolutionRunner_->stop();
        if (!evolutionRunner_->wait(100)) {
            qDebug() << "evolutionRunner_ failed to shut down in 0.1 s. Terminating.";
            evolutionRunner_->terminate();
        } else {
            qDebug() << "evolutionRunner_ successfully shut down in 0.1 s.";
        }
        evolutionRunner_.reset(nullptr);
    }
}

void MoMainDriver::stop() {
    shutDownEvolutionRunner();
}

std::vector<QString> MoMainDriver::getFileNames(
        QAbstractListModel *inputImages) const {
    std::vector<QString> fileNames;
    fileNames.reserve(inputImages->rowCount());
    for (int i = 0; i < inputImages->rowCount(); ++i) {
        QUrl url = inputImages->data(inputImages->index(i),
                                     MoSourceImages::FileNameRole).toUrl();
        QString fn = url.toLocalFile();
        if (QFile(fn).exists()) {
            QString nativeFilename = QDir::toNativeSeparators(fn);
            fileNames.push_back(nativeFilename.toUtf8().constData());
        } else {
        }
    }
    return fileNames;
}

std::shared_ptr<MoMosaicModel> MoMainDriver::getCurrentModel() {
    return currentModel_;
}

void MoMainDriver::setCurrentModel(std::shared_ptr<MoMosaicModel> newModel) {
    qDebug() << "in MoMainDriver::setCurrentModel.";
    currentModel_ = newModel;
    emit modelChanged(newModel);
}
