#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include "File.hpp"
#include "HashMap.hpp"
#include "Heap.hpp"

#include <string>
#include <vector>

class FileManager{
    private:
        HashMap Files;
    public:
        FileManager();
        void create(std::string filename);
        void read(std::string filename);
        void insert(std::string filename, std::string content);
        void update(std::string filename, std::string content);
        void snapshot(std::string filename, std::string message);
        void rollback(std::string filename, std::string version_id);
        void history(std::string filename);
        void recent_files(int num);
        void biggest_trees(int num);
};

#endif