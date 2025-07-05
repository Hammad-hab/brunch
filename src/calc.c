#include "type.c"

void recalc_cells(struct XLaunch config)
{
    int margined_cell_width, margined_cell_height;
    int cell_width, cell_height;
    if (config.text_after){
        cell_width=config.icon_size+config.icon_padding*2;
        cell_height=config.icon_size+config.icon_v_padding*2;
        margined_cell_width=config.icon_size+config.icon_padding*2+config.least_margin;
        margined_cell_height=config.icon_size+config.icon_v_padding*2+config.least_v_margin;
        if(config.ucolumns == 0)
            config.ucolumns = 1;
    } else {
        cell_width=config.icon_size+config.icon_padding*2;
        cell_height=config.icon_size+config.icon_v_padding*2+config.font_height+config.text_padding;
        margined_cell_width=config.icon_size+config.icon_padding*2+config.least_margin;
        margined_cell_height=config.icon_size+config.icon_v_padding*2+config.font_height+config.text_padding+config.least_v_margin;
    }

    config.border = config.screen_width/10;
    if (config.uborder.value > 0) config.border = config.uborder.value;
    if (config.uborder.value == -1 && config.uborder.percent == -1){
        if (config.ucolumns == 0){
            config.border = 0;
        } else {
            config.side_border = (config.screen_width - (config.ucolumns * cell_width + (config.ucolumns - 1) * config.least_margin))/2;
            config.border = (config.screen_height - config.prompt_font_height - config.prompt_spacing - (config.urows * cell_height + (config.urows - 1) * config.least_v_margin))/2;
        }
    }

    if (config.uside_border.value == 0 && config.uside_border.percent == -1) config.side_border = config.border;
    if (config.uside_border.value > 0) config.side_border = config.uside_border.value;
    if (config.uside_border.value == -1 && config.uside_border.percent == -1){
        if (config.ucolumns == 0){
            config.side_border = 0;
        } else {
            config.side_border = (config.screen_width - (config.ucolumns * cell_width + (config.ucolumns - 1) * config.least_margin))/2;
        }
    }

    int usable_width;
    int usable_height;
    // These do while loops should run at most three times, it's just to avoid copying code
    do {
        usable_width = config.screen_width-config.side_border*2;
        usable_height = config.screen_height-config.border*2;
        usable_height = config.screen_height-config.border*2-config.prompt_spacing-config.prompt_font_height;

        // If the usable_width is too small, take some space away from the border
        if (usable_width < cell_width) {
            config.side_border = (config.screen_width - cell_width - 1)/2;
        } else if (usable_height < cell_height) {
            config.border = (config.screen_height - cell_height - config.prompt_spacing - config.prompt_font_height - 1)/2;
        }

    } while ((usable_width < cell_width && config.screen_width > cell_width) || (usable_height < cell_height && config.screen_height > cell_height));

    // just in case, make sure border is never negative
    if (config.border < 0) config.border = 0;
    if (config.side_border < 0) config.side_border = 0;

    // If columns were not manually overriden, calculate the most it can possibly contain
    if (config.ucolumns == 0){
        config.columns = usable_width/margined_cell_width;
    } else{
        config.columns = config.ucolumns;
    }
    if (config.urows == 0){
        config.rows = usable_height/margined_cell_height;
    } else{
        config.rows = config.urows;
    }

    // If we don't have space for a single column or row, force it.
    if (config.columns <= 0) {
        config.columns = 1;
    }
    if (config.rows <= 0 ) {
        config.rows = 1;
    }

    if (config.text_after){
        config.cell_width = (usable_width - config.least_margin*(config.columns - 1))/config.columns;
    }

    // The space between the icon tiles to fill all the space
    if (config.columns == 1){
        config.column_margin = (usable_width - config.cell_width*config.columns);
    } else {
        config.column_margin = (usable_width - config.cell_width*config.columns)/(config.columns - 1);
    }
    if (config.rows == 1){
        config.row_margin = (usable_height - config.cell_height*config.rows);
    } else {
        config.row_margin = (usable_height - config.cell_height*config.rows)/(config.rows - 1);
    }

    // These are kept in case manual positioning is reintroduced
    config.prompt_x = (config.side_border * config.side_border_ratio) / 50;
    config.prompt_y = (config.border * config.border_ratio) / 50;
    /*
    if(config.uside_border == 0){
        config.side_border = config.border;
    }*/
}

