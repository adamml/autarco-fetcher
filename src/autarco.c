#include <autarco.h>

const char AUTARCO_BASE_URL[48] = "https://my.autarco.com/api/m1/site/";
const char AUTARCO_URL_SUFFIX_POWER[8] = "/power";
const char AUTARCO_URL_SUFFIX_ENERGY[8] = "/energy";

const char CURL_PREFIX[6] = "curl ";
const char CURL_BASIC_AUTH_FLAG[6] = " -u\"";
const char CURL_BASIC_AUTH_SEP[2] = ":";
const char CURL_BASIC_AUTH_CLOSE[2] = "\"";

struct string {
  char *ptr;
  size_t len;
};

void init_string(struct string *s) {
  s->len = 0;
  s->ptr = malloc(s->len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, void *s)
{
  struct string *ss = (struct string *)s;
  size_t new_len = ss->len + size*nmemb;
  ss->ptr = realloc(ss->ptr, new_len+1);
  if (ss->ptr == NULL) {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(ss->ptr+ss->len, ptr, size*nmemb);
  ss->ptr[new_len] = '\0';
  ss->len = new_len;

  return size*nmemb;
}

void generate_file_name(char *res, char *outdir, int p_or_e){
    time_t t = time(NULL);
    struct tm tn = *localtime(&t);
    char dash[12] = "-";
    char year[12];
    sprintf(year, "%d", tn.tm_year+1900);
    char month[12];
    sprintf(month, "%02d", tn.tm_mon+1);
    char day[12];
    sprintf(day, "%02d", tn.tm_mday+1);
    char dot_json[6] = ".json";

    int i=0;
    int j=0;
    while(outdir[i] != '\0'){
        res[j] = outdir[i];
        i++;
        j++;
    }
    i=0;
    while(year[i] != '\0'){
        res[j] = year[i];
        i++;
        j++;
    }
    i=0;
    while(dash[i] != '\0'){
        res[j] = dash[i];
        i++;
        j++;
    }
    i=0;
    while(month[i] != '\0'){
        res[j] = month[i];
        i++;
        j++;
    }
    i=0;
    while(dash[i] != '\0'){
        res[j] = dash[i];
        i++;
        j++;
    }
    i = 0;
    while(day[i] != '\0'){
        res[j] = day[i];
        i++;
        j++;
    }
    i=0;
    while(dash[i] != '\0'){
        res[j] = dash[i];
        i++;
        j++;
    }

    if(p_or_e == 0){
        i = 1;
        while(AUTARCO_URL_SUFFIX_POWER[i] != '\0'){
            res[j] = AUTARCO_URL_SUFFIX_POWER[i];
            i++;
            j++;
        }
    } else if(p_or_e == 1){
        i = 1;
        while(AUTARCO_URL_SUFFIX_ENERGY[i] != '\0'){
            res[j] = AUTARCO_URL_SUFFIX_ENERGY[i];
            i++;
            j++;
        }
    }
    i = 0;
    while(dot_json[i] != '\0'){
        res[j] = dot_json[i];
        i++;
        j++;
    }
    res[j] = '\0';
}

void autarco_build_curl_request(char *site_id,
                                char *uname,
                                char *pwd,
                                char *outdir,
                                int power_or_energy){
    char return_array[2048];
    int i = 0;
    int j = 0;

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
    return_array[j] = '\0';

    CURL* curl = curl_easy_init();
    if(curl)
    {
        CURLcode res;
        struct string s;
		init_string(&s);
        curl_easy_setopt(curl, CURLOPT_URL, return_array);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&s);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_USERNAME, uname);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, pwd);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK){
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
      		res = curl_easy_perform(curl);
		}
        if(res == CURLE_OK){
            char outname[756];
            generate_file_name(outname, outdir, power_or_energy);
            FILE *fid = fopen(outname, "w");
            if(fid){
                fprintf(fid, s.ptr);
            }
            fclose(fid);
        }
    }
    curl_easy_cleanup(curl);
}