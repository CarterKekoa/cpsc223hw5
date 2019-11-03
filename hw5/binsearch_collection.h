//Carter Mooring
//CPSC 223
//Dr. Bowers
//binsearch_collection.h
//This file helps run the base program and everything I implemented

#ifndef BINSEARCH_COLLECTION_H
#define BINSEARCH_COLLECTION_H

#include <vector>
#include <algorithm>
#include "collection.h"

using namespace std;

template<typename K, typename V>
class BinSearchCollection : public Collection <K ,V>{
  public:

    // insert a key - value pair into the collection
    void insert(const K& key, const V& val);

    // remove a key - value pair from the collection
    void remove(const K& key);

    // find and return the value associated with the key
    bool find(const K& key, V& val) const;

    // find and return the list of keys >= to k1 and <= to k2
    void find(const K& k1, const K& k2, std :: vector <K>& keys) const;

    // return all of the keys in the collection
    void keys(std :: vector <K>& keys) const;

    // return all of the keys in ascending ( sorted ) order
    void sort(std :: vector <K>& keys) const;

    // return the number of keys in collection
    int size() const;

  private:

    // helper function for binary search
    bool binsearch(const K& key, int& index) const;

    // vector storage
    std :: vector<std :: pair <K,V>> kv_list;
};


// This function returns true and sets index if key is found in
// kv_list , and returns false and sets index to where key should go in
// kv_list otherwise . If list is empty , index is unchanged .
template <typename K, typename V>
bool BinSearchCollection <K,V>::binsearch(const K& key, int& index) const
{
  int bottom = 0;
  int top = kv_list.size()-1;
  int middle;
  pair<K, V> p;

  while (bottom <= top){    //while you arnt at the top or end
    middle = (top + bottom) / 2;
    p = kv_list.at(middle);

    if (key > p.first){   //if key is greater than the start
      bottom = middle + 1;
    } else if (key < p.first) {    //else if its less that the start
      top = middle - 1;
    } else if (key == p.first) {  //else if it is equal to the start
      index = middle;
      return true;
    }
  }

  if (kv_list.size() != 0){   //if the size is greater than 0
    index = bottom;
  }else{
    index = 0;
  }

  return false;
}

// insert a key - value pair into the collection
template <typename K, typename V>
void BinSearchCollection<K, V>::insert(const K& key, const V& val)
{
  int counter;
  pair<K, V> tmp;
  tmp.first = key;
  tmp.second = val;
  if(!binsearch(key, counter)){
    kv_list.insert(kv_list.begin() + counter, tmp);
  }
}

// remove a key - value pair from the collection
template <typename K, typename V>
void BinSearchCollection <K, V>::remove(const K& key)
{
  int counter;
  if (binsearch(key, counter)){
    kv_list.erase(kv_list.begin() + counter);
  }
}

// find and return the value associated with the key
template <typename K, typename V>
bool BinSearchCollection<K, V>::find(const K& key, V& val) const
{
  int counter;
  pair<K, V> tmp;
  if (binsearch(key, counter)){
    tmp = kv_list.at(counter);
    val = tmp.second;
    return true;
  }
  return false;
}

// find and return the list of keys >= to k1 and <= to k2
template <typename K, typename V>
void BinSearchCollection<K, V>::find(const K& k1, const K& k2, std :: vector <K>& keys) const
{
  int counter;
  bool hold = binsearch(k1, counter);
  pair<K, V> tmp = kv_list[counter];
  while (tmp.first <= k2 && counter < kv_list.size()){
    keys.push_back(tmp.first);
    counter++;
    tmp = kv_list[counter];
  }
}

// return all of the keys in the collection
template <typename K, typename V>
void BinSearchCollection<K, V>::keys(std :: vector <K>& keys) const
{
  if (kv_list.size() > 0){
    for(pair<K, V> tmp : kv_list){
      keys.push_back(tmp.first);
    }
  }
}

// return all of the keys in ascending ( sorted ) order
template <typename K, typename V>
void BinSearchCollection<K, V>::sort(std :: vector <K>& keys) const
{
  this->keys(keys);
}

// return the number of keys in collection
template <typename K, typename V>
int BinSearchCollection<K, V>::size() const
{
  return kv_list.size();
}

#endif
