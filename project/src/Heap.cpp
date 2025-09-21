#include "../include/Heap.hpp"
#include "../include/File.hpp"
using namespace std;

bool Heap::moreRecent(File* file1, File* file2){
    if(file1->modified_timestamp>file2->modified_timestamp){
        return true;
    }
    return false;
};

bool Heap::greaterVersions(File* file1, File* file2){
    if(file1->total_versions>file2->total_versions){
        return true;
    }
    return false;
};

bool Heap::comp(File* file1, File* file2){
    if(useVersions){
        return greaterVersions(file1, file2);
    }
    return moreRecent(file1, file2);
};

void Heap::buildHeap(){
    int n = arr.size();
    for(int j=n-1; j>=0; j--){
        int i = j;
        while(i<size){
            int left = 2*i+1;
            int right = 2*i+2;
            int max_index = i;

            if(left < size && comp(arr[left].second, arr[max_index].second)){
                max_index = left;
            }
            
            if(right < size && comp(arr[right].second, arr[max_index].second)){
                max_index = right;
            }

            if(max_index != i){
                swap(arr[i], arr[max_index]);
                i = max_index;
            }
            else{
                break;
            }
        }
    }
};

Heap::Heap(vector<pair<string, File*>> files, bool useVersions){
    this->useVersions = useVersions;
    arr = files;
    size = arr.size();
    buildHeap();
};

pair<string, File*> Heap::pop(){
    pair<string, File*> top = arr[0];
    int i = 0;
    arr[0] = arr[size-1];
    size--;
    while(i<size){
        int left = 2*i + 1;
        int right = 2*i + 2;
        int max_index = i;

        if(left < size && comp(arr[left].second, arr[max_index].second)){
            max_index = left;
        }
        if(right < size && comp(arr[right].second, arr[max_index].second)){
            max_index = right;
        }

        if(max_index != i){
            swap(arr[i], arr[max_index]);
            i = max_index;
        }
        else{
            break;
        }
    }
    return top;
};