#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <string.h>

#define NUM_PIXELS 784

typedef struct {
    int value;
    int pixels[NUM_PIXELS];
} Number;

struct initParams{
    float** W1;
    float** W2;
    float** b1;
    float** b2;
};

float **giveMeARandomMatrixNM(int n, int m){
    float ** matrix = (float**)malloc(n*sizeof(float*));
    srand(time(NULL));
    // Generate a random number between 0 and 1
    double randomValue = (double)rand() / RAND_MAX;
    for(int i=0;i<n;i++){
        matrix[i] = (float*)malloc(m*sizeof(float));
        for(int j=0;j<m;j++){
            matrix[i][j] = randomValue;
            randomValue =  (double)rand() / RAND_MAX;
        }
    }
    return matrix;
}

float *giveMeRandomList(int n){
    float * list = (float*)malloc(n*sizeof(float));
    srand(time(NULL));
    // Generate a random number between 0 and 1
    for(int i=0;i<n;i++){
        float randomValue =  (float)rand() / RAND_MAX;
        list[i] = randomValue;
    }
    return list;
}

float** substractMatrixVal(float** matrix1, float val, int m, int n){
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            matrix1[i][j] = matrix1[i][j] - val;
        }
    }
    return matrix1;
}

struct initParams getInitParams(){
    struct initParams x;
    x.W1 = substractMatrixVal(giveMeARandomMatrixNM(10,784),0.5,10,784);
    x.b1 = substractMatrixVal(giveMeARandomMatrixNM(10,1),0.5,10,1);
    x.W2 = substractMatrixVal(giveMeARandomMatrixNM(10,784),0.5,10,784);
    x.b2 = substractMatrixVal(giveMeARandomMatrixNM(10,1),0.5,10,1);
    return x;
}

void freeInitParams(struct initParams ip){
    for(int i=0;i<10;i++){
        free(ip.W1[i]);
        free(ip.W2[i]);
        free(ip.b1[i]);
        free(ip.b2[i]);
    }
    printf("Done freeing the memory for the params\n");
}

void freeMatrix(float **matrix, int lines){
    for(int i=0;i<lines;i++){
        free(matrix[i]);
    }
    printf("Done freeing the matrix");
}

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

    // Allocate memory for x_train and y_train
    float *y_train = malloc(sizeof(float) * num_records);
    float **x_train = (float**)malloc(sizeof(float*) * num_records);
    if (x_train == NULL || y_train == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(data);
        return 1;
    }

    for (int i = 0; i < num_records; i++) {
        x_train[i] = (float*)malloc(sizeof(float) * NUM_PIXELS);
        if (x_train[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for row %d\n", i);
            // Free previously allocated memory before exiting
            for (int j = 0; j < i; j++) {
                free(x_train[j]);
            }
            free(x_train);
            free(y_train);
            free(data);
            return 1;
        }

        y_train[i] = data[i].value;
        for (int j = 0; j < NUM_PIXELS; j++) {
            x_train[i][j] = data[i].pixels[j] / 255.0;
        }
    }

    struct initParams iP = getInitParams();
    printf("Init params done\n");
    printf("some sample of the W1 : %lf\n",iP.W1[2][2]);
    freeInitParams(iP);

    printf("Some random pixels vals from the x_train %lf %lf %lf\n",x_train[23][242],x_train[55][231],x_train[77][432]);

    printf("DONE\n");


    // Dealocation of memory zone 
    for (int i = 0; i < num_records; i++) {
        free(x_train[i]);
    }
    free(y_train);
    free(x_train);
    free(data);

    return 0;
}
