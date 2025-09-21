#ifndef HEAP_HPP
#define HEAP_HPP

#include <string>
#include <vector>

class File;

class Heap{
    private:
        std::vector<std::pair<std::string, File*>> arr;
        int size;
        bool useVersions;
        bool moreRecent(File* file1, File* file2);
        bool greaterVersions(File* file1, File* file2);
        bool comp(File* file1, File* file2);
        void buildHeap();

    public:
        Heap(std::vector<std::pair<std::string, File*>> files, bool useVersions);
        std::pair<std::string, File*> pop();
};

#endif