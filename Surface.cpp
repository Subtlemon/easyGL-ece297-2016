#include "Surface.h"

std::unordered_map<cairo_surface_t*, unsigned> Surface::surfaces;

Surface::Surface() {
    mSurface = NULL;
}

Surface::Surface(const char* filePath) {
    setSurface(filePath);
}

Surface::~Surface() {
    if (mSurface == NULL) return; // nothing to be done
    if (surfaces[mSurface] == 1)
        cairo_surface_destroy(mSurface);
    else if (surfaces[mSurface] < 1)
        std::cerr << "Yeah notify Vaughn that Harry screwed up again" << std::endl;
    --surfaces[mSurface];
}

// assignment operator
Surface& Surface::operator=(const Surface& surface) {
    mSurface = surface.mSurface;
    ++surfaces[mSurface];
    return *this;
}

// CCtor
Surface::Surface(const Surface& surface) {
    mSurface = surface.mSurface;
    ++surfaces[mSurface];
}

void Surface::setSurface(const char* filePath) {
    --surfaces[mSurface];
    cairo_surface_destroy(mSurface);
    mSurface = cairo_image_surface_create_from_png (filePath);
    ++surfaces[mSurface];
    switch(cairo_surface_status(mSurface)) {
        case CAIRO_STATUS_SUCCESS:
            return;
        case CAIRO_STATUS_NULL_POINTER:
            std::cerr << "Oops we messed up on our end." << std::endl << 
                    "Please notify Vaughn that Harry screwed up." << std::endl;
            break;
        case CAIRO_STATUS_NO_MEMORY:
            std::cerr << "Out of memory" << std::endl;
            break;
        case CAIRO_STATUS_READ_ERROR:
            std::cerr << "Error reading file" << std::endl;
            break;
        case CAIRO_STATUS_INVALID_CONTENT:
            std::cerr << "Invalid Content" << std::endl;
            break;
        case CAIRO_STATUS_INVALID_FORMAT:
            std::cerr << "Invalid Format" << std::endl;
            break;
        case CAIRO_STATUS_INVALID_VISUAL:
            std::cerr << "Invalid Visual" << std::endl;
            break;
        default:
            std::cerr << "Invalid Error" << std::endl;
            break;
    }

    // should only reach this point if unsuccessfull
    --surfaces[mSurface];
    cairo_surface_destroy(mSurface);
    mSurface = NULL;
}

cairo_surface_t* Surface::getSurface() const {
    return mSurface;
}
