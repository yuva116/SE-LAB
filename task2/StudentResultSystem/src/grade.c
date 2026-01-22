#include <string.h>
#include "student.h"
#include "grade.h"
#include "cgpa.h"

int gradeIndex(char g[]) {
    if (!strcmp(g, "O"))  return 0;
    if (!strcmp(g, "A+")) return 1;
    if (!strcmp(g, "A"))  return 2;
    if (!strcmp(g, "B+")) return 3;
    if (!strcmp(g, "B"))  return 4;
    if (!strcmp(g, "C"))  return 5;
    if (!strcmp(g, "D"))  return 6;
    return 7;
}

void assignGrade(struct student *s) {
    if (s->percent >= 90) strcpy(s->grade, "O");
    else if (s->percent >= 85) strcpy(s->grade, "A+");
    else if (s->percent >= 75) strcpy(s->grade, "A");
    else if (s->percent >= 65) strcpy(s->grade, "B+");
    else if (s->percent >= 60) strcpy(s->grade, "B");
    else if (s->percent >= 55) strcpy(s->grade, "C");
    else if (s->percent >= 50) strcpy(s->grade, "D");
    else strcpy(s->grade, "F");

    s->cgpa = calculateCgpa(s->grade);
}
