#ifndef STUDENT_H
#define STUDENT_H

#define MAX 100
#define SUB 5
#define COL 8

struct student {
    char id[20];
    char name[30];
    int marks[SUB];
    int total;
    float percent;
    char grade[3];
    float cgpa;
};

void readStudents(struct student s[], int table[][COL], int *n);
void printResults(struct student s[], int table[][COL], int n);

#endif
