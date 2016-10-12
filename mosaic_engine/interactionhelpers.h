#ifndef INTERACTIONHELPERS_H
#define INTERACTIONHELPERS_H

class MoPotential;


void moTransformToWorldCoordinates(float x, float y, float w, float h,
                                        float alpha, float scale,
                                        float* r);
float moComputeBadnessPair(float x0, float y0, float w0, float h0,
                         float alpha0, float scale0,
                         float x1, float y1, float w1, float h1,
                         float alpha1, float scale1,
                         MoPotential* potential);

#endif // INTERACTIONHELPERS_H
