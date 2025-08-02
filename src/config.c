#include <sys/file.h>
#include <stdio.h>
#include <getopt.h>
#include <sys/poll.h>
#include "types.h"
#include "./utils/errutils.c"
#include "./utils/help.c"
#ifndef CONFIG
#define CONFIG

void handle_option(int c, char *optarg);
void parse_button(char *button_spec);

int icon_size = 64;
int ucolumns = 0;
int columns;
int urows = 0;
int rows;
int column_margin = 2;
int row_margin = 2;
int icon_padding = 40;
int icon_v_padding = -1;
int text_padding = 10;
int border;
int side_border = 0;
int border_ratio = 50;
int side_border_ratio = 50;
int cell_width;
int cell_height;
int font_height;
int prompt_font_height;
int use_root_img = 0;
char commandline[10024];
char commandlinetext[10024];
int prompt_x;
int prompt_y;
int mouse_moves = 0;
char *background_file = "";
char *highlight_file = "";
char *input_file = "";
int read_config = 0;
FILE *input_source = NULL;
char *prompt = "Search: ";
char *font_name = "";
char *prompt_font_name = "";
char *program_name;
char *window_title;
char *window_icon;
int bg_fill = 0;
int no_prompt = 0;
int no_title = 0;
int prompt_spacing = 48;
int windowed = 0;
int multiple_instances = 0;
int uposx = 0;
int uposy = 0;
int force_reposition = 0;
int uwidth = 0;
int uheight = 0;
percentable_t uborder = {.percent = -1, .value = 0};
percentable_t uside_border = {.percent = -1, .value = 0};
int void_click_terminate = 0;
int focus_lost_terminate = 0;
int dont_quit = 0;
int reverse = 0;
int output_only = 0;
int select_only = 0;
int text_after = 0;
int text_other_side = 0;
int clear_memory = 0;
int upside_down = 0;
int padding_swap = 0;
int least_margin = 0;
int least_v_margin = -1;
int hide_missing = 0;
int center_icons = 0;
int noscroll = 0;
int scrolled_past = 0;
int hovered_entry = 0;
color_t text_color = {.r = 255, .g = 255, .b = 255, .a = 255};
color_t prompt_color = {.r = 255, .g = 255, .b = 255, .a = 255};
color_t background_color = {.r = 46, .g = 52, .b = 64, .a = 102};
color_t shadow_color = {.r = 0, .g = 0, .b = 0, .a = 30};
int background_color_set = 0;
color_t highlight_color = {.r = 255, .g = 255, .b = 255, .a = 50};
color_t scrollbar_color = {.r = 255, .g = 255, .b = 0., .a = 60};
color_t scrollindicator_color = {.r = 255, .g = 255, .b = 255, .a = 112};
int stdin_poll_timeout = 10;
int desktop_mode = 0;
int entries_count = 0;
node_t *entries = NULL;
button_t *buttons = NULL;
shortcut_t *shortcuts = NULL;
keynode_t *cmdline = NULL;


