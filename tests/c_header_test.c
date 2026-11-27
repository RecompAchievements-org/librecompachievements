#include "rca/rca.h"

#include <stdio.h>
#include <string.h>

int main(void) {
    if (strcmp(rca_version(), RCA_VERSION_STRING) != 0) {
        fprintf(stderr, "Library version %s does not match header version %s\n", rca_version(),
                RCA_VERSION_STRING);
        return 1;
    }
    return 0;
}
