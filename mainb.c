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

    // Skip header line
    if (!fgets(buffer, sizeof(buffer), file)) {
        fclose(file);
        fprintf(stderr, "Empty file\n");
        return NULL;
    }

    // First pass to count records
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

    // Skip header again
    fgets(buffer, sizeof(buffer), file);

    for (int i = 0; i < count; i++) {
        if (!fgets(buffer, sizeof(buffer), file)) {
            fprintf(stderr, "Error reading line %d\n", i+2);
            free(numbers);
            fclose(file);
            return NULL;
        }

        char* token = strtok(buffer, ",");
        if (!token) {
            fprintf(stderr, "Invalid format in line %d\n", i+2);
            free(numbers);
            fclose(file);
            return NULL;
        }

        numbers[i].value = atoi(token);

        for (int j = 0; j < NUM_PIXELS; j++) {
            token = strtok(NULL, ",");
            if (!token) {
                fprintf(stderr, "Missing pixel data in line %d\n", i+2);
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


int main(){
    const char *c = "train.csv";
    int num_records;
    Number *data = read_csv(c,&num_records);

    if (data) {
        printf("Successfully read %d records\n", num_records);   
        printf("First digit: %d\n", data[123].value);
        printf("First pixel value: %d\n", data[123].pixels[0]);  
        free(data);
    }
    return 0;
}
