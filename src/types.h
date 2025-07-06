#ifndef TYPES
#define TYPES

const int VERSION_MAJOR = 4; // Major version, changes when breaking backwards compatability
const int VERSION_MINOR = 7; // Minor version, changes when new functionality is added
const int VERSION_PATCH = 5; // Patch version, changes when something is changed without changing deliberate functionality (eg. a bugfix or an optimisation)

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
    struct node *next;
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
    struct button *next;
} button_t;
typedef struct shortcut
{
    char *key;
    node_t *entry;
    struct shortcut *next;
} shortcut_t;

typedef struct keynode
{
    char key[255];
    struct keynode *next;
} keynode_t;

typedef struct color
{
    int r, g, b, a;
} color_t;

typedef struct percentable
{
    int percent;
    int value;
} percentable_t;

#endif