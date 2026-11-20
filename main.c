#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STUDENTS 100
#define MAX_SUBJECTS 10
struct Student {
    int roll;
    char name[50];
};
struct Subject {
    char name[50];
    int total;
    int present[MAX_STUDENTS];
};
struct Student students[MAX_STUDENTS];
struct Subject subjects[MAX_SUBJECTS];
int studentCount = 0, subjectCount = 0;
void saveData() {
    FILE *fp;
    int i, j;
    fp = fopen("students.txt", "w");
    if (fp == NULL) {
        printf("Could not save students.\n");
        return;
    }
    for (i = 0; i < studentCount; i++) {
        fprintf(fp, "%d|%s\n",
                students[i].roll, students[i].name);
    }
    fclose(fp);
    fp = fopen("subjects.txt", "w");
    if (fp == NULL) {
        printf("Could not save subjects.\n");
        return;
    }
    for (i = 0; i < subjectCount; i++) {
        fprintf(fp, "%s\n", subjects[i].name);
    }
    fclose(fp);
    fp = fopen("attendance.txt", "w");
if (fp == NULL) {
        printf("Could not save attendance.\n");
        return;
    }
    for (i = 0; i < subjectCount; i++) {
        for (j = 0; j < studentCount; j++) {
            fprintf(fp, "%d %d %d %d\n",
                    i + 1,
                    subjects[i].total,
                    students[j].roll,
                    subjects[i].present[j]);
        } }
fclose(fp);
}
void loadData() {
    FILE *fp;
    char line[100];
    int subjectNo, total, roll, present;
    int studentIndex;
    fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("students.txt not found. Starting with no students.\n");
    } else {
        while (fgets(line, sizeof(line), fp) != NULL &&
               studentCount < MAX_STUDENTS) {
            char *separator = strchr(line, '|');
            if (separator == NULL) {
                printf("Invalid student record: %s", line);
                continue;
            }
            *separator = '\0';
            students[studentCount].roll = atoi(line);
            strcpy(students[studentCount].name,
                   separator + 1);
            students[studentCount].name[
                strcspn(students[studentCount].name, "\r\n")
            ] = '\0';
            studentCount++;
        }
        fclose(fp);
    }
    fp = fopen("subjects.txt", "r");
    if (fp != NULL) {
        while (fgets(line, sizeof(line), fp) != NULL &&
               subjectCount < MAX_SUBJECTS) {
            line[strcspn(line, "\r\n")] = '\0';
            if (line[0] == '\0') {
                continue;
            }
            strcpy(subjects[subjectCount].name, line);
            subjects[subjectCount].total = 0;
            subjectCount++;
        }
        fclose(fp);
    }
    fp = fopen("attendance.txt", "r");
    if (fp != NULL) {
        while (fscanf(fp, "%d %d %d %d",
                      &subjectNo, &total, &roll, &present) == 4) {
            if (subjectNo < 1 || subjectNo > subjectCount) {
                continue;
            }
            for (studentIndex = 0;
                 studentIndex < studentCount;
                 studentIndex++) {
                if (students[studentIndex].roll == roll) {
                    break;
                }}
            if (studentIndex == studentCount) {
                continue;
            }subjects[subjectNo - 1].total = total;
            subjects[subjectNo - 1].present[studentIndex] = present;
        }
        fclose(fp);
    }printf("Students loaded: %d\n", studentCount);
    printf("Subjects loaded: %d\n", subjectCount);
}
void addStudent() {
    int roll, i;
    if (studentCount >= MAX_STUDENTS) {
        printf("Student list is full.\n");
        return;
    }
    printf("Roll number: ");
    if (scanf("%d", &roll) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }
    for (i = 0; i < studentCount; i++) {
        if (students[i].roll == roll) {
            printf("Roll number already exists.\n");
            return;
        }}
    students[studentCount].roll = roll;
    printf("Student name: ");
    if (scanf(" %49[^\n]", students[studentCount].name) != 1) {
        printf("Invalid name.\n");
        return;
    }
    studentCount++;
    saveData();
    printf("Student added successfully.\n");
}
void viewStudents() {
    int i;
    if (studentCount == 0) {
        printf("No students registered.\n");
        return;
    }
    printf("\n--- Student List ---\n");
    for (i = 0; i < studentCount; i++) {
        printf("%d | %s\n",
               students[i].roll,
               students[i].name);
    }}
void addSubject() {
    if (subjectCount >= MAX_SUBJECTS) {
        printf("Subject limit reached.\n");
        return;
    }
    printf("Subject name: ");
    if (scanf(" %49[^\n]", subjects[subjectCount].name) != 1) {
        printf("Invalid subject name.\n");
        return;
    }
    subjects[subjectCount].total = 0;
    subjectCount++;
    saveData();
    printf("Subject added successfully.\n");
}
void viewSubjects() {
    int i;
    if (subjectCount == 0) {
        printf("No subjects registered.\n");
        return;
    }
    printf("\n--- Subject List ---\n");
    for (i = 0; i < subjectCount; i++) {
        printf("%d. %s\n", i + 1, subjects[i].name);
    }}
