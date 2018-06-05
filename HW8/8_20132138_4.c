#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "cJSON.h"

// HW8_4 : color json parser
// 20132138
// Jungwoo Song
// Usage : gcc 8_20132138_4.c cJSON.c -o 8_20132138_4.out

char* create_color_json(void);

int main(void){
    char json[1024];
    int nread;
    int fd;

    if( 0 < ( fd = open("./color.txt", O_RDONLY))){
        nread = read(fd, json, 1024);
        json[nread] = 0;
        puts(json);
        close(fd);
    }
    else {
        printf("File Open Error");
    }

    parse_color_json(json);

    return 0;
}

void parse_color_json(const char * const color_json){
    cJSON *color = NULL;
    cJSON *values = NULL;
    cJSON *value = NULL;
    cJSON *name = NULL;
    cJSON *hex = NULL;
    int i;

    color = cJSON_Parse(color_json);

    values = cJSON_GetObjectItemCaseSensitive(color, "colorsArray");
    printf("Colors : ");
    cJSON_ArrayForEach(value, values){
        name = cJSON_GetObjectItemCaseSensitive(value, "colorName");
        hex = cJSON_GetObjectItemCaseSensitive(value, "hexValue");
        printf("(%s : %s)  ", name->valuestring, hex->valuestring);
    }
    printf("\n");

end : 
    cJSON_Delete(color);
    return ;
}
