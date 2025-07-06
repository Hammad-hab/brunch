#include <Imlib2.h>

int get_font_height(Imlib_Font font){
    imlib_context_set_font(font);
    // maximum font descent is relative to baseline (ie. negative)
    int height = imlib_get_maximum_font_ascent() - imlib_get_maximum_font_descent();
    imlib_free_font();
    return height;
}

Imlib_Font load_default_font(){
    // No font was specified, try to load some default options as a fallback
    Imlib_Font font;
    font = imlib_load_font("OpenSans-Regular/10");
    if (!font) font = imlib_load_font("DejaVuSans/10");
    return font;
}

Imlib_Font load_font()
{
    Imlib_Font font;
    if (strlen(font_name) == 0){
        font = load_default_font();
    } else {
        font = imlib_load_font(font_name);
    }
    if (font == NULL) {
        fprintf(stderr, "Font %s could not be loaded! Please specify one with -f parameter\n", font_name);
        exit(FONTERROR);
    }

    if (!no_title)
       font_height = get_font_height(font);

    return font;
}


Imlib_Font load_prompt_font(const char* prompt_font_name, const char* font_name)
{
    Imlib_Font font;
    if (strlen(prompt_font_name) == 0)
    {
        if (strlen(font_name) == 0)
        {
            font = load_default_font();
        }
        else
        {
            font = imlib_load_font(font_name);
        }
    }
    else
    {
        font = imlib_load_font(prompt_font_name);
    }
    if (font == NULL)
    {
        fprintf(stderr, "Prompt font %s could not be loaded! Please specify one with -F parameter\n", prompt_font_name);
        exit(FONTERROR);
    }

    if (!no_prompt)
        prompt_font_height = get_font_height(font);

    return font;
}