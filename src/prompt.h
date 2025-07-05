#ifndef PROMPT_H
#define PROMPT_H

#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include "./type.c"
void show_help();


enum exit_code {
    OKAY,
    ESCAPE = 0x20,
    RIGHTCLICK,
    VOIDCLICK,
    FOCUSLOST,
    INTERNALCMD,
    LOCKERROR = 0x40,
    ALLOCERROR,
    FONTERROR,
    CONFIGERROR,
    WINERROR,
    LOCALEERROR,
    INPUTMERROR,
    INPUTCERROR,
    POLLERROR,
    EXTERNALERROR
};


static struct option long_options[] =
    {
        {"tc",                    required_argument, 0, 1009},
        {"textcolor",             required_argument, 0, 1009},
        {"pc",                    required_argument, 0, 1010},
        {"promptcolor",           required_argument, 0, 1010},
        {"backgroundcolor",       required_argument, 0, 1011},
        {"bc",                    required_argument, 0, 1011},
        {"hc",                    required_argument, 0, 1012},
        {"highlightcolor",        required_argument, 0, 1012},
        {"name",                  required_argument, 0, 1013},
        {"config",                required_argument, 0, 1014},
        {"bgfill",                no_argument,       0, 1015},
        {"focuslostterminate",    no_argument,       0, 1016},
        {"borderratio",           required_argument, 0, 1017},
        {"sideborderratio",       required_argument, 0, 1018},
        {"noscroll",              no_argument,       0, 1019},
        {"iconvpadding",          required_argument, 0, 1020},
        {"shadowcolor",           required_argument, 0, 1021},
        {"sc",                    required_argument, 0, 1021},
        {"title",                 required_argument, 0, 1022},
        {"icon",                  required_argument, 0, 1025},
        {"scrollbarcolor",        required_argument, 0, 1023},
        {"scrollindicatorcolor",  required_argument, 0, 1024},
        {"stdinpolltimeout",      required_argument, 0, 1026},
        {"button",                required_argument, 0, 'A'},
        {"textafter",             no_argument,       0, 'a'},
        {"border",                required_argument, 0, 'b'},
        {"sideborder",            required_argument, 0, 'B'},
        {"center",                no_argument,       0, 'C'},
        {"columns",               required_argument, 0, 'c'},
        {"desktop",               no_argument,       0, 'd'},
        {"hidemissing",           no_argument,       0, 'e'},
        {"font",                  required_argument, 0, 'f'},
        {"promptfont",            required_argument, 0, 'F'},
        {"background",            required_argument, 0, 'g'},
        {"rootwindowbackground",  no_argument,       0, 'G'},
        {"height",                required_argument, 0, 'h'},
        {"help",                  no_argument,       0, 'H'},
        {"iconpadding",           required_argument, 0, 'I'},
        {"input",                 required_argument, 0, 'i'},
        {"highlight",             required_argument, 0, 'L'},
        {"leastmargin",           required_argument, 0, 'l'},
        {"clearmemory",           no_argument,       0, 'M'},
        {"multiple",              no_argument,       0, 'm'},
        {"noprompt",              no_argument,       0, 'n'},
        {"notitle",               no_argument,       0, 'N'},
        {"outputonly",            no_argument,       0, 'o'},
        {"textotherside",         no_argument,       0, 'O'},
        {"prompt",                required_argument, 0, 'p'},
        {"promptspacing",         required_argument, 0, 'P'},
        {"dontquit",              no_argument,       0, 'q'},
        {"reverse",               no_argument,       0, 'R'},
        {"rows",                  required_argument, 0, 'r'},
        {"iconsize",              required_argument, 0, 's'},
        {"selectonly",            no_argument,       0, 'S'},
        {"textpadding",           required_argument, 0, 'T'},
        {"voidclickterminate",    no_argument,       0, 't'},
        {"shortcuts",             required_argument, 0, 'U'},
        {"upsidedown",            no_argument,       0, 'u'},
        {"leastvmargin",          required_argument, 0, 'V'},
        {"version",               no_argument,       0, 'v'},
        {"width",                 required_argument, 0, 'w'},
        {"windowed",              no_argument,       0, 'W'},
        {"paddingswap",           no_argument,       0, 'X'},
        {"xposition",             required_argument, 0, 'x'},
        {"yposition",             required_argument, 0, 'y'},
        {0, 0, 0, 0}
    };

#endif