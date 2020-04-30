//
// Created by lukas on 07.04.19.
//

#pragma once

#include <iostream>
#include <vector>

template<class keytype, class valuetype>
class Hashmap {
public:
    /**
     * add key-value pair to hashmap
     * @param key keyvalue
     * @param value valuevalue
     */
    void add(keytype key, keytype value);

    /**
     * get key of specific position
     * @param position int position
     * @return responding key object
     */
    keytype getKey(int position);

    /**
     * get value of specific position
     * @param position int position
     * @return responding value object
     */
    valuetype getValue(int position);

    /**
     * get size of Hashmap
     * @return size of Hashmap
     */
    int size();

private:
    std::vector<keytype> keys;
    std::vector<valuetype> values;
};

template<class keytype, class valuetype>
void Hashmap<keytype, valuetype>::add(keytype key, keytype value) {
    keys.push_back(key);
    values.push_back(value);
}

template<class keytype, class valuetype>
keytype Hashmap<keytype, valuetype>::getKey(int position) {
    return keys.at(position);
}

template<class keytype, class valuetype>
valuetype Hashmap<keytype, valuetype>::getValue(int position) {
    return values.at(position);
}

template<class keytype, class valuetype>
int Hashmap<keytype, valuetype>::size() {
    return (int) (keys.size());
}
