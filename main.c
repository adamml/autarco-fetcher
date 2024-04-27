#include <autarco.h>
#include <conf_reader.h>
#include <stdio.h>

int main (void){

    struct conf c;
    conf_reader(&c, "conf.toml");

    char autarco_curl_command_power[2048];
    char autarco_curl_command_energy[2048];
    
    autarco_build_curl_request(autarco_curl_command_power,
                               c.AUTARCO_SITE_ID,
                               c.AUTARCO_UNAME,
                               c.AUTARCO_PWD,
                               0);
    autarco_build_curl_request(autarco_curl_command_energy,
                               c.AUTARCO_SITE_ID,
                               c.AUTARCO_UNAME,
                               c.AUTARCO_PWD,
                               1);
    printf("%s\n", autarco_curl_command_power);
    printf("%s\n", autarco_curl_command_energy);

    return 0;
}