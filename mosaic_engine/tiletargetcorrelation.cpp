#include <tiletargetcorrelation.h>


float MoTileTargetCorrelation::computeBadness(const MoMosaicModel &model,
                                              const MoTargetImage &targetImage) {
    Q_UNUSED(model);
    Q_UNUSED(targetImage);
    return 0.0f;
}
