#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include <string>
#include <vector>

class File;

class HashMap{
    private:
        struct Node {
            std::string key;
            File* value;
            Node* next;
            Node(const std::string&k, File* v) : key(k), value(v), next(nullptr){};
            ~Node(){};
        };

        std::vector<Node*> table;
        int bucketCount;
        int count;
        const double loadFactorThreshold = 0.7;
        int hashFunction(const std::string &key, int mod);
        void rehash();
    
    public:
        HashMap(int initialSize = 101);
        void put(const std::string &key, File* value);
        bool get(const std::string &key, File* &value);
        void remove(const std::string &key);
        std::vector<std::string> keys();
        ~HashMap();
};

#endif