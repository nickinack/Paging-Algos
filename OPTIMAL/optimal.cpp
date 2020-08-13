//
//  main.cpp
//  OptimalPager
//
//  Created by Karthik Viswanathan on 8/13/20.
//  Copyright © 2020 Karthik Viswanathan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <queue>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

void optimal(long long int pages[] , long long int pageSize , long long int frames);
long long int predict_least_index(vector<long long int> pager , long long int pages[] , long long int pageSize , long long int frames , long long int i);
void print_seq(long long int len , long long int order[], long long int page_fault , long long int valid_count);

void optimal(long long int pages[] , long long int pageSize , long long int frames)
{
    long long int hits = 0;
    long long int page_faults = 0;
    vector<long long int> pager;
    long long int pager_len = 0;
    long long int present[pageSize+1];
    long long int order[pageSize+1];
    long long int order_len = 0;
    
    for(long long int i = 0 ; i < pageSize ; i++)
        present[i] = 0;
    
    for(long long int i = 0 ; i < pageSize ; i++)
    {
        if(pager_len < frames)
        {
            if(present[pages[i]])
                hits++;
            
            if(!present[pages[i]])
            {
                pager.push_back(pages[i]);
                present[pages[i]] = 1;
                page_faults++;
                pager_len++;
            }
        }
        else
        {
            if(present[pages[i]])
                hits++;
            else
            {
                page_faults++;
                long long int j = predict_least_index(pager , pages , pageSize , frames , i);
                present[pager[j]] = 0;
                order[order_len] = pager[j];
                order_len++;
                pager[j] = pages[i];
                present[pages[i]] = 1;
            }
            
        }
    }
    while(!pager.empty())
    {
        order[order_len] = pager.back();
        pager.pop_back();
        order_len++;
    }
    print_seq(pageSize, order, page_faults, hits);
}

long long int predict_least_index(vector<long long int> pager , long long int pages[] , long long int pageSize , long long int frames , long long int i)
{
    long long int res = -1;
    long long int farthest = i+1;
    i += 1;
    long long int j , k;
    for(k = 0 ; k < frames ; k++)
    {
        for(j = i ; j<pageSize ; j++)
        {
            if(pages[j] == pager[k] && j>farthest)
            {
                farthest = j;
                res = k;
                break;
            }
        }
        if(j == pageSize) return k;
    }
    
    if(res == -1)
        return 0;
    else
        return res;
}

void print_seq(long long int len , long long int order[], long long int page_fault , long long int valid_count)
{
    ofstream out1;
    out1.open("result.txt");
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
    cout<<frame_size<<endl;
    for(long long int i = 0 ; i < n ; i++)
    {
        pages[i] = values[i];
    }
    optimal(pages , n , frame_size);
    return 0;
}
