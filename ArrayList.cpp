#include "ArrayList.h"
#include <cstdint>
#define MAX_CAPACITY 128

// an arraylist specifically for resource constrained devices
// 
class ArrayList {
private:
    int* data; 
    int idx;
    int size = 10;

public:
    ArrayList () {
        idx = 0;
        data = new int[size];
    }

    bool resize() {
        if (size * 2 <= MAX_CAPACITY) {
            int* data2 = new int[size *= 2]; 
            for (int i = 0; i < idx; i++) {
                data2[i] = data[i]; 
            }

            delete[] data;
            data = data2;
            return true;
        } 
        return false;
    }

    bool push(int value) {
        if (idx >= size) {
            if (!resize()) {return false;}
        }
        data[idx++] = value;
        return true;
    }

    bool push_front(int value) {
        if (idx >= size) {
            if (!resize()) {return false;};
        }
        for (int i = idx; i > 0; i--) {
            data[i] = data[i - 1];
        }
        data[0] = value;
        idx++;
        return true;
    }

    bool insert(int index, int value) {
        if (index == idx) {
            if (!push(value)) {return false;};
        } else if (index == 0) {
            if (!push_front(value)) {return false;};
        } else {
            if (idx >= size - 1) {
                if (!resize()) {return false;} ;
            }
            for (int i = idx; i > index; i--) {
                data[i] = data[i - 1];
            }
            data[index] = value;
            idx++;
        }
        return true;
    }

    // returns all occurances of 'value' in a bitmask composed of 2 uint32_t integers in the form low (0 - 63), high (64 - 128)
    // there is a 1 in the index where value was found and 0 where it wasn't
    uint64_t* find(int value) {
        bool results = false;
        uint64_t arr[2]; // arr[0] represents bit 0-63 and arr[1] is bit 64-127

        for (int i = 0; i < 64; i++) {
            if (data[i] == value) {
                arr[0] |= (arr[0] << i);                
                results = true;
            }
        }
        for (int i = 64; i < 128; i++) {
            if (data[i] == value) {
                arr[1] |= (arr[1] << i);                
                results = true;
            }
        }
        if (!results) {return nullptr;}
        return arr;
    }

    int get(int index) {
        if (index < 0 || index >= idx) {return -1;}  
        return data[index];
    }

    bool set(int index, int value) {
        if (index < 0 || index >= idx) {return -1;}  
        data[index] = value;
    }

    ~ArrayList() {
        delete[] data;     
    }
};