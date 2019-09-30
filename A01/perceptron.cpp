#include <bits/stdc++.h>
using namespace std;

// Constants & Definitions

const int N = 7;
const int M = 5;

const int input[10][N*M] = {
    {0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0},
    {0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0},
    {0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0},
    {1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0},
    {1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0},
    {0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0}
}

struct Perceptron {
    int weight[N*M];
    double threshold = 0;
} perceptron[10];

int step_function(int u) {
    return (u>=0) ? 1:-1;
}

// Actual Functions

void init_perceptron(int index) {
    
    char index_name[30];
    sprintf(index_name, "perceptron_%d_weight.txt",index);
    
    FILE *fp = fopen(index_name,"w");
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            fprintf(fp, "1 ");
            perceptron[index].weight[i*N+j] = 1;
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
}

void init_perceptrons() {
    for(int index = 0; index<=9; index++) {
        init_perceptron(index);
    }
}

void update_perceptron(int index) {
    
    char index_name[30];
    sprintf(index_name, "perceptron_%d_weight.txt",index);
    
    FILE *fp = fopen(index_name,"w");
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            fprintf("%d ",perceptron[index].weight[i*N+j]);
        }
        fprintf(fp,"\n");
    }
    
    fclose(fp);   
}

void calculate(const int *A, const int *B) {
    int arr_size = N*M;
    int result = 0;
    for(int i=0; i<arr_size; i++) {
        int a = A[i], b = B[i];
        result += a*b;
    }
    return step_function(result);
}

int main() {
    
    printf("Learning Phase Start");
    init_perceptrons();
    printf("Initialized Perceptrons[0~9]");
    int epoch = 0;
    
    while(!is_validate_perceptrons()) {
        // get output data
        // update perceptrons
    } 
    
    return 0;
}
