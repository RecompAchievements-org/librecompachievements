#include <rca/rca.h>

#include <string.h>

int main(void) {
    return strcmp(rca_version(), RCA_VERSION_STRING) == 0 ? 0 : 1;
}
