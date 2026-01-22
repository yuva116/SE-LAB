#include <string.h>
#include "cgpa.h"

float calculateCgpa(char grade[]) {
    if (!strcmp(grade, "O"))  return 10.0;
    if (!strcmp(grade, "A+")) return 9.0;
    if (!strcmp(grade, "A"))  return 8.0;
    if (!strcmp(grade, "B+")) return 7.0;
    if (!strcmp(grade, "B"))  return 6.0;
    if (!strcmp(grade, "C"))  return 5.0;
    if (!strcmp(grade, "D"))  return 4.0;
    return 0.0;
}
