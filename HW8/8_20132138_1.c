#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "cJSON.h"

// HW8_1 : device json creator
// 20132138
// Jungwoo Song
// Usage : gcc 8_20132138_1.c cJSON.c -o 8_20132138_1.out

char* create_device_json(void);

int main(void){
    char *json;
    int fd;

    json = create_device_json();
    printf("%s\n", json);

    if( 0 < ( fd = open("./device.txt", O_WRONLY | O_CREAT, 0644))){
        write(fd, json, strlen(json));
        close(fd);
    }
    else {
        printf("File Open Error");
    }

    return 0;
}

char* create_device_json(void){
    const int value_list[3] = {20, 21, 23};
    char* string = NULL;
    cJSON *device = NULL;
    cJSON *name = NULL;
    cJSON *type = NULL;
    cJSON *values = NULL;
    cJSON *value = NULL;
    int i;

    device = cJSON_CreateObject();

    name = cJSON_CreateString("ESP32");
    if(name == NULL){
         goto end;
    }
    cJSON_AddItemToObject(device, "device", name);

    type = cJSON_CreateString("Temperature");
    if(type == NULL){
         goto end;
    }
    cJSON_AddItemToObject(device, "sensorType", type);

    values = cJSON_CreateArray();
    if(values == NULL){
        goto end;
    }
    cJSON_AddItemToObject(device, "Value", values);
    for(i = 0; i < (sizeof(value_list) /  sizeof(int)); i++){
        value = cJSON_CreateNumber(value_list[i]);
        cJSON_AddItemToArray(values, value);
    }

    string = cJSON_Print(device);

end : 
    cJSON_Delete(device);
    return string;
}
