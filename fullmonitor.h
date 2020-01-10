#ifndef FULLMONITOR_H
#define FULLMONITOR_H
#include <bits/stdc++.h>
#include "monitor.h"

class FullMonitor: Monitor {
public:
    FullMonitor();

    std::queue<int> copy_queue(const std::queue<int> &Q);
    void printQueue( std::queue<int> qQueue );
    void printBothFifo( std::queue<int> qQueue1, std::queue<int> qQueue2 );

    void* A1(void);
    void* A2(void);
    void* B1(void);
    void* B2(void);

    static void* A1_helper( void* context );
    static void* A2_helper( void* context );
    static void* B1_helper( void* context );
    static void* B2_helper( void* context );


private:
    std::queue<int> evenQueue;
    std::queue<int> oddQueue;

    int evenValue, oddValue;

    Condition con_A1, con_A2, con_B1, con_B2;
};

#endif /* FULLMONITOR_H */