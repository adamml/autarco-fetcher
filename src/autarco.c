#include <autarco.h>

const char AUTARCO_BASE_URL[48] = "https://my.autarco.com/api/m1/site/";
const char AUTARCO_URL_SUFFIX_POWER[8] = "/power";
const char AUTARCO_URL_SUFFIX_ENERGY[8] = "/energy";

const char CURL_PREFIX[6] = "curl ";
const char CURL_BASIC_AUTH_FLAG[6] = " -u\"";
const char CURL_BASIC_AUTH_SEP[2] = ":";
const char CURL_BASIC_AUTH_CLOSE[2] = "\"";

void generate_file_name(int p_or_e){
    time_t t = time(NULL);
    struct tm tn = *localtime(&t);
    if(p_or_e == 0){
        printf("%d-%02d-%02d_power.json\n", tn.tm_year+1900, tn.tm_mon+1, tn.tm_mday+1);
    } else if(p_or_e == 1){
        printf("%d-%02d-%02d_energy.json\n", tn.tm_year+1900, tn.tm_mon+1, tn.tm_mday+1);
    }
}

void autarco_build_curl_request(char* return_array, 
                                char *site_id,
                                char *uname,
                                char* pwd,
                                int power_or_energy){
    int i = 0;
    int j = 0;
    while (CURL_PREFIX[i] != '\0'){
        return_array[j] = CURL_PREFIX[i];
        i++;
        j++;
    }
    
    i = 0;
    while (AUTARCO_BASE_URL[i] != '\0'){
        return_array[j] = AUTARCO_BASE_URL[i];
        i++;
        j++;
    }

    i=0;
    while (site_id[i] != '\0'){
        return_array[j] = site_id[i];
        i++;
        j++;
    }

    if(power_or_energy == 0){
        i=0;
        while (AUTARCO_URL_SUFFIX_POWER[i] != '\0'){
            return_array[j] = AUTARCO_URL_SUFFIX_POWER[i];
            i++;
            j++;
        }
    } else if(power_or_energy == 1){
        i=0;
        while (AUTARCO_URL_SUFFIX_ENERGY[i] != '\0'){
            return_array[j] = AUTARCO_URL_SUFFIX_ENERGY[i];
            i++;
            j++;
        }
    }

    i=0;
    while (CURL_BASIC_AUTH_FLAG[i] != '\0'){
        return_array[j] = CURL_BASIC_AUTH_FLAG[i];
        i++;
        j++;
    }

    i=0;
    while (uname[i] != '\0'){
        return_array[j] = uname[i];
        i++;
        j++;
    }

    i=0;
    while (CURL_BASIC_AUTH_SEP[i] != '\0'){
        return_array[j] = CURL_BASIC_AUTH_SEP[i];
        i++;
        j++;
    }

    i=0;
    while (pwd[i] != '\0'){
        return_array[j] = pwd[i];
        i++;
        j++;
    }

    i=0;
    while (CURL_BASIC_AUTH_CLOSE[i] != '\0'){
        return_array[j] = CURL_BASIC_AUTH_CLOSE[i];
        i++;
        j++;
    }
    return_array[j] = '\0';

    generate_file_name(power_or_energy);

    CURL *curl;
}