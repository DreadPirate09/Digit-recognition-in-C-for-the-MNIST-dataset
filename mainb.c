#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_PIXELS 784

typedef struct {
    int value;
    int pixels[NUM_PIXELS];
} Number;

Number* read_csv(const char* filename, int* num_records) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    char buffer[16032];

    if (!fgets(buffer, sizeof(buffer), file)) {
        fclose(file);
        fprintf(stderr, "Empty file\n");
        return NULL;
    }

    int count = 0;
    while (fgets(buffer, sizeof(buffer), file)) count++;
    rewind(file);
    *num_records = count;

    Number* numbers = malloc(count * sizeof(Number));
    if (!numbers) {
        fclose(file);
        perror("Memory allocation failed");
        return NULL;
    }

    fgets(buffer, sizeof(buffer), file);

    for (int i = 0; i < count; i++) {
        if (!fgets(buffer, sizeof(buffer), file)) {
            fprintf(stderr, "Error reading line %d\n", i + 2);
            free(numbers);
            fclose(file);
            return NULL;
        }

        char* token = strtok(buffer, ",");
        if (!token) {
            fprintf(stderr, "Invalid format in line %d\n", i + 2);
            free(numbers);
            fclose(file);
            return NULL;
        }

        numbers[i].value = atoi(token);

        for (int j = 0; j < NUM_PIXELS; j++) {
            token = strtok(NULL, ",");
            if (!token) {
                fprintf(stderr, "Missing pixel data in line %d\n", i + 2);
                free(numbers);
                fclose(file);
                return NULL;
            }
            numbers[i].pixels[j] = atoi(token);
        }
    }

    fclose(file);
    return numbers;
}

int main() {
    const char *c = "train.csv";
    int num_records;
    Number *data = read_csv(c, &num_records);

    if (!data) {
        fprintf(stderr, "Failed to read data\n");
        return 1;
    }

    printf("Successfully read %d records\n", num_records);
    printf("First digit: %d\n", data[123].value);
    printf("First pixel value: %d\n", data[123].pixels[0]);

    float *x_train = malloc(sizeof(float) * num_records);
    float **y_train = (float**)malloc(sizeof(float*) * num_records);
    if (x_train == NULL || y_train == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(data);
        return 1;
    }

    for (int i = 0; i < num_records; i++) {
        y_train[i] = (float*)malloc(sizeof(float) * NUM_PIXELS);
        if (y_train[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for row %d\n", i);
            // Free previously allocated memory before exiting
            for (int j = 0; j < i; j++) {
                free(y_train[j]);
            }
            free(y_train);
            free(x_train);
            free(data);
            return 1;
        }

        x_train[i] = data[i].value;
        for (int j = 0; j < NUM_PIXELS; j++) {
            y_train[i][j] = data[i].pixels[j] / 255.0;
        }
    }

    printf("Some random pixels vals from the y_train %lf %lf %lf\n",y_train[23][242],y_train[55][231],y_train[77][432]);
    printf("DONE\n");

    // Dealocation of memory zone 
    for (int i = 0; i < num_records; i++) {
        free(y_train[i]);
    }
    free(y_train);
    free(x_train);
    free(data);

    return 0;
}
