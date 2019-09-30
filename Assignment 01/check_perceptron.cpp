/*
 * Perceptron 검증을 위한 코드
 * Target Program : validating.exe
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

// test data의 형식을 정의
const int test_input[10][N*M] = {
    {0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0},
    {0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0},
    {1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0},
    {0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0},
    {1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0},
    {0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0}
};

// Perceptron 구조 정의 (threshold는 0으로)
struct Perceptron {
    int weight[N*M];
} perceptron[10];

// step function 정의
int step_function(int u) {
    return (u>=0) ? 1:-1;
}

// Actual Functions

// Actual output을 계산하기 위한 행렬 연산
int calculate(const int *A, const int *B) {
    int arr_size = N*M;
    int result = 0;
    for(int i=0; i<arr_size; i++) {
        int a = A[i], b = B[i];
        result += a*b;
    }
    return result;
}

// learning 과정에서 최종적으로 기록된 각 perceptron의 weight를 불러오는 함수
void load_perceptron(int index) {
    char filename[20];
    sprintf(filename,"perceptron-%d.txt",index);
    
    int input;
    FILE *fp = fopen(filename,"r");
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            fscanf(fp,"%d",&input);
            perceptron[index].weight[i*M+j] = input;
        }
    }
    fclose(fp);
}

int main() {
    
    // Perceptron의 weight를 가져온다.
    for(int i=0; i<=9; i++) {
        load_perceptron(i);
    }
    
    // 대표 이미지에 대한 테스트 진행
    printf("------Results of representative patterns------\n\n");
    for(int i=0; i<=9; i++) {
        
        // i번째 패턴에 대한 인식 결과 출력
        printf("------Results of Pattern %d------\n",i);
        
        // step function을 거치지 않은 raw value 출력
        for(int j=0; j<=9; j++) {
            int ret = calculate(perceptron[j].weight, input[i]);
            printf("%4d ",ret);
        }
        printf("\n");
        
        // step function을 거친 one-hot code 출력
        for(int j=0; j<=9; j++) {
            int ret = calculate(perceptron[j].weight, input[i]);
            printf("%4d ",step_function(ret));
        }
        printf("\n\n");
    }
    
    // 노이즈를 추가한 테스트 이미지에 대한 테스트 진행
    printf("------Results of test patterns------\n\n");
    for(int i=0; i<=9; i++) {
        
        // i번째 패턴에 대한 인식 결과 출력
        printf("------Results of Pattern %d------\n",i);
        
        // step function을 거치지 않은 raw value 출력
        for(int j=0; j<=9; j++) {
            int ret = calculate(perceptron[j].weight, test_input[i]);
            printf("%4d ",ret);
        }
        printf("\n");
        
        // step function을 거친 one-hot code 출력
        for(int j=0; j<=9; j++) {
            int ret = calculate(perceptron[j].weight, test_input[i]);
            printf("%4d ",step_function(ret));
        }
        printf("\n\n");
    }
    return 0;
}