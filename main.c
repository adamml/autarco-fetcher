#include <autarco.h>
#include <conf_reader.h>
#include <stdio.h>

int main (void){

    struct conf c;
    conf_reader(&c, "conf.toml");
    
    autarco_build_curl_request(c.AUTARCO_SITE_ID,
                               c.AUTARCO_UNAME,
                               c.AUTARCO_PWD,
                               0);
                               
    autarco_build_curl_request(c.AUTARCO_SITE_ID,
                               c.AUTARCO_UNAME,
                               c.AUTARCO_PWD,
                               1);

    return 0;
}