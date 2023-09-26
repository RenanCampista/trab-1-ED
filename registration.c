#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registration.h"

Registration *registration_constroy() {
    Registration *r = (Registration *) calloc(1, sizeof(Registration));
    if (r == NULL)
        exit(printf("Problema ao alocar uma matrícula."));
    
    return r;
}

void registration_destruct(Registration *r) {
    if (r != NULL)
        free(r);
}