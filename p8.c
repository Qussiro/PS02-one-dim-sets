#include<stdio.h>
int pocet_porovnania = 0;

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
}

MNOZINA* mIntersection(MNOZINA *A, MNOZINA *B) {
    MNOZINA *result = init((A->size < B->size ? A->size : B->size)); // CHeck smaller size
    pocet_porovnania++;
    int ind = 0;

    for (int i = 0; i < A->size; i++) {
        for (int j = 0; j < B->size; j++) {
            if (A->arr[i] == B->arr[j]) {
                result->arr[ind] = A->arr[i];
                ind++;
                pocet_porovnania++;
                
                break; 
            }
            pocet_porovnania++;
        }
        pocet_porovnania++;
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
        pocet_porovnania++;
    }
    
	// +`B` different elements
    for (int i = 0; i < B->size; i++) {
        int found = 0;
        for (int j = 0; j < A->size; j++) {
            if (B->arr[i] == A->arr[j]) {
                found = 1;
                pocet_porovnania++;
                break;
            }
            pocet_porovnania++;
        }
        
        if (!found) {
            result->arr[ind] = B->arr[i];
            ind++;
            
        }
        pocet_porovnania++;
    }

    result->size = ind;
    result->arr = realloc(result->arr, sizeof(int) * result->size);
    return result;
}

MNOZINA* mRand(int size){
	MNOZINA *result = init(size);
	
	for (int i = 0; i < result->size; i++) {
        int same;
        
        do
        {
            same = 0;
            
			// idk about the boundaries of rand numbers
            result->arr[i] = rand() % (size+10) + 1;
            
            for (int j = 0; j < i; j++) {
                if (result->arr[j] == result->arr[i])
                {
                    same = 1;
                    break;
                }
            }
        } while (same);
    }
	
	return result;
}

void addNumber(MNOZINA *M, int num) {
    M->size++;
    M->arr = realloc(M->arr, sizeof(int) * M->size);
    
    M->arr[M->size - 1] = num;
}

void removeNumber() {
	
}

void pocetToFile(int times){
	MNOZINA *M1, *M2, *M3;
	FILE *fptr;
	
	fptr = fopen("pocty.txt", "w");
	
	for(int i = 0; i < times; i++){
		M1 = mRand(i);
    	M2 = mRand(i);
    	M3 = mIntersection(M1,M2);
    	M3 = mUnion(M1,M2);
    	
    	printf("\nPocet porovnania %d: %d", i, pocet_porovnania); 
    	fprintf(fptr, "%d\n", pocet_porovnania);
    	pocet_porovnania = 0;
	}
    destroy(M1);
    destroy(M2);
    
	fclose(fptr);
}
int main(){
    pocetToFile(50);
    printf("\n");
    
    return 0;
}
