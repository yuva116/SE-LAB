#include "student.h"

int main() {
    struct student s[MAX];
    int table[MAX][COL];
    int n;

    readStudents(s, table, &n);
    printResults(s, table, n);

    return 0;
}
