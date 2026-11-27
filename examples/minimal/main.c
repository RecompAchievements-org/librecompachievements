// Smallest program that links librecompachievements; it grows into a console "game" with the SDK.
#include <rca/rca.h>

#include <stdio.h>

int main(void) {
    printf("librecompachievements %s\n", rca_version());
    return 0;
}
