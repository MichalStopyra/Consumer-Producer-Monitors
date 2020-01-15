#include <iostream>
#include "fullmonitor.h"

FullMonitor::FullMonitor() {
    oddValue = 1;
    evenValue = 0;
}


std::queue<int> FullMonitor::copy_queue(const std::queue<int> &Q) {
    std::queue<int> Q2 = Q;
    return Q2;
}

void FullMonitor::printQueue( std::queue<int> qQueue )
{
    std::queue<int> q = copy_queue(qQueue);
    while (!q.empty()){
        std::cout<<" "<<q.front();
        q.pop();
    }
    return;
}

void FullMonitor::printBothFifo( std::queue<int> qQueue1, std::queue<int> qQueue2 ) {
    std::cout<<"-------------------------------------------------------------------"<<std::endl;
    printQueue( qQueue1 );
    std::cout<<std::endl<<"-------------------------------------------------------------------"<<std::endl<<std::endl;
    std::cout<<"-------------------------------------------------------------------"<<std::endl;
    printQueue( qQueue2 );
    std::cout<<std::endl<<"-------------------------------------------------------------------"<<std::endl<<std::endl;


}

void* FullMonitor::A1 ( void ) {

    while ( true ) {
        enter();

        if( evenQueue.size() >= 10 )
                wait( con_A1 );

        //std::cout<<"A1\n";
        evenQueue.push ( evenValue );
        std::cout<<"dodano "<< evenValue<<" do parz, l el w p: "<<evenQueue.size()<<std::endl;
        printBothFifo( evenQueue, oddQueue );

        if( evenQueue.size() > oddQueue.size() )
            signal( con_A2 );

        if( evenQueue.size() + oddQueue.size() >= 3 && evenQueue.size() != 0 )
            signal( con_B1 );


        evenValue = ( evenValue + 2 )%100;

        leave();
    }
}

void* FullMonitor::A1_helper( void* context ){
    return ( (FullMonitor*) context ) -> A1 ( );
}


void* FullMonitor::A2 ( void ) {

    while ( true ) {
        enter();
       // std::cout<<"A2\n";

        if( evenQueue.size() <= oddQueue.size() )
            wait( con_A2 );

        oddQueue.push ( oddValue );
        std::cout<<"dodano "<< oddValue<<" do nieparz, l el w np: "<<oddQueue.size()<<std::endl;
        printBothFifo( evenQueue, oddQueue );

        if( evenQueue.size() + oddQueue.size() >= 7 && oddQueue.size() != 0 )
            signal( con_B2 );

        oddValue = ( oddValue + 2 )%100;

        leave();
    }
}

void* FullMonitor::A2_helper( void* context ){
    return ( (FullMonitor*) context ) -> A2 ( );
}


void* FullMonitor::B1 ( void ) {

    while ( true ) {
        enter();
        //std::cout<<"B1\n";

        if( evenQueue.size() + oddQueue.size() < 3 || evenQueue.empty() )
            wait( con_B1 );

        int deletedValue = evenQueue.front();
        evenQueue.pop ();
        std::cout<<"usunieto "<< deletedValue<<" od parz, l el w p: "<<evenQueue.size()<<std::endl;
        printBothFifo( evenQueue, oddQueue );

        if(evenQueue.size() > oddQueue.size() )
            signal ( con_A2 );

        if( evenQueue.size() < 10 )
            signal( con_A1 );

        if( evenQueue.size() + oddQueue.size() == 6)
            wait( con_B2 );

        leave();
    }
}

void* FullMonitor::B1_helper( void* context ){
    return ( (FullMonitor*) context ) -> B1 ( );
}


void* FullMonitor::B2 ( void ) {

    while ( true ) {
        enter();
        //std::cout<<"B2\n";

        if( evenQueue.size() + oddQueue.size() < 7 || oddQueue.empty() )
            wait( con_B2 );

        int deletedValue = oddQueue.front();
        oddQueue.pop ();
        std::cout<<"usunieto "<< deletedValue<<" od nieparz, l el w np: "<<oddQueue.size()<<std::endl;
        printBothFifo( evenQueue, oddQueue );

        if( evenQueue.size() > oddQueue.size() )
            signal( con_A2 );

        if( evenQueue.size() + oddQueue.size() == 2 )
            wait( con_B1 );

        leave();
    }
}

void* FullMonitor::B2_helper( void* context ){
    return ( (FullMonitor*) context ) -> B2 ( );
}
