#ifndef LOGO
#define LOGO

#include <X11/Xlib.h>
#include <Imlib2.h>
#include <X11/cursorfont.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

#define LOGO_DIMENSION 256

int load_logo(Display* disp, XVisualInfo vinfo, Window win, XSetWindowAttributes attr)
{
    XWindowAttributes win_attr;
    XGetWindowAttributes(disp, win, &win_attr);
    
    imlib_context_set_display(disp);
    imlib_context_set_visual(vinfo.visual);
    imlib_context_set_drawable(win);

    Imlib_Image image = imlib_load_image("./bl.png");
    if (!image) {
        fprintf(stderr, "..And Brunch said: I Failed to load image\n");
        return -1;
    }
    imlib_context_set_image(image);
    imlib_render_image_on_drawable_at_size(0, win_attr.height-LOGO_DIMENSION*0.75, LOGO_DIMENSION, LOGO_DIMENSION);
    imlib_free_image();
    return 0;
}


#endif