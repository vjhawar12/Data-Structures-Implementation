#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#endif


class ArrayList {
private:
    int* data; 
    int idx;
    int capacity = 10000;

public:
    ArrayList();

    int* resize();

    void insert_front(int);
    void insert_back(int);
    void insert(int, int);

    int find(int);

    int get();
    void set(int, int);

    ~ArrayList();
};