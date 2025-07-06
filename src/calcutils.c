#include "types.h"

void calculate_percentage(int maxvalue, percentable_t* percentable)
{
    if(percentable->percent != -1) {
        percentable->value = (maxvalue * percentable->percent) / 100;
    }
}
