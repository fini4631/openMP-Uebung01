// icpc -openmp -o main main.cpp
// export DYLD_LIBRARY_PATH="/opt/intel/composer_xe_2015.0.077/compiler/lib:$DYLD_LIBRARY_PATH"
// ./main

#include <stdio.h>						// macht die c++ Standard Bibliothek verfügbar
#include <omp.h> 						// includiert openMP Funktionen.

int main (int argc, char* argv[])
{
	int numThreads;						// Deklariert Variable numThreads als int.
	int threadID;						// Deklariert Variable threadID als int.
	double start, end;					// Deklariert Variable star und end als (float fälschlicherweise) double.
	
	start = omp_get_wtime(); 			// Start wird instanziiert und initialisiert, belegt mit Prozesszeit.
										// Gleitkommawert mit doppelter Genauigkeit
								// "Returns elapsed wall clock time in seconds."

								/*  Ein Pragma weist den Compiler an bestimmte Operationen auszuführen. 
								Kennt ein Compiler die #pragma Anweisung nicht, so wird sie einfach ohne 
								Felermeldung oder Warnung ignoriert. Somit können Compileroptionen 
								definiert werden ohne mit anderen Compilern in Konflikt zu treten. 
								Hier handelt es sich um das omp Pragma, welches einen parallelen Block
								einleitet (omp parallel) und in diesem die zu startenden 
								Threads zur Parallisierung auf einen bestimmten 
								Wert festlegt "num_threads( INT )" */
	#pragma omp parallel num_threads(2) // omp_get_max_threads()
	{	// "Forms a team of threads and starts parallel execution"
		threadID = omp_get_thread_num(); // Die ID vom jeweiligen aktuellen Thread wird gespeichert 
										// und später per printf ausgegeben	
		// "Returns the thread number of the calling thread within the current team."
		printf("Hello from thread %d\n", threadID);

		/*  Wird nur von Thread mit der Nummer 0 ausgeführt (Master Thread?) #pragma omp master */
		if (threadID == 0)
		{
			numThreads = omp_get_num_threads();				// Anzahl der gestarteten Threads
			printf("Number of threads: %d\n", numThreads);
		}
	}

	end = omp_get_wtime();
	printf("This task took %f seconds \n", end-start);
}