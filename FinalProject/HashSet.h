#pragma once
#include <list>
#include <functional>
using namespace std;
using std::list;

const int INITIAL_CAPACITY = 7;

template<class T>
class HashSet {
public:
    HashSet() : tSize(0), capacity(INITIAL_CAPACITY) {
        data = new list<T>[INITIAL_CAPACITY];
    }

    ~HashSet() { delete [] data; }

    bool insert(T item) {
        // implement insert here
        // return true if item was inserted, false if item was already in the set
        size_t index = getIndex(item);
        for (auto thing : data[index]){
            if(thing == item){ return false; }
        }

        data[index].push_front(item); 
        tSize++;
        return true; 
    }

    bool remove(T item) {
        // implement remove here
        // return true if item was removed, false if item wasn't in the set
        if(!contains(item)){return false;}
        tSize--;
        size_t index = getIndex(item);
        data[index].remove(item);
        
        return true;
    }

    bool contains(T item) const {
        // implement contains here
        // return true if item is in the set, false otherwise
        size_t index = getIndex(item);
        for (auto entry : data[index]){
            if(entry == item){ return true; }
        }
        return false;
    }

    void clear() {
        // implement clear here
        // remove all elements from the set
        delete [] data;
        tSize = 0;
        data = new list<T>[INITIAL_CAPACITY];
    }

    int size() const {
        // implement size here
        // return the number of elements in the set
        return tSize;
    }
private:
    int tSize;
    int capacity;
    list<T>* data;

    size_t getIndex(T item) const {
        size_t hashCode = hash<T>{}(item);
        return hashCode % capacity; // index
    }

};
