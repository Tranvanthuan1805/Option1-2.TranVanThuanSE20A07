#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define FILE_NAME "products.bin"

typedef struct {
    int product_id;
    char product_name[MAX_NAME_LENGTH];
    float price;
    int quantity;
} Product;

void writeProductsToFile();
void appendProductsToFile();
void readProductsFromFile();
void modifyProductById();

int main() {
    int choice;

    do {
        printf("\n--- Quan Ly San Pham ---\n");
        printf("1. Ghi san pham \n");
        printf("2. Them san pham\n");
        printf("3. Xem san pham\n");
        printf("4. Sua san pham\n");
        printf("0. Thoat\n");
        printf("Moi ban nhap vao lua chon : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: writeProductsToFile(); break;
            case 2: appendProductsToFile(); break;
            case 3: readProductsFromFile(); break;
            case 4: modifyProductById(); break;
            case 0: printf("Thoat chuong trinh\n"); break;
            default: printf("Lua chon khong hop le\n");
        }
    } while (choice != 0);

    return 0;
}

void writeProductsToFile() {
    FILE *file = fopen(FILE_NAME, "wb");
    if (file == NULL) {
        printf("Loi mo tep de ghi\n");
        return;
    }

    Product product;
    printf("Nhap thong tin san pham (ID = 0 de ket thuc):\n");

    while (1) {
        printf("ID: ");
        scanf("%d", &product.product_id);
        if (product.product_id == 0) break;
        printf("Ten: ");
        scanf(" %[^\n]", product.product_name);
        printf("Gia: ");
        scanf("%f", &product.price);
        printf("So luong: ");
        scanf("%d", &product.quantity);
        fwrite(&product, sizeof(Product), 1, file);
    }

    fclose(file);
    printf("Ghi du lieu thanh cong\n");
}

void appendProductsToFile() {
    FILE *file = fopen(FILE_NAME, "ab");
    if (file == NULL) {
        printf("Loi mo tep de them\n");
        return;
    }

    Product product;
    printf("Nhap thong tin san pham (ID = 0 de ket thuc):\n");

    while (1) {
        printf("ID: ");
        scanf("%d", &product.product_id);
        if (product.product_id == 0) break;
        printf("Ten: ");
        scanf(" %[^\n]", product.product_name);
        printf("Gia: ");
        scanf("%f", &product.price);
        printf("So luong: ");
        scanf("%d", &product.quantity);

        fwrite(&product, sizeof(Product), 1, file);
    }

    fclose(file);
    printf("Them du lieu thanh cong\n");
}

void readProductsFromFile() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("Loi mo tep de doc\n");
        return;
    }

    Product product;
    printf("%-10s %-50s %-10s %-10s\n", "ID", "Ten", "Gia", "So luong");

    while (fread(&product, sizeof(Product), 1, file) == 1) {
        printf("%-10d %-50s %-10.2f %-10d\n", product.product_id, product.product_name, product.price, product.quantity);
    }

    fclose(file);
}

void modifyProductById() {
    FILE *file = fopen(FILE_NAME, "r+b");
    if (file == NULL) {
        printf("Loi mo tep de sua\n");
        return;
    }

    int id_sua;
    printf("Nhap ID san pham can sua: ");
    scanf("%d", &id_sua);

    Product product;
    int tim_thay = 0;

    while (fread(&product, sizeof(Product), 1, file) == 1) {
        if (product.product_id == id_sua) {
            tim_thay = 1;
            printf("Nhap ten moi: ");
            scanf(" %[^\n]", product.product_name);
            printf("Nhap gia moi: ");
            scanf("%f", &product.price);
            printf("Nhap so luong moi: ");
            scanf("%d", &product.quantity);

            fseek(file, -sizeof(Product), SEEK_CUR);
            fwrite(&product, sizeof(Product), 1, file);
            break;
        }
    }

    fclose(file);
    if (tim_thay) printf("Sua san pham thanh cong\n");
    else printf("Khong tim thay ID %d\n", id_sua);
}