#include<stdio.h>

typedef struct {
	int *arr;
	int size;
} MNOZINA;

// TODO: check if allocation "prebehla dobre"
MNOZINA* init(int size)
{
    MNOZINA *M = (MNOZINA*)malloc(sizeof(MNOZINA));
    M->size = size;
    M->arr = (int*)malloc(sizeof(int)*size);
    return M;
}

void insert(MNOZINA *M){
	for(int i = 0; i < M->size; i++)
	{
		scanf("%d", &M->arr[i]);
	}
}

void show(MNOZINA *M){
	printf("{ ");
	for(int i = 0; i < M->size; i++)
	{
		if (i == M->size-1) 
			printf("%d ", M->arr[i]);
		else 
			printf("%d, ", M->arr[i]);
	}
	printf("}");
}

void destroy(MNOZINA *M)
{
	 free(M->arr);
	 free(M); 
	 M = NULL;
	 printf("\n!! DESTROYED !!");
}

//void selectionSort(int arr[], int n) 
//{ 
//    int min_idx; 
//    
//    for (int i = 0; i < n - 1; i++) { 
//        min_idx = i; 
//        
//        for (int j = i + 1; j < n; j++) { 
//            if (arr[j] < arr[min_idx]) 
//                min_idx = j; 
//        } 
//        
//        if (min_idx != i) {
//        	int temp = arr[min_idx];
//        	arr[min_idx] = arr[i];
//        	arr[i] = temp;
//		}
//    } 
//} 

MNOZINA* mIntersection(MNOZINA *A, MNOZINA *B) {
    MNOZINA *result = init((A->size < B->size ? A->size : B->size)); // CHeck smaller size
    int ind = 0;

    for (int i = 0; i < A->size; i++) {
        for (int j = 0; j < B->size; j++) {
            if (A->arr[i] == B->arr[j]) {
                result->arr[ind] = A->arr[i];
                ind++;
                
                break; 
            }
        }
    }
    
    result->size = ind;
    return result;
}

MNOZINA* mUnion(MNOZINA *A, MNOZINA *B) {
    MNOZINA *result = init(A->size + B->size); // Max possible size
    int ind = 0; 
	
	// `A` elements
    for (int i = 0; i < A->size; i++) {
        result->arr[ind] = A->arr[i];
        ind++;
    }
    
	// +`B` different elements
    for (int i = 0; i < B->size; i++) {
        int found = 0;
        for (int j = 0; j < A->size; j++) {
            if (B->arr[i] == A->arr[j]) {
                found = 1;
                break;
            }
        }
        
        if (!found) {
            result->arr[ind] = B->arr[i];
            ind++;
            
        }
    }

    result->size = ind;
    result->arr = realloc(result->arr, sizeof(int) * result->size);
    return result;
}

void addNumber(MNOZINA *M, int num) {
    M->size++;
    M->arr = realloc(M->arr, sizeof(int) * M->size);
    
    M->arr[M->size - 1] = num;
}

void removeNumber() {
	
}

int main(){
    MNOZINA *M1, *M2, *M3, *M4;
    int length_m1, length_m2;
    
    printf("Kolko cisel v 1 a 2 mnozinach: \n");
    scanf("%d%d", &length_m1, &length_m2);
    
    M1 = init(length_m1);
    M2 = init(length_m2);
    
    printf("\nNapiste %d cisel do 1 mnozine: \n", length_m1);
    insert(M1);    
    
    printf("\nNapiste %d cisel do 2 mnozine: \n", length_m2);
    insert(M2);
	
	printf("\nMnozina 1: ");  
    show(M1);
    printf("\nMnozina 2: "); 
    show(M2);
    printf("\n");
    
    printf("\nPrienik mnozin 1 a 2: "); 
    M3 = mIntersection(M1,M2);
    show(M3);
    
    printf("\nSpojenie mnozin 1 a 2: "); 
    M4 = mUnion(M1,M2);
    show(M4);
    
    printf("\nAdd number to 1 array: "); 
    addNumber(M1,111);
    show(M1);
    
    printf("\n");
    destroy(M1);
    destroy(M2);
    destroy(M3);
    destroy(M4);
    
    return 0;
}
