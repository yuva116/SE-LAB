#include <stdio.h>
#include <string.h>

#define MAX 100
#define SUB 5
#define COL 8   /* M1 M2 M3 M4 M5 Total Percent GradeIndex */

struct student {
    char id[20];
    char name[30];
    int marks[SUB];
    int total;
    float percent;
    char grade[3];
    float cgpa;
};

float gradeToCgpa(char g[]) {
    if (!strcmp(g, "O"))  return 10;
    if (!strcmp(g, "A+")) return 9;
    if (!strcmp(g, "A"))  return 8;
    if (!strcmp(g, "B+")) return 7;
    if (!strcmp(g, "B"))  return 6;
    if (!strcmp(g, "C"))  return 5;
    if (!strcmp(g, "D"))  return 4;
    return 0;
}

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

    s->cgpa = gradeToCgpa(s->grade);
}

int main() {
    struct student s[MAX];
    int table[MAX][COL];
    int n, i, j;
    float avg = 0, high, low;
    int gcount[8] = {0};

    FILE *fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("File cannot be opened\n");
        return 0;
    }

    fscanf(fp, "%d", &n);

    for (i = 0; i < n; i++) {
        fscanf(fp, "%s %s", s[i].id, s[i].name);

        s[i].total = 0;
        for (j = 0; j < SUB; j++) {
            fscanf(fp, "%d", &s[i].marks[j]);
            s[i].total += s[i].marks[j];
        }

        s[i].percent = s[i].total / 5.0;
        assignGrade(&s[i]);

        for (j = 0; j < SUB; j++)
            table[i][j] = s[i].marks[j];

        table[i][5] = s[i].total;
        table[i][6] = (int)(s[i].percent);
        table[i][7] = gradeIndex(s[i].grade);
    }

    fclose(fp);

    high = low = s[0].percent;

    printf("\n---------------------- STUDENT RESULT TABLE ----------------------\n");
    printf("ID        Name        M1  M2  M3  M4  M5  Total  %%   Grade\n");
    printf("-----------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("%-9s %-10s ", s[i].id, s[i].name);

        for (j = 0; j < SUB; j++)
            printf("%3d ", table[i][j]);

        printf("%5d  %3d  %-2s\n",
               table[i][5], table[i][6], s[i].grade);

        avg += s[i].percent;

        if (s[i].percent > high) high = s[i].percent;
        if (s[i].percent < low)  low = s[i].percent;

        gcount[ table[i][7] ]++;
    }

    avg /= n;

    printf("-----------------------------------------------------------------\n");
    printf("\nClass Average Percentage : %.2f\n", avg);
    printf("Highest Percentage       : %.2f\n", high);
    printf("Lowest Percentage        : %.2f\n", low);

    printf("\nGrade Distribution\n");
    printf("O:%d  A+:%d  A:%d  B+:%d  B:%d  C:%d  D:%d  F:%d\n",
           gcount[0], gcount[1], gcount[2], gcount[3],
           gcount[4], gcount[5], gcount[6], gcount[7]);

    return 0;
}
