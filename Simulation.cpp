//
// Created by Shafeey on 10/30/2016.
//

#include <fstream>
#include <iostream>
#include "Simulation.h"

Simulation::Simulation(Trace *pTrace, Cache *pCache):
        pTrace(pTrace), pCache(pCache){ }

void Simulation::simulate() {

    for(std::vector<MemAccess>::iterator it = pTrace->trace.begin(); it != pTrace->trace.end(); ++it){
        bool hit = pCache->access(it->address);

        if(hit)
            stats.num_hits++;

        stats.total++;
    }

    std::cout << "Simulation complete." << std::endl << std::endl;

    std::cout << "Memory access: " << std::dec << stats.total << std:: endl;
    std::cout << "Hit: " << stats.num_hits << std::endl;
	std::cout << "Miss rate : " << stats.num_hits*100.0/stats.total << "%" << std::endl;
    std::cout << "Miss: " << stats.total - stats.num_hits << std::endl;
    std::cout << "Miss rate : " << (stats.total - stats.num_hits)*100.0/stats.total << "%" << std::endl;
}


void Trace::load(std::string file_name) {
    this->file_name = file_name;

    std::ifstream infile;

    uint32_t address;
    char type;
    int offset;
    unsigned long base;

    infile.open(file_name.c_str(), std::ifstream::in);

    if ( !infile ) {
        std::cout << "Failed to open file " << file_name << std::endl;
        return;
    }

    while (infile >> type >> offset >> std::hex >> base)
    {
        address = (uint32_t) base;
        trace.push_back(MemAccess(type, (uint32_t) address));
    }

    infile.close();
    std::cout << "File read complete!!" << std::endl;

}

MemAccess::MemAccess(char type, uint32_t address) :
                        type(type), address(address){ }
