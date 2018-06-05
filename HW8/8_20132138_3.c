#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "cJSON.h"

// HW8_3 : color json creator
// 20132138
// Jungwoo Song
// Usage : gcc 8_20132138_3.c cJSON.c -o 8_20132138_3.out

char* create_color_json(void);

int main(void){
    char *json;
    int fd;

    json = create_color_json();
    printf("%s\n", json);

    if( 0 < ( fd = open("./color.txt", O_WRONLY | O_CREAT, 0644))){
        write(fd, json, strlen(json));
        close(fd);
    }
    else {
        printf("File Open Error");
    }

    return 0;
}

char* create_color_json(void){
    const char* name_list[3] = {"red", "green", "blue"};
    const char* value_list[3] = {"#f00", "#0f0", "00f"};
    char* string = NULL;

    cJSON *color = NULL;
    cJSON *values = NULL;
    cJSON *value = NULL;
    cJSON *name = NULL;
    cJSON *hex = NULL;
    int i;

    color = cJSON_CreateObject();

    values = cJSON_CreateArray();
    if(values == NULL){
        goto end;
    }
    cJSON_AddItemToObject(color, "colorsArray", values);
    for(i = 0; i < 3; i++){
        value =  cJSON_CreateObject();
        if(value == NULL){
            goto end;
        }
        cJSON_AddItemToArray(values, value);
        
        name = cJSON_CreateString(name_list[i]);
        if (name == NULL){
            goto end;
        }
        cJSON_AddItemToObject(value, "colorName", name);

        hex = cJSON_CreateString(value_list[i]);
        if(hex == NULL){
            goto end;
        }
        cJSON_AddItemToObject(value, "hexValue", hex);
    }

    string = cJSON_Print(color);

end : 
    cJSON_Delete(color);
    return string;
}
