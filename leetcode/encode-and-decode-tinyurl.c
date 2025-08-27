#define MAX_URLS 10000
#define BASE_URL "http://tinyurl.com/"


char* url_store[MAX_URLS];
int url_count = 0;

char* encode(char* longUrl) {
    url_store[url_count] = strdup(longUrl); 


    char* shortUrl = (char*)malloc(100);
    sprintf(shortUrl, "%s%d", BASE_URL, url_count);

    url_count++;
    return shortUrl;
}


char* decode(char* shortUrl) {
    int id;
    sscanf(shortUrl + strlen(BASE_URL), "%d", &id);  
    return url_store[id];
}

