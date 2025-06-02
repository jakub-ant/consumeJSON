#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>

int outputValueOfScannedKey(cJSON *jsonFile)
{
    char *key = malloc(64);

    scanf("%s", key);

    cJSON *keyValPair = cJSON_GetObjectItemCaseSensitive(jsonFile, key);

    if (keyValPair == NULL)
    {
        printf("Not found");
        return 0;
    }

    printf("%s: %s", key, keyValPair->valuestring);
}

int main()
{
    CURL *curl;
    curl = curl_easy_init();

    CURLcode res;

    curl_easy_setopt(curl, CURLOPT_URL, "https://api.nbp.pl/api/exchangerates/rates/c/usd/today/?format=json");

    res = curl_easy_perform(curl);

    if (res == CURLE_OK)
    {
        printf("ok");
        return 0;
    }

    FILE *file = fopen("file.json", "r");
    if (file == NULL)
    {
        printf("Error: Unable to open the file.\n");
        return 1;
    }

    char *buffer = malloc(255);

    int len = fread(buffer, 1, 255, file);

    fclose(file);

    cJSON *jsonFile = cJSON_Parse(buffer);

    free(buffer);

    outputValueOfScannedKey(jsonFile);
    return 0;
}