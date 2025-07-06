#include "../types.h"
#include "../config.c"

void calculate_percentage(int maxvalue, percentable_t *percentable)
{
    if (percentable->percent != -1)
    {
        percentable->value = (maxvalue * percentable->percent) / 100;
    }
}

void recalc_cells()
{
    int margined_cell_width, margined_cell_height;

    if (text_after)
    {
        cell_width = icon_size + icon_padding * 2;
        cell_height = icon_size + icon_v_padding * 2;
        margined_cell_width = icon_size + icon_padding * 2 + least_margin;
        margined_cell_height = icon_size + icon_v_padding * 2 + least_v_margin;
        if (ucolumns == 0)
            ucolumns = 1;
    }
    else
    {
        cell_width = icon_size + icon_padding * 2;
        cell_height = icon_size + icon_v_padding * 2 + font_height + text_padding;
        margined_cell_width = icon_size + icon_padding * 2 + least_margin;
        margined_cell_height = icon_size + icon_v_padding * 2 + font_height + text_padding + least_v_margin;
    }

    border = screen_width / 10;
    if (uborder.value > 0)
        border = uborder.value;
    if (uborder.value == -1 && uborder.percent == -1)
    {
        if (ucolumns == 0)
        {
            border = 0;
        }
        else
        {
            side_border = (screen_width - (ucolumns * cell_width + (ucolumns - 1) * least_margin)) / 2;
            border = (screen_height - prompt_font_height - prompt_spacing - (urows * cell_height + (urows - 1) * least_v_margin)) / 2;
        }
    }

    if (uside_border.value == 0 && uside_border.percent == -1)
        side_border = border;
    if (uside_border.value > 0)
        side_border = uside_border.value;
    if (uside_border.value == -1 && uside_border.percent == -1)
    {
        if (ucolumns == 0)
        {
            side_border = 0;
        }
        else
        {
            side_border = (screen_width - (ucolumns * cell_width + (ucolumns - 1) * least_margin)) / 2;
        }
    }

    int usable_width;
    int usable_height;
    // These do while loops should run at most three times, it's just to avoid copying code
    do
    {
        usable_width = screen_width - side_border * 2;
        usable_height = screen_height - border * 2;
        usable_height = screen_height - border * 2 - prompt_spacing - prompt_font_height;

        // If the usable_width is too small, take some space away from the border
        if (usable_width < cell_width)
        {
            side_border = (screen_width - cell_width - 1) / 2;
        }
        else if (usable_height < cell_height)
        {
            border = (screen_height - cell_height - prompt_spacing - prompt_font_height - 1) / 2;
        }

    } while ((usable_width < cell_width && screen_width > cell_width) || (usable_height < cell_height && screen_height > cell_height));

    // just in case, make sure border is never negative
    if (border < 0)
        border = 0;
    if (side_border < 0)
        side_border = 0;

    // If columns were not manually overriden, calculate the most it can possibly contain
    if (ucolumns == 0)
    {
        columns = usable_width / margined_cell_width;
    }
    else
    {
        columns = ucolumns;
    }
    if (urows == 0)
    {
        rows = usable_height / margined_cell_height;
    }
    else
    {
        rows = urows;
    }

    // If we don't have space for a single column or row, force it.
    if (columns <= 0)
    {
        columns = 1;
    }
    if (rows <= 0)
    {
        rows = 1;
    }

    if (text_after)
    {
        cell_width = (usable_width - least_margin * (columns - 1)) / columns;
    }

    // The space between the icon tiles to fill all the space
    if (columns == 1)
    {
        column_margin = (usable_width - cell_width * columns);
    }
    else
    {
        column_margin = (usable_width - cell_width * columns) / (columns - 1);
    }
    if (rows == 1)
    {
        row_margin = (usable_height - cell_height * rows);
    }
    else
    {
        row_margin = (usable_height - cell_height * rows) / (rows - 1);
    }

    // These are kept in case manual positioning is reintroduced
    prompt_x = (side_border * side_border_ratio) / 50;
    prompt_y = (border * border_ratio) / 50;
    /*
    if(uside_border == 0){
        side_border = border;
    }*/
}
