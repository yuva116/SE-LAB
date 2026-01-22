#include <ctype.h>
#include <string.h>
#include "validation.h"

int validId(char id[]) {
    int i;
    if (strlen(id) == 0)
        return 0;

    for (i = 0; id[i]; i++) {
        if (!isalnum(id[i]))
            return 0;
    }
    return 1;
}

int validName(char name[]) {
    int i;
    if (strlen(name) == 0)
        return 0;

    for (i = 0; name[i]; i++) {
        if (!isalpha(name[i]))
            return 0;
    }
    return 1;
}

int validMark(int mark) {
    return (mark >= 0 && mark <= 100);
}
