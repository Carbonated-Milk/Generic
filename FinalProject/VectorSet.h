#pragma once

#include <vector>
using std::vector;

template<class T>
class VectorSet {
public:
    bool contains(T item) const {
        // implement contains here
        for(T element : vSet){
            if(element == item){
                return true;
            }
        }
        return false;
        // return true if item is in the set and false if not
    }

    bool insert(T item) {
        // implement insert here
        if(contains(item)){ return false; }

        vSet.push_back(item);
        return true;
        // return true if item is inserted and false if item is already in the
        // set
    }

    bool remove(T item) {
        // implement remove here
        if(!contains(item)){ return false; }

        for (int i = 0; i < size(); i++){
            if(vSet.at(i) == item){
                vSet.erase(vSet.begin()+i);
                return true;
            }
        }
        
        return false;
        // return true if item is removed and false if item wasn't in the set
    }

    int size() const {
        // implement size here
        return vSet.size();
        // return the number of items in the set
    }

    bool empty() const {
        // implement empty here
        return vSet.size() == 0;
        // return true if the set is empty and return false otherwise
    }

    void clear() {
        // implement clear here
        vSet.clear();
        // remove all items from the set
    }

private:
    vector<T> vSet = {};
};