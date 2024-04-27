#include <autarco.h>
#include <conf_reader.h>
#include <stdio.h>

int main (int argc, char *argv[]){

    struct conf c;
    conf_reader(&c, argv[1]);
    
    autarco_build_curl_request(c.AUTARCO_SITE_ID,
                               c.AUTARCO_UNAME,
                               c.AUTARCO_PWD,
                               c.AUTARCO_OUT_DIR,
                               0);
                               
    autarco_build_curl_request(c.AUTARCO_SITE_ID,
                               c.AUTARCO_UNAME,
                               c.AUTARCO_PWD,
                               c.AUTARCO_OUT_DIR,
                               1);

    return 0;
}