#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <sstream>

using namespace std;

void fifo(long long int n , long long int present[] , long long int pages[], long long int frame_size);
void print_seq(long long int len , long long int order[], long long int page_fault , long long int valid_count);

void fifo(long long int n , long long int present[] , long long int pages[], long long int frame_size)
{
    queue<long long int> q;
    long long int page_fault = 0;
    long long int valid_count = 0;
    long long int order[n] = {0};
    long long int len = 0;
    for(long long int i = 0 ; i < n ; i++)
    {
        if(present[pages[i]])
        {
            valid_count++;
        }
        else
        {
            q.push(pages[i]);
            present[pages[i]] = 1;
            if(q.size() > frame_size)
            {
                present[q.front()] = 0;
                order[len] = q.front();
                len++;
                q.pop();
            }
            page_fault++;
        }
        
    }
    while(!q.empty())
    {
        order[len] = q.front();
        len++;
        q.pop();
    }

    print_seq(len, order, page_fault , valid_count);

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

int main(int argc, char **argv)
{
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
    long long int present[n] = {0};
    long long int pages[n] = {0};
    for(long long int i = 0 ; i < n ; i++)
    {
        pages[i] = values[i];
    }
    fifo(n,present,pages,frame_size);


}