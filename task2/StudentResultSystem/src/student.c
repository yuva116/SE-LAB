#include <stdio.h>
#include "student.h"
#include "grade.h"
#include "validation.h"

void readStudents(struct student s[], int table[][COL], int *n) {
    int i, j;
    FILE *fp = fopen("students.txt", "r");

    if (!fp) {
        printf("Error opening file\n");
        return;
    }

    fscanf(fp, "%d", n);

    for (i = 0; i < *n; i++) {
        fscanf(fp, "%s %s", s[i].id, s[i].name);

        if (!validId(s[i].id) || !validName(s[i].name)) {
            printf("Invalid ID or Name at record %d\n", i + 1);
            fclose(fp);
            return;
        }

        s[i].total = 0;

        for (j = 0; j < SUB; j++) {
            fscanf(fp, "%d", &s[i].marks[j]);

            if (!validMark(s[i].marks[j])) {
                printf("Invalid marks for %s\n", s[i].id);
                fclose(fp);
                return;
            }

            s[i].total += s[i].marks[j];
        }

        s[i].percent = s[i].total / 5.0;
        assignGrade(&s[i]);

        for (j = 0; j < SUB; j++)
            table[i][j] = s[i].marks[j];

        table[i][5] = s[i].total;
        table[i][6] = (int)s[i].percent;
        table[i][7] = gradeIndex(s[i].grade);
    }

    fclose(fp);
}

void printResults(struct student s[], int table[][COL], int n) {
    int i, j;
    float avg = 0, high, low;
    int gcount[8] = {0};

    high = low = s[0].percent;

    printf("\n---------------- STUDENT RESULT ----------------\n");
    printf("ID     Name     M1 M2 M3 M4 M5 Tot %%  Grade CGPA\n");
    printf("------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("%-6s %-8s ", s[i].id, s[i].name);

        for (j = 0; j < SUB; j++)
            printf("%3d", table[i][j]);

        printf("%4d %3d %-5s %.1f\n",
               s[i].total,
               (int)s[i].percent,
               s[i].grade,
               s[i].cgpa);

        avg += s[i].percent;

        if (s[i].percent > high) high = s[i].percent;
        if (s[i].percent < low)  low = s[i].percent;

        gcount[ gradeIndex(s[i].grade) ]++;
    }

    avg /= n;

    printf("------------------------------------------------\n");
    printf("Class Average : %.2f\n", avg);
    printf("Highest %%     : %.2f\n", high);
    printf("Lowest %%      : %.2f\n", low);

    printf("\nGrade Distribution\n");
    printf("O:%d A+:%d A:%d B+:%d B:%d C:%d D:%d F:%d\n",
           gcount[0], gcount[1], gcount[2], gcount[3],
           gcount[4], gcount[5], gcount[6], gcount[7]);
}
