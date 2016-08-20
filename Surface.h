#ifndef SURFACE_H
#define SURFACE_H

#include <iostream>
#include <string>
//#include <cairo.h>
//#include <cairo-xlib.h>
#include "graphics_state.h"

class Surface {
    public:
        Surface();
        Surface(const char* filePath);
        ~Surface();

        void setSurface(const char* filePath);

        // Note: getSurface will return NULL if never properly initialized
        cairo_surface_t* getSurface() const;

    private:
        cairo_surface_t* mSurface;
};

#endif
