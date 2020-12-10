#include <iostream>
#include "unistd.h"
#include "Simulation.h"
#include "Cache.h"

using namespace std;

int main(int argc, char *argv[]) {

    int opt;
    string file_name = "gcc-10K.memtrace";
    uint32_t cache_size = 512;
    uint32_t block_size = 16;
    uint32_t m = 4;

    while ((opt = getopt(argc,argv,"f:c:b:m:")) != EOF)
        switch(opt)
        {
            case 'f': file_name.assign(optarg); break;
            case 'c': cache_size = (uint32_t) stoul(optarg); break;
            case 'b': block_size = (uint32_t) stoul(optarg); break;
            case 'm': m = (uint32_t) stoul(optarg); break;
            case '?': fprintf(stderr, "usage is \n -f file_name : to take input from file_name"
                        "\n -c <Cache size in KB>"
                        "\n -b <Block size(Byte)>"
                        "\n -m <Ways number>"
                );
            default: cout<<endl; abort();
        }

    cout << "Loading Memory Trace... " << file_name << " ... ";
    Trace trace;
    trace.load(file_name);

    cout << "Loading Cache... " ;
    cout << cache_size << " KB";
    if(m > 1) cout << ", " << m << "-way set associative";
    else if(m < 1) cout << ", Fully associative";
    else cout << ", Direct mapped";
    cout << endl;

    Cache cache = Cache(cache_size * 1024, block_size, m);

    cout << "Initiating Simulation ..." << endl;

    Simulation simulation(&trace, &cache);
    simulation.simulate();

    return 0;
}
