#ifndef SURFACE_H
#define SURFACE_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <cairo.h>
#include <cairo-xlib.h>

class Surface {
    public:
        Surface();
        Surface(const char* filePath);
        ~Surface();

        // assignment operator
        Surface& operator=(const Surface& rhs);
        // cctor
        Surface(const Surface& surface);

        void setSurface(const char* filePath);

        // Note: getSurface will return NULL if never properly initialized
        cairo_surface_t* getSurface() const;

    private:
        cairo_surface_t* mSurface;

        void safeDestroySurface();

        // static hash table to keep track of surfaces
        static std::unordered_map<cairo_surface_t*, unsigned> surfaces;
};

#endif
