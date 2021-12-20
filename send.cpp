#include <mpi.h>
#include <cstdlib>
#include <iostream>
using namespace std;


int main(int argc, char* argv[]){

        int id, np;
        int s, r;
        double eTime, sTime, Time;
        long long i, N=10000000;
        long long* arr = new long long[N];
        MPI_Status Status;
        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &id);
        MPI_Comm_size(MPI_COMM_WORLD, &np);
        MPI_Barrier(MPI_COMM_WORLD);
        srand((unsigned)(time(0)));
        if (id == 0)
        {
                for (i = 0; i < N; i++)
                        arr[i] = rand()%10000 + 1;
        }
        MPI_Bcast(&N, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        if (id == 1)
                long long* larr = new long long[N];
        sTime = MPI_Wtime();
        for (int j = 0; j < 100; j++)
        {
                if (j % 2 == 0)
                {
                        s = 0;
                        r = 1;
                        if (id == 0)
                                MPI_Send(arr, N, MPI_LONG_LONG, r, 0, MPI_COMM_WORLD);

                        else if (id == 1)
                                MPI_Recv(larr, N, MPI_LONG_LONG, s, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
                }
                else
                {
                        s = 1;
                        r = 0;
                        if (id == 1)
                                MPI_Send(larr, N, MPI_LONG_LONG, r, 0, MPI_COMM_WORLD);

                        else if (id == 0)
                                MPI_Recv(arr, N, MPI_LONG_LONG, s, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);

                }

        }

        MPI_Barrier(MPI_COMM_WORLD);
        eTime = MPI_Wtime();
        Time = eTime - sTime;
        if (id == 0)
        {
                cout << "Длительность: " << Time << endl;
        }
        MPI_Finalize();
        return 0;
}
