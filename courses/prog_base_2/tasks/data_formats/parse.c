#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "cJSON.h"
#include "parse.h"
#include "scientist.h"

void parse(char * text, scientist ** s)
{
	cJSON * j = cJSON_Parse(text);
    int count = cJSON_GetArraySize(j);
   for (int i = 0; i < count; i++) {
        cJSON * jElem = cJSON_GetArrayItem(j, i);
        char * name = cJSON_GetObjectItem(jElem, "name")->valuestring;
        char * surname = cJSON_GetObjectItem(jElem, "surname")->valuestring;
        char * birthdate = cJSON_GetObjectItem(jElem, "birthdate")->valuestring;
        //char * papers = cJSON_GetObjectItem(jElem, "theNumberOfScientificPapers")->valuestring;
        int  papers = cJSON_GetObjectItem(jElem, "theNumberOfScientificPapers")->valueint;
        double experience = cJSON_GetObjectItem(jElem, "experience")->valuedouble;
        cJSON * jCompany = cJSON_GetObjectItem(jElem, "company");
        char * comp_name = cJSON_GetObjectItem(jCompany, "name")->valuestring;
        char * deparment = cJSON_GetObjectItem(jCompany, "deparment")->valuestring;
        scientist_fill(s[i],name,surname,birthdate,papers,experience,comp_name,deparment);
        }
    cJSON_Delete(j);
}
