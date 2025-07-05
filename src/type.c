#ifndef TYPES
#define TYPES

#include <sys/file.h>

typedef struct node
{
    char title[256];
    char icon[256];
    char cmd[512];
    int hovered;
    int clicked;
    int hidden;
    int x;
    int y;
    struct node * next;
} node_t;

typedef struct button
{
    char icon_normal[256];
    char icon_highlight[256];
    char cmd[512];
    int hovered;
    int clicked;
    int x;
    int y;
    int w;
    int h;
    struct button * next;
} button_t;
typedef struct shortcut
{
  char *key;
  node_t *entry;
  struct shortcut *next;
} shortcut_t;

typedef struct keynode {
    char key[255];
    struct keynode * next;
} keynode_t;

typedef struct color {
    int r, g, b, a;
} color_t;

typedef struct percentable {
    int percent;
    int value;
} percentable_t;


struct XLaunch {
    // Icon and layout settings
    int icon_size;
    int icon_padding;
    int icon_v_padding;
    int text_padding;
    int least_margin;
    int least_v_margin;
    
    // Grid layout
    int ucolumns;
    int columns;
    int urows;
    int rows;
    int column_margin;
    int row_margin;
    
    // Border settings
    int border;
    int side_border;
    int border_ratio;
    int side_border_ratio;
    percentable_t uborder;
    percentable_t uside_border;
    
    // Cell dimensions
    int cell_width;
    int cell_height;
    int font_height;
    int prompt_font_height;
    
    // Window settings
    int use_root_img;
    int windowed;
    int multiple_instances;
    int uposx;
    int uposy;
    int force_reposition;
    int uwidth;
    int uheight;
    int no_title;
    
    // Command and input
    char commandline[10024];
    char commandlinetext[10024];
    char * input_file;
    FILE * input_source;
    int read_config;
    int stdin_poll_timeout;
    
    // Prompt settings
    char * prompt;
    char * prompt_font_name;
    int prompt_x;
    int prompt_y;
    int prompt_spacing;
    int no_prompt;
    color_t prompt_color;
    
    // Font settings
    char * font_name;
    
    // Window properties
    char * program_name;
    char * window_title;
    char * window_icon;
    
    // Background and styling
    char * background_file;
    char * highlight_file;
    int bg_fill;
    color_t background_color;
    color_t shadow_color;
    int background_color_set;
    color_t highlight_color;
    color_t scrollbar_color;
    color_t scrollindicator_color;
    
    // Text colors
    color_t text_color;
    
    // Mouse and interaction
    int mouse_moves;
    int hovered_entry;
    
    // Behavior flags
    int void_click_terminate;
    int focus_lost_terminate;
    int dont_quit;
    int reverse;
    int output_only;
    int select_only;
    int text_after;
    int text_other_side;
    int clear_memory;
    int upside_down;
    int padding_swap;
    int hide_missing;
    int center_icons;
    int noscroll;
    int scrolled_past;
    
    // X11 display and window management
    Display *disp;
    Window win;
    XVisualInfo vinfo;
    XSetWindowAttributes attr;
    int x11_fd;
    struct pollfd eventfds[2];
    XIM im;
    XIC ic;
    int screen;
    int screen_width;
    int screen_height;
};


#endif