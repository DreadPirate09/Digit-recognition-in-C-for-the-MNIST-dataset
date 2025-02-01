#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define INPUT_SIZE 784
#define HIDDEN_SIZE 10
#define OUTPUT_SIZE 10
#define ALPHA 0.01
#define ITERATIONS 500
#define DATA_SIZE 42000
#define TEST_SIZE 20000
#define NUM_PIXELS 784

typedef struct {
    int value;
    int pixels[NUM_PIXELS];
} Number;

typedef struct {
    int pixels[NUM_PIXELS];
} Test;

double random_weight() {
    double random_val = (rand() / (double)RAND_MAX) - 0.5;
    return random_val;
}

void ReLU(double *Z, int size) {
    for (int i = 0; i < size; i++) {
        if (Z[i] < 0)
            Z[i] = 0;
    }
}

void softmax(double *Z, double *A, int size) {
    double sum_exp = 0.0;
    for (int i = 0; i < size; i++) {
        sum_exp += exp(Z[i]);
    }
    for (int i = 0; i < size; i++) {
        A[i] = exp(Z[i]) / sum_exp;        
    }
}

void init_params(double *W1, double *b1, double *W2, double *b2) {
    for (int i = 0; i < HIDDEN_SIZE * INPUT_SIZE; i++) {
        W1[i] = random_weight();
    }
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        b1[i] = random_weight();
    }
    for (int i = 0; i < OUTPUT_SIZE * HIDDEN_SIZE; i++) {
        W2[i] = random_weight();
    }
    for (int i = 0; i < OUTPUT_SIZE; i++) {
        b2[i] = random_weight();
    }
}

void forward_prop(double *W1, double *b1, double *W2, double *b2, double *X,double *Z1, double *A1, double *Z2, double *A2) {
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        Z1[i] = 0;
        for (int j = 0; j < INPUT_SIZE; j++) {
            Z1[i] += W1[i * INPUT_SIZE + j] * X[j];
        }
        Z1[i] += b1[i];
    }
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        A1[i] = (Z1[i] > 0) ? Z1[i] : 0;
    }
    for (int i = 0; i < OUTPUT_SIZE; i++) {
        Z2[i] = 0;
        for (int j = 0; j < HIDDEN_SIZE; j++) {
            Z2[i] += W2[i * HIDDEN_SIZE + j] * A1[j];
        }
        Z2[i] += b2[i];
    }
    softmax(Z2, A2, OUTPUT_SIZE);
}

void backward_prop(double *Z1, double *A1, double *Z2, double *A2,
                   double *W2, double *X, double *target,
                   double *dW1, double *db1, double *dW2, double *db2) {
    double dZ2[OUTPUT_SIZE];
    for (int i = 0; i < OUTPUT_SIZE; i++) {
        dZ2[i] = A2[i] - target[i];
    }
    for (int i = 0; i < OUTPUT_SIZE; i++) {
        db2[i] = dZ2[i];
        for (int j = 0; j < HIDDEN_SIZE; j++) {
            dW2[i * HIDDEN_SIZE + j] = dZ2[i] * A1[j];
        }
    }
    double dZ1[HIDDEN_SIZE];
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        dZ1[i] = 0;
        for (int j = 0; j < OUTPUT_SIZE; j++) {
            dZ1[i] += W2[j * HIDDEN_SIZE + i] * dZ2[j];
        }
        if (Z1[i] < 0)
            dZ1[i] = 0;
    }
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        db1[i] = dZ1[i];
        for (int j = 0; j < INPUT_SIZE; j++) {
            dW1[i * INPUT_SIZE + j] = dZ1[i] * X[j];
        }
    }
}

void update_params(double *W1, double *b1, double *W2, double *b2,double *dW1, double *db1, double *dW2, double *db2) {
    for (int i = 0; i < HIDDEN_SIZE * INPUT_SIZE; i++) {
        W1[i] -= ALPHA * dW1[i];
    }
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        b1[i] -= ALPHA * db1[i];
    }
    for (int i = 0; i < OUTPUT_SIZE * HIDDEN_SIZE; i++) {
        W2[i] -= ALPHA * dW2[i];
    }
    for (int i = 0; i < OUTPUT_SIZE; i++) {
        b2[i] -= ALPHA * db2[i];
    }
}

int get_prediction(double *A2) {
    int pred = 0;
    for (int i = 1; i < OUTPUT_SIZE; i++) {
        if (A2[i] > A2[pred])
            pred = i;
    }
    return pred;
}

