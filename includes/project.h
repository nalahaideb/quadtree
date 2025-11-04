#ifndef PROJECT_H
#define PROJECT_H
#include "Includes.h"
#include "Constants.h"
#include "compgeom.h"
#include "Surface.h"
#include "Event.h"
#include <cmath>
Surface sf(W, H);
#include "tree.h"
#include "tree.cpp"
#include "orb.h"

//keypressed = get_keypressed();
/* class Quadtree */
/* { */
/*   public: */
/*   Quadtree(const int w, const int h) */
/*       :ps(&sf), rect(w, h, w, h) */
/*     { */
/*         tree->insert(0, new Quadtree(w / 2, h / 2)); */
/*     } */
/*     TreeNodev< Rect > * tree; */
/*     Surface * ps; */
/*     Rect rect; */
/*   private: */
/* }; */
inline void drawAfterMe()
{
    sf.fill(BLACK);
    sf.lock();
}
inline void drawBeforeMe()
{
    sf.unlock();
    sf.flip();
}

#endif
