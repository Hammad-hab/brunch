#include <Imlib2.h>
#include<stdio.h>


Imlib_Image load_image(char * icon) {
    Imlib_Load_Error load_error;
    Imlib_Image image = imlib_load_image_with_error_return(icon, &load_error);
    if(image) {
        imlib_context_set_image(image);
        imlib_free_image();
    } else {
        fprintf(stderr, "Could not load icon %s, Imlib failed with: ", icon);
        switch(load_error) {
            case IMLIB_LOAD_ERROR_NONE:
                fprintf(stderr, "IMLIB_LOAD_ERROR_NONE");
                break;
            case IMLIB_LOAD_ERROR_IMAGE_FRAME:
                fprintf(stderr, "IMLIB_LOAD_ERROR_IMAGE_FRAME");
                break;
            
            case IMLIB_LOAD_ERROR_IMAGE_READ:
                fprintf(stderr, "IMLIB_LOAD_ERROR_IMAGE_READ");
                break;
            
            case IMLIB_LOAD_ERROR_FILE_DOES_NOT_EXIST:
                fprintf(stderr, "IMLIB_LOAD_ERROR_FILE_DOES_NOT_EXIST");
                break;
            case IMLIB_LOAD_ERROR_FILE_IS_DIRECTORY:
                fprintf(stderr, "IMLIB_LOAD_ERROR_FILE_IS_DIRECTORY");
                break;
            case IMLIB_LOAD_ERROR_PERMISSION_DENIED_TO_READ:
                fprintf(stderr, "IMLIB_LOAD_ERROR_PERMISSION_DENIED_TO_READ");
                break;
            case IMLIB_LOAD_ERROR_NO_LOADER_FOR_FILE_FORMAT:
                fprintf(stderr, "IMLIB_LOAD_ERROR_NO_LOADER_FOR_FILE_FORMAT");
                break;
            case IMLIB_LOAD_ERROR_PATH_TOO_LONG:
                fprintf(stderr, "IMLIB_LOAD_ERROR_PATH_TOO_LONG");
                break;
            case IMLIB_LOAD_ERROR_PATH_COMPONENT_NON_EXISTANT:
                fprintf(stderr, "IMLIB_LOAD_ERROR_PATH_COMPONENT_NON_EXISTANT");
                break;
            case IMLIB_LOAD_ERROR_PATH_COMPONENT_NOT_DIRECTORY:
                fprintf(stderr, "IMLIB_LOAD_ERROR_PATH_COMPONENT_NOT_DIRECTORY");
                break;
            case IMLIB_LOAD_ERROR_PATH_POINTS_OUTSIDE_ADDRESS_SPACE:
                fprintf(stderr, "IMLIB_LOAD_ERROR_PATH_POINTS_OUTSIDE_ADDRESS_SPACE");
                break;
            case IMLIB_LOAD_ERROR_TOO_MANY_SYMBOLIC_LINKS:
                fprintf(stderr, "IMLIB_LOAD_ERROR_TOO_MANY_SYMBOLIC_LINKS");
                break;
            case IMLIB_LOAD_ERROR_OUT_OF_MEMORY:
                fprintf(stderr, "IMLIB_LOAD_ERROR_OUT_OF_MEMORY");
                break;
            case IMLIB_LOAD_ERROR_OUT_OF_FILE_DESCRIPTORS:
                fprintf(stderr, "IMLIB_LOAD_ERROR_OUT_OF_FILE_DESCRIPTORS");
                break;
            case IMLIB_LOAD_ERROR_PERMISSION_DENIED_TO_WRITE:
                fprintf(stderr, "IMLIB_LOAD_ERROR_PERMISSION_DENIED_TO_WRITE");
                break;
            case IMLIB_LOAD_ERROR_OUT_OF_DISK_SPACE:
                fprintf(stderr, "IMLIB_LOAD_ERROR_OUT_OF_DISK_SPACE");
                break;
            case IMLIB_LOAD_ERROR_UNKNOWN:
                fprintf(stderr, "IMLIB_LOAD_ERROR_UNKNOWN");
                break;
        }
        fprintf(stderr, "\n");
    }
    return image;
}
