#include <iostream>
#include "fullmonitor.h"


int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cout << "Uruchom program komendą: ./a.out nrA1 nrA2 nrB1 nrB2" << std::endl;
       // return 1;
    }

    int nrA1 = atoi(argv[1]);
    int nrA2 = atoi(argv[2]);
    int nrB1 = atoi(argv[3]);
    int nrB2 = atoi(argv[4]);

    if (nrA1 <= 0 || nrA2 <= 0 || nrB1 <= 0 || nrB2 <= 0) {
        std::cout << "Error: podaj liczby dodatnie " << std::endl;
        return 1;
    }

    FullMonitor monitor_m;
    pthread_t thread_t[nrA1 + nrA2 + nrB1 + nrB2];

    int j = 0;
    for (int i = j; i < j + nrA1; ++i)
        pthread_create( &thread_t[i], NULL, &FullMonitor::A1_helper, &monitor_m );
    j += nrA1;

    for (int i = j; i < j + nrA2; ++i)
        pthread_create( &thread_t[i], NULL, &FullMonitor::A2_helper, &monitor_m );
    j += nrA2;

    for (int i = j; i < j + nrB1; ++i)
        pthread_create( &thread_t[i], NULL, &FullMonitor::B1_helper, &monitor_m );
    j += nrB1;

    for (int i = j; i < j + nrB2; ++i)
        pthread_create( &thread_t[i], NULL, &FullMonitor::B2_helper, &monitor_m );
    j += nrB2;


    for (int i = 0; i < j; ++i)
        pthread_join( thread_t[i], NULL );

    return 0;
}