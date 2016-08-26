#include "mosaicmodel.h"

#include <stdexcept>
#include <QtGlobal>


MoMosaicModel::MoMosaicModel() : size_(0), targetImage_(QImage(), QSize()) {
}

static float computeTileArea(const std::vector<MoTile>& tiles) {
    float area = 0.0f;
    for (auto t : tiles) {
        const QImage* i = t.getImage();
        area += i->width() * i->height();
    }
    return area;
}

void MoMosaicModel::constructInitialState(const MoTargetImage& targetImage,
                                          const std::vector<MoTile>& tiles) {
    targetImage_ = targetImage;
    tiles_ = tiles;
    size_ = tiles.size();

    x_.resize(tiles.size());
    std::fill(x_.begin(), x_.end(), 0.0f);

    y_.resize(tiles.size());
    std::fill(y_.begin(), y_.end(), 0.0f);

    rotations_.resize(tiles.size());
    std::fill(rotations_.begin(), rotations_.end(), 0.0f);

    float totalTileArea = computeTileArea(tiles_);
    QSize targetSize = targetImage.getSize();
    float targetArea = targetSize.width() * targetSize.height();
    scales_.resize(tiles.size());
    std::fill(scales_.begin(), scales_.end(),
              1.2f * targetArea / totalTileArea);
}

void MoMosaicModel::resize(int size) {
    size_ = size;
    x_.resize(size);
    y_.resize(size);
    rotations_.resize(size);
    scales_.resize(size);
}

int MoMosaicModel::size() const {
    return size_;
}

void MoMosaicModel::getWidths(float *widthsBegin) const {
    int n = tiles_.size();
    for (int i = 0; i < n; ++i) {
        // TODO: figure out what the right dimensions are here
        // Currently we do screen space?
        widthsBegin[i] = scales_[i] * tiles_[i].getImage()->width();
    }
}

void MoMosaicModel::getHeights(float *heightsBegin) const {
    int n = tiles_.size();
    for (int i = 0; i < n; ++i) {
        // TODO: figure out what the right dimensions are here
        // Currently we do screen space?
        heightsBegin[i] = scales_[i] * tiles_[i].getImage()->height();
    }
}

void MoMosaicModel::setXCoords(const float *xBegin, const float *xEnd) {
    if (std::distance(xBegin, xEnd) != size_) {
        throw std::runtime_error(
                    "Number of elements in [xBegin, xEnd) "
                    "doesn't match size of MoMosaicModel.");
    }
    std::copy(xBegin, xEnd, x_.begin());
}

void MoMosaicModel::getXCoords(float *xBegin) const {
    std::copy(x_.cbegin(), x_.cend(), xBegin);
}


void MoMosaicModel::setYCoords(const float *yBegin, const float *yEnd) {
    if (std::distance(yBegin, yEnd) != size_) {
        throw std::runtime_error(
                    "Number of elements in [yBegin, yEnd) "
                    "doesn't match size of MoMosaicModel.");
    }
    std::copy(yBegin, yEnd, y_.begin());
}

void MoMosaicModel::getYCoords(float *yBegin) const {
    std::copy(y_.cbegin(), y_.cend(), yBegin);
}

void MoMosaicModel::setRotations(const float *rotationsBegin,
                                 const float *rotationsEnd) {
    if (std::distance(rotationsBegin, rotationsEnd) != size_) {
        throw std::runtime_error(
                    "Number of elements in [rotationsBegin, rotationsEnd) "
                    "doesn't match size of MoMosaicModel.");
    }
    std::copy(rotationsBegin, rotationsEnd, rotations_.begin());
}

void MoMosaicModel::getRotations(float *rotationsBegin) const {
    std::copy(rotations_.cbegin(), rotations_.cend(), rotationsBegin);
}

void MoMosaicModel::setScales(const float *scalesBegin,
                              const float *scalesEnd) {
    if (std::distance(scalesBegin, scalesEnd) != size_) {
        throw std::runtime_error(
              "Number of elements in [scalesBegin, scalesEnd) "
              "doesn't match size of MoMosaicModel.");
    }
    std::copy(scalesBegin, scalesEnd, scales_.begin());
}

void MoMosaicModel::getScales(float *scalesBegin) const {
    std::copy(scales_.cbegin(), scales_.cend(), scalesBegin);
}
