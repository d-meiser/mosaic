#ifndef INTERACTIONTILETILE_H
#define INTERACTIONTILETILE_H

#include <badness.h>
#include <potential.h>
#include <memory>


class MoInteractionTileTile : public MoBadness {
public:
    MoInteractionTileTile(std::unique_ptr<MoPotential> potential);
    virtual ~MoInteractionTileTile() {}
    virtual float computeBadness(const MoMosaicModel &model,
                                 const MoTargetImage &targetImage);
private:
    std::unique_ptr<MoPotential> potential_;

    float computeBadnessPair(const MoMosaicModel& model,
                                                const MoTargetImage& targetImage,
                                                int i, int j);
};

#endif // INTERACTIONTILETILE_H