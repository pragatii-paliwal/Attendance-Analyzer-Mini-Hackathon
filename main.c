
#include <stdio.h>

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

void addStudent() {
    int roll, i;
    if (studentCount == MAX_STUDENTS) {
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
    printf("Student added.\n");
}
void viewStudents() {
    int i;

    for (i = 0; i < studentCount; i++)
        printf("%d | %s\n", students[i].roll, students[i].name);

    if (studentCount == 0)
        printf("No students registered.\n");
}

void addSubject() {
    if (subjectCount == MAX_SUBJECTS) {
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
    printf("Subject added.\n");
}
void viewSubjects() {
    int i;
    for (i = 0; i < subjectCount; i++)
        printf("%d. %s\n", i + 1, subjects[i].name);
    if (subjectCount == 0)
        printf("No subjects registered.\n");
}
float percentage(int present, int total) {
    if (total == 0)
        return 0;

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
    printf("Enter 1 for present, 0 for absent.\n");
for (i = 0; i < studentCount; i++) {
        printf("%s (%d): ", students[i].name, students[i].roll);

        if (scanf("%d", &choice) != 1 ||
            (choice != 0 && choice != 1)) {
            printf("Invalid input. Please restart attendance marking.\n");
            while (getchar() != '\n');
            return;
        }

        subjects[id - 1].present[i] += choice;
    }
    subjects[id - 1].total++;
    printf("Attendance recorded.\n");
}
void attendanceReport() {
    int i, j;

    for (j = 0; j < subjectCount; j++) {
        printf("\n%s\n", subjects[j].name);

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
        }}
if (subjectCount == 0)
        printf("Add a subject first.\n");
}
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
            }
        }
    }

    if (!found)
        printf("No students below 75%%, or no classes have been recorded.\n");
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
        if (students[i].roll == roll)
            break;
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
        int absences = (int)(present * 100.0 / target - total + 0.000001);

        printf("Target already reached.\n");
        printf("Maximum future absences: %d\n", absences);
        return;
    }
    if (target == 100) {
        printf("Attend every future class to approach 100%%; exact 100%% is impossible after any past absence.\n");
        return;
    }
     while ((present + needed) * 100.0 <
           target * (total + needed)) {
        needed++;
    }
    printf("Attend the next %d classes consecutively to reach %.2f%%.\n",
           needed, target);
}

int main() {
    int choice;

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
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 9);
    return 0;
}