static struct option long_options[] =
    {

        {"tc", required_argument, 0, 1009},
        {"textcolor", required_argument, 0, 1009},
        {"pc", required_argument, 0, 1010},
        {"promptcolor", required_argument, 0, 1010},
        {"backgroundcolor", required_argument, 0, 1011},
        {"bc", required_argument, 0, 1011},
        {"hc", required_argument, 0, 1012},
        {"highlightcolor", required_argument, 0, 1012},
        {"name", required_argument, 0, 1013},
        {"config", required_argument, 0, 1014},
        {"bgfill", no_argument, 0, 1015},
        {"focuslostterminate", no_argument, 0, 1016},
        {"borderratio", required_argument, 0, 1017},
        {"sideborderratio", required_argument, 0, 1018},
        {"noscroll", no_argument, 0, 1019},
        {"iconvpadding", required_argument, 0, 1020},
        {"shadowcolor", required_argument, 0, 1021},
        {"sc", required_argument, 0, 1021},
        {"title", required_argument, 0, 1022},
        {"icon", required_argument, 0, 1025},
        {"scrollbarcolor", required_argument, 0, 1023},
        {"scrollindicatorcolor", required_argument, 0, 1024},
        {"stdinpolltimeout", required_argument, 0, 1026},
        {"button", required_argument, 0, 'A'},
        {"textafter", no_argument, 0, 'a'},
        {"border", required_argument, 0, 'b'},
        {"sideborder", required_argument, 0, 'B'},
        {"center", no_argument, 0, 'C'},
        {"columns", required_argument, 0, 'c'},
        {"desktop", no_argument, 0, 'd'},
        {"hidemissing", no_argument, 0, 'e'},
        {"font", required_argument, 0, 'f'},
        {"promptfont", required_argument, 0, 'F'},
        {"background", required_argument, 0, 'g'},
        {"rootwindowbackground", no_argument, 0, 'G'},
        {"height", required_argument, 0, 'h'},
        {"help", no_argument, 0, 'H'},
        {"iconpadding", required_argument, 0, 'I'},
        {"input", required_argument, 0, 'i'},
        {"highlight", required_argument, 0, 'L'},
        {"leastmargin", required_argument, 0, 'l'},
        {"clearmemory", no_argument, 0, 'M'},
        {"multiple", no_argument, 0, 'm'},
        {"noprompt", no_argument, 0, 'n'},
        {"notitle", no_argument, 0, 'N'},
        {"outputonly", no_argument, 0, 'o'},
        {"textotherside", no_argument, 0, 'O'},
        {"prompt", required_argument, 0, 'p'},
        {"promptspacing", required_argument, 0, 'P'},
        {"dontquit", no_argument, 0, 'q'},
        {"reverse", no_argument, 0, 'R'},
        {"rows", required_argument, 0, 'r'},
        {"iconsize", required_argument, 0, 's'},
        {"selectonly", no_argument, 0, 'S'},
        {"textpadding", required_argument, 0, 'T'},
        {"voidclickterminate", no_argument, 0, 't'},
        {"shortcuts", required_argument, 0, 'U'},
        {"upsidedown", no_argument, 0, 'u'},
        {"leastvmargin", required_argument, 0, 'V'},
        {"version", no_argument, 0, 'v'},
        {"width", required_argument, 0, 'w'},
        {"windowed", no_argument, 0, 'W'},
        {"paddingswap", no_argument, 0, 'X'},
        {"xposition", required_argument, 0, 'x'},
        {"yposition", required_argument, 0, 'y'},
        {0, 0, 0, 0}};

void parse_config(FILE *input)
{
    int readstatus;
    int position = 0;
    int size = 0;
    int eol = 0;
    int fileline = 1;
    char *optarg = NULL;
    char matching[(sizeof(long_options) / sizeof(struct option)) - 1];
    char *entries_word = "entries";
    int matching_entries = 1;
    int matched = '?';
    int comment = 0;
    memset(matching, 1, sizeof(long_options) / sizeof(struct option) - 1);

    struct pollfd fds;
    fds.fd = fileno(input);
    fds.events = POLLIN;
    node_t *current_entry;
    while (poll(&fds, 1, 0))
    {
        char b;
        readstatus = read(fds.fd, &b, 1);
        if (readstatus <= 0)
        {
            break;
        }
        if ((b == ':' && optarg == NULL) || b == '\n')
        {
            if (b == '\n')
                eol = 1;
            b = '\0';
        }
        if (b == '#' && optarg == NULL && position == 0)
            comment = 1;
        if (comment == 1 && eol != 1)
            continue;
        if (b == ' ' && position == 0)
            continue;
        if (optarg == NULL)
        {
            for (int i = 0; i < sizeof(long_options) / sizeof(struct option) - 1; i++)
            {
                if (long_options[i].name[position] != b)
                {
                    matching[i] = 0;
                }
            }
            if (entries_word[position] != b && eol != 1)
            {
                matching_entries = 0;
            }
            if (b == '\0')
            {
                for (int i = 0; i < sizeof(long_options) / sizeof(struct option) - 1; i++)
                {
                    if (matching[i] == 1)
                    {
                        optarg = malloc(1);
                        position = -1;
                        matched = long_options[i].val;
                    }
                }
            }
        }
        else
        {
            optarg = realloc(optarg, ++size);
            optarg[position] = b;
        }
        position++;
        if (eol == 1)
        {
            if (position != 1)
            {
                if (matching_entries)
                {
                    input_source = input;
                    break;
                }
                else
                {
                    if (matched == '?')
                    {
                        fprintf(stderr, "Got unknown option in config file on line %d\n", fileline);
                    }
                    handle_option(matched, optarg);
                }
            }
            position = 0;
            size = 0;
            eol = 0;
            comment = 0;
            matching_entries = 1;
            memset(matching, 1, sizeof(long_options) / sizeof(struct option) - 1);
            if (optarg != NULL)
            {
                // free(optarg);
                optarg = NULL;
            }
            matched = '?';
            fileline++;
        }
    }
    if (position > 1)
    {
        if (matching_entries)
        {
            input_source = input;
        }
        else
        {
            if (matched == '?')
            {
                for (int i = 0; i < sizeof(long_options) / sizeof(struct option) - 1; i++)
                {
                    if (matching[i] == 1)
                    {
                        matched = long_options[i].val;
                       break;
                    }
                }
            }
            if (matched == '?')
            {
                fprintf(stderr, "Got unknown option in config file on line %d\n", fileline);
            }
            handle_option(matched, optarg);
        }
    }
    if (input_source != input)
        close(fds.fd);
}

