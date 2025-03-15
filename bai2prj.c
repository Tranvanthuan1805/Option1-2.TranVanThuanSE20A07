#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "students.txt"
#define MAX_NAME_LENGTH 50

typedef struct {
    int id;
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    float gpa;
} Student;

void addStudent();
void displayStudents();
void searchStudent();

int main() {
    int choice;
    do {
        printf("\n--- Quan Ly Sinh Vien ---\n");
        printf("1. Them sinh vien\n");
        printf("2. Tim kiem sinh vien\n");
        printf("3. Hien thi danh sach sinh vien\n");
        printf("0. Thoat\n");
        printf("Chon chuc nang: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: searchStudent(); break;
            case 3: displayStudents(); break;
            case 0: printf("Thoat chuong trinh\n"); break;
            default: printf("Lua chon khong hop le\n");
        }
    } while (choice != 0);

    return 0;
}

void addStudent() {
    FILE *file = fopen(FILENAME, "a");
    if (file == NULL) {
        printf("Khong the mo tep !\n");
        return;
    }

    Student student;
    printf("Moi nhap vao ID sinh vien : ");
    scanf("%d", &student.id);
    printf("Moi nhap vao ten sinh vien ( khong dau ): ");
    scanf(" %[^\n]", student.firstName);
    printf("Moi nhap vao ho sinh vien : ");
    scanf(" %[^\n]", student.lastName);
    printf("Moi nhap vao GPA cua sinh vien : ");
    scanf("%f", &student.gpa);

    fprintf(file, "%d,%s,%s,%.2f\n", student.id, student.firstName, student.lastName, student.gpa);
    fclose(file);
    printf("Sinh vien da duoc them thanh cong\n");
}

void searchStudent() {
    int searchId;
    printf("Moi nhap vao ID cua sinh vien can tim: ");
    scanf("%d", &searchId);

    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Khong the mo tep \n");
        return;
    }

    Student student;
    while (fscanf(file, "%d,%[^,],%[^,],%f\n", &student.id, student.firstName, student.lastName, &student.gpa) == 4) {
        if (student.id == searchId) {
            printf("ID sinh vien : %d, Ten sinh vien: %s, Ho: %s, GPA: %.2f\n", student.id, student.firstName, student.lastName, student.gpa);
            fclose(file);
            return;
        }
    }

    fclose(file);
    printf("Khong tim thay sinh vien voi ID %d\n", searchId);
}

void displayStudents() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("khong the mo tep \n");
        return;
    }

    Student student;
    printf("%-5s %-15s %-15s %-5s\n", "ID", "Ten", "Ho", "GPA");
    while (fscanf(file, "%d,%[^,],%[^,],%f\n", &student.id, student.firstName, student.lastName, &student.gpa) == 4) {
        printf("%-5d %-15s %-15s %.2f\n", student.id, student.firstName, student.lastName, student.gpa);
    }

    fclose(file);
}