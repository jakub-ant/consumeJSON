#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h>

int main()
{
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

    cJSON *email = cJSON_GetObjectItemCaseSensitive(jsonFile, "email");
    printf("email: %s", email->valuestring);

    return 0;
}