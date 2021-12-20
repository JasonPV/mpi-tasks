#include <mpi.h>
#include <cstdlib>
#include <iostream>
using namespace std;


int main(int argc, char* argv[]){

        int id, np;
        double eTime,sTime, Time;
        long long i, N=10000, mn;
        long long* array = new long long[N];
        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &id);
        MPI_Comm_size(MPI_COMM_WORLD, &np);
        MPI_Barrier(MPI_COMM_WORLD);
        srand((unsigned)(time(0)));
        if (id == 0)
        {
                for (i = 0; i < N; i++)
                        array[i] = rand()%1000 + 1;
        }
        sTime = MPI_Wtime();
        MPI_Bcast(&N, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);
        long long lmn, lN = N/np;
        long long* buf = new long long[lN];
        MPI_Scatter(array, lN, MPI_LONG_LONG, buf, lN, MPI_LONG_LONG, 0, MPI_COMM_WORLD);
        lmn = buf[0];
        for (long long j = 1; j < lN; j++)
               if (buf[j] < lmn)
                        lmn = buf[j];          
        MPI_Reduce(&lmn, &mn, 1, MPI_LONG_LONG, MPI_MIN, 0, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
        eTime = MPI_Wtime();
        Time =eTime - sTime;
        if (id == 0)
        {
                cout << "Минимальное значение вектора: " << mn << endl;
                cout << "Длительность: " << Time << endl;
        }
        MPI_Finalize();
        return 0;
}
