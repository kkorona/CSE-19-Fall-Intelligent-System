/*
 * Perceptron Learning을 위한 코드
 * Target program : learning.exe
 */


#include <bits/stdc++.h>
using namespace std;

// Constants & Definitions

const int N = 7;
const int M = 5;

// input data의 형식을 정의
const int input[10][N*M] = {
    {0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0},
    {0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0},
    {0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0},
    {1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0},
    {1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0},
    {0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0}
};

// 갱신 여부를 체크하기 위한 배열
bool validation[10];

// Perceptron 구조 정의 (threshold는 0으로)
struct Perceptron {
    int weight[N*M];
} perceptron[10];

// step function 정의
int step_function(int u) {
    return (u>=0) ? 1:-1;
}

// Actual Functions

// 개별 Perceptron weight 초기화
void init_perceptron(int index) {
        
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            perceptron[index].weight[i*M+j] = 1;
        }
    }
}

// 모든 Perceptron weight 초기화
void init_perceptrons() {
    for(int index = 0; index<=9; index++) {
        init_perceptron(index);
        validation[index] = false;
    }
}

// Actual output을 계산하기 위한 행렬 연산
int calculate(const int *A, const int *B) {
    int arr_size = N*M;
    int result = 0;
    for(int i=0; i<arr_size; i++) {
        int a = A[i], b = B[i];
        result += a*b;
    }
    return step_function(result);
}

// 개별 Perceptron의 weight 갱신 함수
void update_perceptron(int index) {
    int new_value[N*M];
    int y[10];
    for(int i=0; i<=10; i++) {
        y[i] = calculate(perceptron[index].weight,input[i]);
    }
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            new_value[i*M+j] = perceptron[index].weight[i*M+j];
        }
    }
    for(int number = 0; number <= 9; number ++) {
        for(int i=0; i<N; i++) {
            for(int j=0; j<M; j++) {
                if(number == index) {
                    new_value[i*M+j] += (1-y[number])*input[number][i*M+j];
                }
                else {
                    new_value[i*M+j] += (-1-y[number])*input[number][i*M+j];
                }
            }
        }
    }
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            perceptron[index].weight[i*M+j] = new_value[i*M+j];
        }
    }
}

// 갱신이 필요한 perceptron의 weight 갱신 함수
void update_perceptrons() {
    for(int i=0; i<=9; i++) {
        if(!validation[i]) {
            update_perceptron(i);
        }
    }
}

// 모든 perceptron중 weight 갱신이 필요한 perceptron의 flag를 켜는 함수
bool is_validate_perceptrons() {
    bool is_validate = true;
    for(int i=0; i<=9; i++) {
        validation[i] = true;
        for(int j=0; j<=9; j++) {
            int calcRes = calculate(perceptron[i].weight,input[j]);
            if(i == j && calcRes < 0) {
                validation[i] = false;
            }
            if(i != j && calcRes > 0) {
                validation[i] = false;
            }
        }
        if(!validation[i]) {
            is_validate = false;
        }
    }
    return is_validate;
}

// 모든 perceptron의 현재 weight를 출력하는 함수
void dump_perceptrons() {
    for(int i=0; i<=9; i++) {
        printf("Perceptron of %d: [",i);
        for(int j=0; j<N*M; j++) {
            printf("%d ",perceptron[i].weight[j]);
        }
        printf("] validation : %s\n",validation[i]?"Correct":"Incorrect");
    }
}

int main() {
    
    printf("------Learning Phase Start------\n");
    init_perceptrons();
    printf("------Initialized Perceptrons[0~9]------\n");
    int epoch = 0;
    
    while(!is_validate_perceptrons()) {
        printf("------ Epoch Generation : %d ------\n\n",epoch);
        // get output data
        dump_perceptrons();
        // update perceptrons
        update_perceptrons();
        epoch++;
        printf("\n");
    } 
    
    printf("------ Epoch Generation : %d ------\n\n",epoch);
    dump_perceptrons();
    
    
    // 각각의 파일에 validation이 완료된 perceptron의 최종 weight를 출력
    for(int i=0; i<=9; i++) {
        char filename[20];
        sprintf(filename,"perceptron-%d.txt",i);
        FILE *fp=fopen(filename,"w");
        for(int j=0; j<N; j++) {
            for(int k=0; k<M; k++) {
                fprintf(fp,"%d ",perceptron[i].weight[j*M+k]);
            }
            fprintf(fp,"\n");
        }
        fclose(fp);
    }
    
    return 0;
}