float percentage(int present, int total) {
    if (total == 0) {
        return 0;
    }
    return present * 100.0f / total;
}
void markAttendance() {
    int id, i, choice;
    if (studentCount == 0 || subjectCount == 0) {
        printf("Add students and subjects first.\n");
        return;
    }
    viewSubjects();
    printf("Subject number: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }
    if (id < 1 || id > subjectCount) {
        printf("Invalid subject.\n");
        return;
    }
    printf("Enter 1 for present and 0 for absent.\n");
    for (i = 0; i < studentCount; i++) {
        printf("%s (%d): ",
               students[i].name,
               students[i].roll);
        if (scanf("%d", &choice) != 1 ||
            (choice != 0 && choice != 1)) {
            printf("Invalid input. Please restart attendance marking.\n");
            while (getchar() != '\n');
            return;
        }
        subjects[id - 1].present[i] += choice;
    }
    subjects[id - 1].total++;
    saveData();
    printf("Attendance recorded successfully.\n");
}
void attendanceReport() {
    int i, j;
    if (subjectCount == 0) {
        printf("Add a subject first.\n");
        return;
    }
    if (studentCount == 0) {
        printf("No students registered.\n");
        return;
    }
    for (j = 0; j < subjectCount; j++) {
        printf("\n--- %s ---\n", subjects[j].name);
        if (subjects[j].total == 0) {
            printf("No classes recorded.\n");
            continue;
        }
        for (i = 0; i < studentCount; i++) {
            printf("%s: %d/%d (%.2f%%)\n",
                   students[i].name,
                   subjects[j].present[i],
                   subjects[j].total,
                   percentage(subjects[j].present[i],
                              subjects[j].total));
        }}}
void findDefaulters() {
    int i, j, found = 0;
    for (j = 0; j < subjectCount; j++) {
        for (i = 0; i < studentCount; i++) {
            if (subjects[j].total > 0 &&
                subjects[j].present[i] * 100 <
                75 * subjects[j].total) {
                printf("%s | %s | %.2f%%\n",
                       students[i].name,
                       subjects[j].name,
                       percentage(subjects[j].present[i],
                                  subjects[j].total));
                found = 1;
            } } }
    if (!found) {
        printf("No students below 75%%, or no classes have been recorded.\n");
    }
}
void attendanceCalculator() {
    int roll, id, i, present, total, needed = 0;
    float target, current;
    printf("Student roll number: ");
    if (scanf("%d", &roll) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }
    for (i = 0; i < studentCount; i++) {
        if (students[i].roll == roll) {
            break;
        }
    }
    if (i == studentCount) {
        printf("Student not found.\n");
        return;
    }
    viewSubjects();
    printf("Subject number: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }
    if (id < 1 || id > subjectCount ||
        subjects[id - 1].total == 0) {
        printf("Invalid subject or no classes recorded.\n");
        return;
    }
    printf("Target percentage (e.g. 75 or 80): ");
    if (scanf("%f", &target) != 1 ||
        target <= 0 || target > 100) {
        printf("Enter a target above 0 and at most 100.\n");
        while (getchar() != '\n');
        return;
    }
    present = subjects[id - 1].present[i];
    total = subjects[id - 1].total;
    current = percentage(present, total);
    printf("Current attendance: %.2f%%\n", current);
    if (current >= target) {
        int absences =
            (int)(present * 100.0 / target - total + 0.000001);
        printf("Target already reached.\n");
        printf("Maximum future absences: %d\n", absences);
        return;
    }
    if (target == 100) {
        printf("Attend every future class to approach 100%%.\n");
        printf("Exact 100%% cannot be reached after a past absence.\n");
        return;
    }
    while ((present + needed) * 100.0 <
           target * (total + needed)) {
        needed++;
    }
    printf("Attend the next %d classes consecutively to reach %.2f%%.\n",
           needed, target);
}
/* Main menu */
int main() {
    int choice;
    loadData();
    do {
        printf("\n======= ATTENDWISE =======\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Add Subject\n");
        printf("4. View Subjects\n");
        printf("5. Mark Attendance\n");
        printf("6. Attendance Report\n");
        printf("7. Students Below 75%%\n");
        printf("8. Smart Attendance Calculator\n");
        printf("9. Exit\n");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                viewStudents();
                break;
            case 3:
                addSubject();
                break;
            case 4:
                viewSubjects();
                break;
            case 5:
                markAttendance();
                break;
            case 6:
                attendanceReport();
                break;
            case 7:
                findDefaulters();
                break;
            case 8:
                attendanceCalculator();
                break;
            case 9:
                saveData();
                printf("Data saved. Goodbye!\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 9);
    return 0;
}
