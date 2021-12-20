#include <mpi.h>
#include <time.h>
#include <cstdlib>
#include <cmath>
#include <iostream>
using namespace std;


int main(int argc, char* argv[])
{
        int id, np;
        double eTime,sTime,Time, gres;
        long long i, N=10000;
        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &id);
        MPI_Comm_size(MPI_COMM_WORLD, &np);
        MPI_Barrier(MPI_COMM_WORLD);
        sTime = MPI_Wtime();
        long long lN = N/np;
        int a = 10;
        int b = 20;
        double h = (double)(b-a)/(double)N;
        double buf, res;
        for(int i = 1+id; i < lN; i+=id+1)
        {
                buf = a + i*h;
                res += buf*buf - 2*buf;
        }

        res *= h;
        MPI_Reduce(&res,&gres,1,MPI_DOUBLE, MPI_SUM,0,MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
        eTime = MPI_Wtime();
        Time =eTime - sTime;
        if (id == 0)
        {
                cout << "Значение интеграла: " << gres << endl;
                cout << "Длительность: " << Time << endl;
        }
        MPI_Finalize();
        return 0;
}
