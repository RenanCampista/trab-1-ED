#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registration.h"

Registration *registration_construct() {
    Registration *r = (Registration *) calloc(1, sizeof(Registration));
    if (r == NULL)
        exit(printf("Problema ao alocar uma matrícula."));
    
    return r;
}

void registration_destroy(Registration *r) {
    if (r != NULL)
        free(r);
}

void registration_read(Registration *r) {
    //Falta terminar
    scanf("%f", &r->presence_percentage);
}