void handle_option(int c, char *optarg) {
    switch (c) {
        case 'v':
            fprintf(stderr, "xlunch graphical program launcher, version %d.%d.%d\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
            exit(OKAY);

        case 'd':
            desktop_mode = 1;
            break;

        case 'G':
            use_root_img = 1;
            if(background_color_set == 0){
                background_color.r = 0;
                background_color.g = 0;
                background_color.b = 0;
                background_color.a = 100;
            }
            break;

        case 'n':
            no_prompt = 1;
            prompt_spacing = 0;
            prompt_font_height = 0;
            break;

        case 'N':
            no_title = 1;
            font_height = 0;
            text_padding = 0;
            break;

        case 'g':
            background_file = optarg;
            if(background_color_set == 0){
                background_color.r = 0;
                background_color.g = 0;
                background_color.b = 0;
                background_color.a = 100;
            }
            break;

        case 'L':
            highlight_file = optarg;
            break;

        case 'I':
            icon_padding = atoi(optarg);
            break;

        case 1020:
            icon_v_padding = atoi(optarg);
            break;

        case 'T':
            text_padding = atoi(optarg);
            break;

        case 'c':
            ucolumns = atoi(optarg);
            break;

        case 'r':
            urows = atoi(optarg);
            break;

        case 'b':
            if(strcmp(optarg, "auto") == 0){
                uborder.value = -1;
            } else {
                if (optarg[strlen(optarg)-1] == '%') {
                    uborder.percent = atoi(optarg);
                } else {
                    uborder.value = atoi(optarg);
                }
            }
            break;

        case 'B':
            if(strcmp(optarg, "auto") == 0){
                uside_border.value = -1;
            } else {
                if (optarg[strlen(optarg)-1] == '%') {
                    uside_border.percent = atoi(optarg);
                } else {
                    uside_border.value = atoi(optarg);
                }
            }
            break;

        case 'P':
            prompt_spacing = atoi(optarg);
            break;

        case 's':
            icon_size = atoi(optarg);
            break;

        case 'i':
            input_file = optarg;
            break;

        case 'W':
            windowed = 1;
            break;

        case 'p':
            prompt = optarg;
            break;

        case 'f':
            font_name = optarg;
            break;

        case 'F':
            prompt_font_name = optarg;
            break;

        case 'm':
            multiple_instances = 1;
            break;

        case 't':
            void_click_terminate = 1;
            break;

        case 'x':
            uposx = atoi(optarg);
            force_reposition = 1;
            break;

        case 'y':
            uposy = atoi(optarg);
            force_reposition = 1;
            break;

        case 'w':
            uwidth = atoi(optarg);
            break;

        case 'h':
            uheight = atoi(optarg);
            break;

        case 'o':
            output_only = 1;
            break;

        case 'S':
            select_only = 1;
            break;

        case 1009:
            sscanf(optarg, "%02x%02x%02x%02x", &text_color.r, &text_color.g, &text_color.b, &text_color.a);
            break;

        case 1010:
            sscanf(optarg, "%02x%02x%02x%02x", &prompt_color.r, &prompt_color.g, &prompt_color.b, &prompt_color.a);
            break;

        case 1011:
            sscanf(optarg, "%02x%02x%02x%02x", &background_color.r, &background_color.g, &background_color.b, &background_color.a);
            background_color_set = 1;
            break;

        case 1021:
            sscanf(optarg, "%02x%02x%02x%02x", &shadow_color.r, &shadow_color.g, &shadow_color.b, &shadow_color.a);
            break;

        case 1012:
            sscanf(optarg, "%02x%02x%02x%02x", &highlight_color.r, &highlight_color.g, &highlight_color.b, &highlight_color.a);
            break;

        case 1023:
            sscanf(optarg, "%02x%02x%02x%02x", &scrollbar_color.r, &scrollbar_color.g, &scrollbar_color.b, &scrollbar_color.a);
            break;

        case 1024:
            sscanf(optarg, "%02x%02x%02x%02x", &scrollindicator_color.r, &scrollindicator_color.g, &scrollindicator_color.b, &scrollindicator_color.a);
            break;

        case 'a':
            text_after = 1;
            break;

        case 1013:
            program_name = optarg;
            break;

        case 1022:
            window_title = optarg;
            break;

        case 1025:
            window_icon = optarg;
            break;

        case 'q':
            dont_quit = 1;
            break;

        case 'R':
            reverse = 1;
            break;

        case 'O':
            text_other_side = 1;
            break;

        case 'M':
            clear_memory = 1;
            break;

        case 'u':
            upside_down = 1;
            break;

        case 'X':
            padding_swap = 1;
            break;

        case 'l':
            least_margin = atoi(optarg);
            break;

        case 'V':
            least_v_margin = atoi(optarg);
            break;

        case 'C':
            center_icons = 1;
            break;

        case 'e':
            hide_missing = 1;
            break;

        case 'A':
            parse_button(optarg);
            break;

        case 'U': ;
            unsigned char lb = optarg[0];
            int i = 0;
            shortcut_t *current_shortcut = NULL;
            while (lb != '\0') {
                if ( current_shortcut == NULL ) {
                    current_shortcut = malloc(sizeof(shortcut_t));
                } else {
                    current_shortcut->next = malloc(sizeof(shortcut_t));
                    current_shortcut = current_shortcut->next;
                }
                if ( shortcuts == NULL)
                    shortcuts = current_shortcut;
                current_shortcut->entry = NULL;
                current_shortcut->next = NULL;
                if (( lb & 0x80 ) == 0 ) {          // lead bit is zero, must be a single ascii
                    current_shortcut->key = malloc(sizeof(char));
                    memcpy(current_shortcut->key, &optarg[i], sizeof(char));
                    i+=1;
                } else if (( lb & 0xE0 ) == 0xC0 ) {  // 110x xxxx
                    current_shortcut->key = malloc(sizeof(char)*2);
                    memcpy(current_shortcut->key, &optarg[i], sizeof(char)*2);
                    i+=2;
                } else if (( lb & 0xF0 ) == 0xE0 ) { // 1110 xxxx
                    current_shortcut->key = malloc(sizeof(char)*3);
                    memcpy(current_shortcut->key, &optarg[i], sizeof(char)*3);
                    i+=3;
                } else if (( lb & 0xF8 ) == 0xF0 ) { // 1111 0xxx
                    current_shortcut->key = malloc(sizeof(char)*4);
                    memcpy(current_shortcut->key, &optarg[i], sizeof(char)*4);
                    i+=4;
                } else {
                   printf( "Unrecognized lead byte in shortcut (%02x)\n", lb );
                }
                lb = optarg[i];
            }
            break;

        case 1014:
            parse_config(fopen(optarg, "rb"));
            read_config = 1;
            break;
            
        case 1015:
            bg_fill = 1;
            break;

        case 1016:
            focus_lost_terminate = 1;
            break;

        case 1017:
            border_ratio = atoi(optarg);
            break;

        case 1018:
            side_border_ratio = atoi(optarg);
            break;

        case 1019:
            noscroll = 1;
            break;

        case '?':
            fprintf(stderr, "See --help for usage documentation\n");
            exit(CONFIGERROR);
            break;

        case 1026:
            stdin_poll_timeout = atoi(optarg);
            break;


        case 'H':
            fprintf (stderr, HELP);
            // Check if we came from the error block above or if this was a call with --help
            if(c == '?'){
                exit(CONFIGERROR);
            } else {
                exit(OKAY);
            }
            break;
    }
}

void parse_button(char *button_spec)
{
    int parsing = 0;  // section currently being read
    int position = 0; // position in the current entry
    int i = 0;
    button_t *new_button = malloc(sizeof(button_t));
    char b = button_spec[0];
    char x[256];
    char y[256];
    while (b != '\0')
    {
        if ((b == ';' && parsing != 4) || (parsing == 2 && b == ','))
        {
            b = '\0';
        }
        switch (parsing)
        {
        case 0:
            new_button->icon_normal[position] = b;
            break;
        case 1:
            new_button->icon_highlight[position] = b;
            break;
        case 2:
            x[position] = b;
            break;
        case 3:
            y[position] = b;
            break;
        case 4:
            new_button->cmd[position] = b;
            break;
        }
        position++;
        if (b == '\0')
        {
            position = 0;
            parsing++;
        }
        int maxlen = (parsing == 4 ? 511 : 255);
        if (position == maxlen)
        {
            fprintf(stderr, "Entry too long, maximum length is %d characters!\n", maxlen);
            break;
        }
        i++;
        b = button_spec[i];
    }
    if (x[0] == '-')
    {
        new_button->x = atoi(x) - 1;
    }
    else
    {
        new_button->x = atoi(x);
    }
    if (y[0] == '-')
    {
        new_button->y = atoi(y) - 1;
    }
    else
    {
        new_button->y = atoi(y);
    }
    imlib_context_set_image(imlib_load_image(new_button->icon_normal));
    new_button->w = imlib_image_get_width();
    new_button->h = imlib_image_get_height();
    imlib_free_image();
    new_button->cmd[position] = '\0';
    new_button->next = buttons;
    buttons = new_button;
}

int screen;
int screen_width;
int screen_height;

#endif