void shuffle(int *array, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

double get_accuracy(int *preds,int len){
    int zeros = 0;
    for(int i=0;i<len;i++){
        if(preds[i] == 0){
            zeros++;
        }
    }
    return (double)zeros/(double)len * 100.0;
}

void train(double *X, double *Y, double *W1, double *b1, double *W2, double *b2, int m_train,double *X_test, double *Y_test) {
    double Z1[HIDDEN_SIZE], A1[HIDDEN_SIZE], Z2[OUTPUT_SIZE], A2[OUTPUT_SIZE];
    double dW1[HIDDEN_SIZE * INPUT_SIZE], db1[HIDDEN_SIZE];
    double dW2[OUTPUT_SIZE * HIDDEN_SIZE], db2[OUTPUT_SIZE];

    // Create an array of indices for shuffling
    int *indices = malloc(m_train * sizeof(int));
    if (indices == NULL) {
        perror("Failed to allocate indices");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < m_train; i++)
        indices[i] = i;

    for (int epoch = 0; epoch < ITERATIONS; epoch++) {
        shuffle(indices, m_train);
        double l = 0;
        int preds[m_train];
        for (int i = 0; i < m_train; i++) {
            int idx = indices[i];
            double *xi = &X[idx * INPUT_SIZE];
            int label = (int)Y[idx];
            l = label;
            double target[OUTPUT_SIZE] = {0};
            if (label >= 0 && label < OUTPUT_SIZE)
                target[label] = 1.0;
            else {
                fprintf(stderr, "Invalid label %d at index %d\n", label, idx);
                continue;
            }
            forward_prop(W1, b1, W2, b2, xi, Z1, A1, Z2, A2);
            preds[i] = label - get_prediction(A2);
            backward_prop(Z1, A1, Z2, A2, W2, xi, target, dW1, db1, dW2, db2);
            update_params(W1, b1, W2, b2, dW1, db1, dW2, db2);
        }
        if (epoch % 10 == 0) {
            int pred = get_prediction(A2);
            int pred_test[TEST_SIZE];
            // lets do prediction for the last 20k labels that we're not used
            for(int t=0;t<TEST_SIZE;t++){
                forward_prop(W1, b1, W2, b2, &X_test[t * INPUT_SIZE], Z1, A1, Z2, A2);
                pred_test[t] = Y_test[t] - get_prediction(A2);
            }
            printf("The accuracy train is : %lf\n",get_accuracy(preds,m_train));
            printf("The accuracy test is : %lf\n",get_accuracy(pred_test,TEST_SIZE));

            printf("The biases right now\n");
            for(int i=0;i<10;i++)
                printf("%lf %lf\n",b1[i],b2[i]);
            printf("The label %lf\n",l);
            printf("Epoch %d: Prediction = %d\n", epoch, pred);
        }
    }
    free(indices);
}

// Read the CSV file into an array of Number structures
Number* read_csv(const char* filename) {
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

    // Count the number of records (lines)
    int count = 0;
    while (fgets(buffer, sizeof(buffer), file))
        count++;
    rewind(file);
    fgets(buffer, sizeof(buffer), file);  // skip header again

    Number* numbers = malloc(count * sizeof(Number));
    if (!numbers) {
        fclose(file);
        perror("Memory allocation failed");
        return NULL;
    }

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

// Read the CSV file into an array of Number structures
Test* read_csv_test(const char* filename) {
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

    // Count the number of records (lines)
    int count = 0;
    while (fgets(buffer, sizeof(buffer), file))
        count++;
    rewind(file);
    fgets(buffer, sizeof(buffer), file);  // skip header again

    Test* numbers = malloc(count * sizeof(Test));
    if (!numbers) {
        fclose(file);
        perror("Memory allocation failed");
        return NULL;
    }

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
        numbers[i].pixels[0] = atoi(token);
        for (int j = 1; j < NUM_PIXELS; j++) {
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
    srand(time(0));

    // Read CSV data
    Number *data = read_csv("train.csv");
    // Test *data_test = read_csv_test("test.csv");
    if (!data) {
        fprintf(stderr, "Failed to load data\n");
        return EXIT_FAILURE;
    }

    // Allocate memory for input (X) and label (Y) arrays.
    // X: each sample is an array of INPUT_SIZE doubles.
    double *X = malloc(sizeof(double) * (DATA_SIZE - TEST_SIZE) * INPUT_SIZE);
    double *Y = malloc(sizeof(double) * (DATA_SIZE - TEST_SIZE));
    double *X_test = malloc(sizeof(double) * TEST_SIZE * INPUT_SIZE);
    double *Y_test = malloc(sizeof(double) * TEST_SIZE * INPUT_SIZE);
    if (!X || !Y || !X_test || !Y_test) {
        fprintf(stderr, "Failed to allocate for X or Y test/training data\n");
        free(data);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < (DATA_SIZE - TEST_SIZE); i++) {
        Y[i] = data[i].value;
        for (int j = 0; j < INPUT_SIZE; j++) {
            X[i * INPUT_SIZE + j] = data[i].pixels[j] / 255.0;
        }
    }

    for (int i = (DATA_SIZE - TEST_SIZE); i < DATA_SIZE; i++) {
        Y_test[i] = data[i].value;
        for (int j = 0; j < INPUT_SIZE; j++) {
            X_test[i * INPUT_SIZE + j] = data[i].pixels[j] / 255.0;
        }
    }
    free(data);  // Data is now in X and Y

    // Allocate parameters dynamically
    double *W1 = malloc(sizeof(double) * HIDDEN_SIZE * INPUT_SIZE);
    double *b1 = malloc(sizeof(double) * HIDDEN_SIZE);
    double *W2 = malloc(sizeof(double) * OUTPUT_SIZE * HIDDEN_SIZE);
    double *b2 = malloc(sizeof(double) * OUTPUT_SIZE);
    if (!W1 || !b1 || !W2 || !b2) {
        fprintf(stderr, "Failed to allocate parameters\n");
        free(X);
        free(Y);
        return EXIT_FAILURE;
    }

    init_params(W1, b1, W2, b2);

    train(X, Y, W1, b1, W2, b2, DATA_SIZE - TEST_SIZE, X_test, Y_test);

    // Test forward propagation on a single sample (for example, the first sample)
    double Z1[HIDDEN_SIZE], A1[HIDDEN_SIZE], Z2[OUTPUT_SIZE], A2[OUTPUT_SIZE];
    printf("The sample taken is : %lf",Y[123]);
    forward_prop(W1, b1, W2, b2, &X[123*784], Z1, A1, Z2, A2);
    int pred_class = get_prediction(A2);
    printf("Predicted class for first sample: %d\n", pred_class);

    // Clean up allocated memory
    free(W1);
    free(b1);
    free(W2);
    free(b2);
    free(X);
    free(Y);
    free(X_test);
    free(Y_test);

    return 0;
}
