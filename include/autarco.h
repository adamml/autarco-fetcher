#ifndef COM_GITHUB_ADAMML_AUTARCOFETCHER_AUTARCO
#define COM_GITHUB_ADAMML_AUTARCOFETCHER_AUTARCO

#include <time.h>
#include <stdio.h>
#include <curl/curl.h>

void autarco_build_curl_request(char *site_id,
                                char *uname,
                                char* pwd,
                                char* outdir,
                                int power_or_energy);

#endif