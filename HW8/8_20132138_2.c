#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "cJSON.h"

// HW8_2 : device json parser
// 20132138
// Jungwoo Song
// Usage : gcc 8_20132138_2.c cJSON.c -o 8_20132138_2.out

char* create_device_json(void);

int main(void){
    char json[1024];
    int nread;
    int fd;

    if( 0 < ( fd = open("./device.txt", O_RDONLY))){
        nread = read(fd, json, 1024);
        json[nread] = 0;
        //puts(json);
        close(fd);
    }
    else {
        printf("File Open Error");
    }

    parse_device_json(json);

    return 0;
}

void parse_device_json(const char * const device_json){
    cJSON *device = NULL;
    cJSON *name = NULL;
    cJSON *type = NULL;
    cJSON *values = NULL;
    cJSON *value = NULL;
    int i;

    device = cJSON_Parse(device_json);

    name = cJSON_GetObjectItemCaseSensitive(device, "device");;
    printf("Device : %s\n", name->valuestring);
    
    type = cJSON_GetObjectItemCaseSensitive(device, "sensorType");
    printf("Type : %s\n", type->valuestring);

    values = cJSON_GetObjectItemCaseSensitive(device, "Value");
    printf("Value : ");
    cJSON_ArrayForEach(value, values){
        printf("%d ", value->valueint);
    }
    printf("\n");

end : 
    cJSON_Delete(device);
    return ;
}
