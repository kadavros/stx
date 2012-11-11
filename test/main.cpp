#include <stx/log.hpp>
#include <stx/elapsed_timer.hpp>
#include <stx/sleep.hpp>
#include <iostream>
using namespace std;
using namespace stx;

int main(int argc, char* argv[])
{
    elapsed_timer t;
    cout << "main()" << endl;
    sleep(4);
    STX_LOG_INFO("stx log");
    cout << t.elapsed() << endl;
    return 0;
}
