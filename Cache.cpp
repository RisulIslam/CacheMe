//
// Created by Shafeey on 11/11/2016.
//

#include <algorithm>
#include <cmath>
#include <iostream>
#include <cassert>
#include <iomanip>
#include "Cache.h"
using namespace std;

bool Cache::access(uint32_t address) {
    bool hit = false;
    uint32_t index = (address >> b) & index_mask;
    uint32_t tag = address >> (b + s);

    assert(index < num_sets);

    std::list<CacheLine> &set = cache_sets[index];
    const std::list<CacheLine>::iterator &it = std::find(set.begin(), set.end(), CacheLine(tag));

    if(it != set.end()){ // Found match in cache line
        hit = true;

        // Take matching entry to the front
        set.emplace_front(tag);
        set.erase(it);
    }
    else {
        // Insert new cache entry
        set.emplace_front(tag);

        // Remove last used if occupancy > number of sets
        if(set.size() > num_ways)
            set.pop_back();
    }

//    cout << "Address: " << setw(8) << hex << address << "\tTag: " << setw(8) << tag << "\tIndex: " << setw(8) << hex << index;
//    cout << "\t" << (hit ? "hit" : "miss") << endl;
    return hit;
}

Cache::Cache(uint32_t cache_size, uint32_t block_size, uint32_t num_ways)
        : block_size(block_size),
          num_ways(num_ways ? num_ways : (cache_size/block_size)),
          num_sets(num_ways ? (cache_size/block_size)/num_ways : 1),
          b((uint32_t) log2(block_size)), s((uint32_t) log2(num_sets)),
          index_mask((uint32_t) (1<<s) - 1),
          cache_sets(std::vector<std::list<CacheLine>>(num_sets, std::list<CacheLine>()))
{


    cout << "Block size: " << block_size << " byte" << endl;
    cout << "Number of sets: " << num_sets << endl;
    cout << "Tag bits: " << 32 - b - s << ", ";
    cout << "Index bits: " << s << ", ";
    cout << "Offset bits: " << b << "\n" << endl;
}


bool CacheLine::operator==(const CacheLine &rhs) const {
    return tag == rhs.tag ;
}

bool CacheLine::operator!=(const CacheLine &rhs) const {
    return !(rhs == *this);
}

CacheLine::CacheLine(uint32_t tag) : tag(tag) { }
