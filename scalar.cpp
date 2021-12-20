#include <mpi.h>
#include <cstdlib>
#include <iostream>
using namespace std;


int main(int argc, char* argv[]){

        int id, np;
        double eTime,sTime, Time;
        long long i, N=10000, sm;
        long long* array1 = new long long[N];
        long long* array2 = new long long[N];

        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &id);
        MPI_Comm_size(MPI_COMM_WORLD, &np);
        MPI_Barrier(MPI_COMM_WORLD);
        srand((unsigned)(time(0)));
        if (id == 0)
        {
                for (i = 0; i < N; i++)
                        array1[i] = rand()%1000 + 1;
                for (i = 0; i < N; i++)
                        array2[i] = rand()%1000 + 1;
        }
        MPI_Bcast(&N, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);
        long long* buf1 = new long long[N/np];
        long long* buf2 = new long long[N/np];
        long long lsm = 0;
        sTime = MPI_Wtime();
        MPI_Scatter(array1, N/np, MPI_LONG_LONG, buf1, N/np, MPI_LONG_LONG, 0, MPI_COMM_WORLD);
        MPI_Scatter(array2, N/np, MPI_LONG_LONG, buf2, N/np, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

        for (long long j = 0; j < N/np; j++)
                lsm += buf1[j]*buf2[j];

        MPI_Reduce(&lsm, &sm, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
        eTime = MPI_Wtime();
        Time =eTime - sTime;
        if (id == 0)
        {
                cout << "Скалярное произведения: " << sm << endl;
                cout << "Длительность: " << Time << endl;
        }
        MPI_Finalize();
        return 0;
}
