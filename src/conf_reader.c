#include <conf_reader.h>

void conf_reader(struct conf *c, char* f){
    char line[2048];
    int autarco = 0;

    FILE *fid = fopen(f, "r");
    char *subString;
    if(fid){
        while(fgets(line, 2048, fid)){
            if(autarco == 1){
                if(strncmp(line, "site_id = ", 10) == 0){
                    subString = strtok(line, "\"");
                    subString = strtok(NULL, "\"");
                    if(subString){strncpy(c->AUTARCO_SITE_ID, subString, 63);}
                } else if (strncmp(line, "uname = ", 8) == 0)
                {
                    subString = strtok(line, "\"");
                    subString = strtok(NULL, "\"");
                    if(subString){strncpy(c->AUTARCO_UNAME, subString, 255);}
                } else if (strncmp(line, "pwd = ", 6) == 0){
                    subString = strtok(line, "\"");
                    subString = strtok(NULL, "\"");
                    if(subString){strncpy(c->AUTARCO_PWD, subString, 255);}
                } else if (strncmp(line, "outdir = ", 9) == 0)
                {
                    subString = strtok(line, "\"");
                    subString = strtok(NULL, "\"");
                    if(subString){strncpy(c->AUTARCO_OUT_DIR, subString, 511);}
                }
            }
            if(strncmp(line, "[autarco]", 9) == 0){
                autarco = 1;
            }
        }
        fclose(fid);
    } else {
        exit(-1);
    }

    return;
}