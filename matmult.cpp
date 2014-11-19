#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// ---------------------------------------------------------------------------
// allocate space for empty matrix A[row][col]
// access to matrix elements possible with:
// - A[row][col]
// - A[0][row*col]

float **alloc_mat(int row, int col)
{
    float **A1, *A2;

	A1 = (float **)calloc(row, sizeof(float *));		// pointer on rows
	A2 = (float *)calloc(row*col, sizeof(float));    // all matrix elements
    
                                                    // es bestehen keine Abhänigkeiten der einzelnen indizes
                                                    // Reihenfolge ist zu beachten ordered
    #pragma omp parallel for ordered
    for (int i = 0; i < row; i++)
        #pragma omp ordered
        A1[i] = A2 + i*col;

    return A1;
}

// ---------------------------------------------------------------------------
// random initialisation of matrix with values [0..9]

void init_mat(float **A, int row, int col)
{
                                                    // es bestehen keine Abhänigkeiten der einzelnen indizes
                                                    // Reihenfolge ist zu beachten ordered
    #pragma omp parallel for ordered
    for (int i = 0; i < row*col; i++)
        #pragma omp ordered
		A[0][i] = (float)(rand() % 10);
}

// ---------------------------------------------------------------------------
// DEBUG FUNCTION: printout of all matrix elements

void print_mat(float **A, int row, int col, char *tag)
{
    int i, j;
                                                    // Ausgabe ist unsinnig zu parallelisieren, 
                                                    // weil nur Speicherzugiff und keine Berechnung.
                                                    // wenn nur eine Schleife parallelisierbar. nicht beide
                                                    // gleichzeitig. #pragma omp for collapse(2) funktioniert nicht,
                                                    // da in der ersten for loop Code (Zeilenumbruch) ausgeführt wird.
    printf("Matrix %s:\n", tag);
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++) 
            printf("%6.1f   ", A[i][j]);
        printf("\n"); 
    }
}

// ---------------------------------------------------------------------------

int main(int argc, char *argv[])
{ // export OMP_NUM_THREADS=1
    float **A, **B, **C;	// matrices
    int d1, d2, d3;         // dimensions of matrices
    int i, j, k;			// loop variables
    double start, end;
    start = omp_get_wtime();

    /* print user instruction */
    if (argc != 4)
    {
        printf ("Matrix multiplication: C = A x B\n");
        printf ("Usage: %s <NumRowA> <NumColA> <NumColB>\n", argv[0]); 
        return 0;
    }

    /* read user input */
    d1 = atoi(argv[1]);		// rows of A and C
    d2 = atoi(argv[2]);     // cols of A and rows of B
    d3 = atoi(argv[3]);     // cols of B and C

    printf("Matrix sizes C[%d][%d] = A[%d][%d] x B[%d][%d]\n", d1, d3, d1, d2, d2, d3);

    /* prepare matrices */
    A = alloc_mat(d1, d2);
    init_mat(A, d1, d2); 
    B = alloc_mat(d2, d3);
    init_mat(B, d2, d3);
    C = alloc_mat(d1, d3);	// no initialisation of C, because it gets filled by matmult

    /* serial version of matmult */
    printf("Perform matrix multiplication...\n");
                      /* spezielle collapse-Schleife, um über ein mehrdimensionales Array zu iterieren
                         Schleifen müssen sehr einfach gehalten sein, damit Parallelisierung erfolgen kann
                         Alle Schleifenvariablen müssen völlig unabhängig voneinander sein. 
                         Sind es aber nicht, die Ausgabe war Fehlerhaft. */

    double sum;
    // #pragma omp parallel for collapse(3) schedule(dynamik)
    for (i = 0; i < d1; i++)
       for (j = 0; j < d3; j++)
          #pragma omp parallel for private(sum)// Rechenintensive Operation wird parallelisiert.
          for (k = 0; k < d2; k++)
            { // Nur hier darf beliebiger Code stehen! wenn collaps verwendet würde
             sum = A[i][k] * B[k][j];
             #pragma omp atomic
             C[i][j] += sum;
         }

    /* test output */
    print_mat(A, d1, d2, "A"); 
    print_mat(B, d2, d3, "B"); 
    print_mat(C, d1, d3, "C"); 

    printf ("\nDone.\n");

    end = omp_get_wtime();
    printf("This task took %f seconds\n", end-start);
    return 0;
}