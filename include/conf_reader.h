#ifndef COM_GITHUB_ADAMML_AUTARCOFETCHER_CONFREADER
#define COM_GITHUB_ADAMML_AUTARCOFETCHER_CONFREADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct conf {
    char AUTARCO_UNAME[256];
    char AUTARCO_PWD[256];
    char AUTARCO_SITE_ID[64];
    char AUTARCO_OUT_DIR[512]; 
};

void conf_reader(struct conf *c, char* f);

#endif