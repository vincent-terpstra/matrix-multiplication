/**
 * @author Vincent Terpstra
 * @file matrix.cpp
 * @date Jan 24 / 2018
 * @purpose
 *      Matrix function practice
 */

#include <iostream>

using namespace std;

/*
 * Display function
 */
void display(const float* matrix, int row, int col){
    const float * endM = matrix + row * col;
    int c = 0;
    while(matrix < endM){
        cout << *matrix++ << " ";
        if(!(++c % col)) cout << endl; 
    }
    cout << endl;
}
/**
 * Calculate the dot product between two vectors
 *      input stride : allows dot product over a column in matrix multiplication
 */
float sdot(const float * vec1, const float * vec2, int row, int stride = 1){
    float sum = 0;
    const float * end = vec1 + row;
    while(vec1 < end){
        sum += *vec1 * *vec2;
        vec1 ++;        //move to next value
        vec2 += stride; //move to next value (column in matrix multiplication)
    }
    return sum;
}

/**
 * Single precision matrix A * x placed into y
 */
float* sax(const float * A, const float * x, int size, float * y){
    const float * endA = A + size * size;
    float * locY = y;
    while(A < endA){
        *locY++ = sdot(x, A, size);
        A += size;
    }
    return y;
}

/**
 * Single precision Matrix multiplication
 */
float* sgemm(const float * A, const float* B, float* C, int size){
    const float * endA = A + size * size; 
    const float * endB = B + size;
    float * locC = C;
    while(A < endA){
        const float * tmpB = B;
        while(tmpB < endB){
            *locC++ = sdot(A, tmpB++, size, size);
        } 
        A += size;
    }
    return C;
}

int main(){
    float x[] = {1, 2, 1, 3, 2};
    float y[] = {1, 2, 2, 1, 3};

    float z[] = {0,0,0,0,0};

    float M[] = {
        1,0,1,0,1,
        0,1,0,1,0,
        0,0,1,1,1,
        0,0,0,1,0,
        1,0,0,0,1
    };
    float A[] = {
        1,0,1,0,1,
        0,1,0,1,0,
        0,0,1,1,1,
        0,0,0,1,0,
        1,0,0,0,1
    };
    float B[] = {
        1,1,1,0,1,
        0,1,1,1,0,
        1,0,1,1,1,
        0,1,0,1,0,
        1,0,1,0,1
    };
    display(sax(M,x, 5, z), 1, 5);
    display(sax(M,y, 5, z), 1, 5);
    display(sgemm(A, B, M, 5), 5, 5);
    return 0;
}