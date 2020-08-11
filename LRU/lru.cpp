//
//  main.cpp
//  Paging-Algorithms
//
//  Created by Karthik Viswanathan on 8/11/20.
//  Copyright © 2020 Karthik Viswanathan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <sstream>

using namespace std;

void lru(long long int pages [] , long long int pageCount, long long int frames);
void print_seq(long long int len , long long int order[], long long int page_fault , long long int valid_count);

void lru(long long int pages [] , long long int pageCount, long long int frames)
{
    map<long long int , long long int> timestamp;
    vector<long long int> pager;
    long long int len = 0;
    long long int present[pageCount+1] ;
    long long int page_faults = 0;
    long long int hits = 0;
    long long int order[pageCount+1];
    long long int len_order = 0;
    for(long long i = 0 ; i < pageCount ; i++)
        present[i] = 0;
    for(long long int i = 0 ; i < pageCount ; i++)
    {
        if(len < frames)
        {
            if(present[pages[i]]){
                hits++;
            }
            if(!present[pages[i]]){
                pager.push_back(pages[i]);
                present[pages[i]] = 1;
                len++;
                page_faults++;
            }
            timestamp[pages[i]] = i;
        }
        else{
            
                if(present[pages[i]])
                {
                    timestamp[pages[i]] = i;
                    hits++;
                }
            
                else if(!present[pages[i]]){
                    page_faults++;
                    long long int min = INT_MAX;
                    long long int min_val = -1;
                    for(long long int j = 0 ; j < len ; j++)
                    {
                        if(timestamp[pager[j]] < min)
                        {
                            min = timestamp[pager[j]];
                            min_val = pager[j];
                        }
                    }
                    pager.erase(std::remove(pager.begin(), pager.end(), min_val), pager.end());
                    order[len_order] = min_val;
                    len_order++;
                    present[min_val] = 0;
                    pager.push_back(pages[i]);
                    present[pages[i]] = 1;
                    timestamp[pages[i]] = i;
                }
        }
    }
    while(!pager.empty())
    {
        order[len_order] = pager.back();
        len_order++;
        pager.pop_back();
    }
    
    print_seq(len_order , order , page_faults , hits);
        
}

void print_seq(long long int len , long long int order[], long long int page_fault , long long int valid_count)
{
    ofstream out1;
    out1.open("results.txt");
    out1<<"Page fault: "<<page_fault<<endl;
    out1<<"Valid Count: "<<valid_count<<endl;
    for(long long int i = 0 ; i < len ; i++)
    {
        out1<<order[i]<<endl;
    }
}
    


int main(int argc, const char * argv[]) {
    if(argc!=3)
    {
        cout<<"Wrong number of arguments"<<endl;
        return -1;
    }
    string filename = argv[1];
    ifstream infile;
    infile.open(filename.c_str());
    
    if(!infile.is_open()){
        cout<<"Error opening "<<filename<<endl;
        return 1;
    }
    
    vector<long long int> values;
    long long int n=0;
    string line;
    long long int val;
    
    while(getline(infile, line)){
        stringstream is(line);
        while(is >> val){
            values.push_back(val);
        }
        n++;
    }
    
    long long int frame_size = atoi(argv[2]);
    long long int pages[1000000] = {0};
    for(long long int i = 0 ; i < n ; i++)
    {
        pages[i] = values[i];
    }
    lru(pages , n , frame_size);
    cout<<"Hello World"<<endl;
    return 0;
}
