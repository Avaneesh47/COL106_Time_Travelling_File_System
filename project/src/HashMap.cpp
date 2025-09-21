#include "../include/HashMap.hpp"
#include "../include/File.hpp"

HashMap::HashMap(int initialSize): bucketCount(initialSize), count(0) {
    table.resize(bucketCount, nullptr);
};

int HashMap::hashFunction(const std::string &key, int mod){
    unsigned long hash = 0;
    for(char c: key){
        hash = hash*31 + c;
    }
    return hash % mod;
};

void HashMap::rehash(){
    int newBucketCount = bucketCount * 2;
    std::vector<Node*> newTable(newBucketCount, nullptr);

    for(int i=0; i<bucketCount; i++){
        Node* curr = table[i];
        while (curr) {
            int idx = hashFunction(curr->key, newBucketCount);
            Node* nextNode = curr->next;

            curr->next = newTable[idx];
            newTable[idx] = curr;

            curr = nextNode;
        }
    }

    table = move(newTable);
    bucketCount = newBucketCount;
};

void HashMap::put(const std::string &key, File* value){
    int idx = hashFunction(key, bucketCount);
    Node* curr = table[idx];

    while (curr) {
        if(curr->key == key){
            curr->value = value;
            return ;
        }
        curr = curr->next;
    }

    Node* newNode = new Node(key, value);
    newNode->next = table[idx];
    table[idx] = newNode;
    count++;

    if((double)count / bucketCount > loadFactorThreshold){
        rehash();
    }
};

bool HashMap::get(const std::string &key, File* &value){
    int idx = hashFunction(key, bucketCount);
    Node* curr = table[idx];

    while (curr) {
        if(curr->key == key){
            value = curr->value;
            return true;
        }
        curr = curr->next;
    }
    return false;
};

void HashMap::remove(const std::string &key){
    int idx = hashFunction(key, bucketCount);
    Node* curr = table[idx];
    Node* prev = nullptr;

    while (curr) {
        if(curr->key == key){
            if(prev) prev->next = curr->next;
            else table[idx] = curr->next;
            delete curr;
            count--;    
            return ;
        }
        prev = curr;
        curr = curr->next;
    }
};

std::vector<std::string> HashMap::keys() {
    std::vector<std::string> result;
    for (int i = 0; i < bucketCount; i++) {
        Node* curr = table[i];
        while (curr) {
            result.push_back(curr->key);
            curr = curr->next;
        }
    }
    return result;
};

HashMap::~HashMap(){
    for(int i=0; i<bucketCount; i++){
        Node* curr = table[i];
        while (curr) {
            Node* next = curr->next;
            delete curr->value;
            delete curr;
            curr = next;
        }
    }
};