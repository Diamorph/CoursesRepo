#include "cJSON.h"
#include "parse.h"

void parse(scientist_t  ** sc)
{
    FILE * file = fopen("Scientist.json", "r");
    char text[10000];
    char line[100];

    while(fgets(line, 100, file) != NULL)
    {
        strcat(text, line);
    }
    fclose(file);

    cJSON * jList = cJSON_Parse(text);
    if (!jList)
    {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr());
        return;
    }

    for (int i = 0; i < cJSON_GetArraySize(jList); i++)
    {
        cJSON * jItem = cJSON_GetArrayItem(jList, i);
        char * name = cJSON_GetObjectItem(jItem, "name")->valuestring;
        char * surname = cJSON_GetObjectItem(jItem, "surname")->valuestring;
        char * date = cJSON_GetObjectItem(jItem, "date")->valuestring;
        int salary = cJSON_GetObjectItem(jItem, "salary")->valueint;
        double age = cJSON_GetObjectItem(jItem, "age")->valuedouble;

        Scientist_set(sc[i], name, surname, age, date, salary);
    }
    cJSON_Delete(jList);
}
