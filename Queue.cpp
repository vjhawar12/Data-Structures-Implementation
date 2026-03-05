class Queue {
    int* data;
    int capacity; 
    int e; 
    int f;

    Queue(int capacity) {
        this->capacity = capacity;
        e = 0;
        f = 0;
        data = new int[capacity]; 
    }

    bool isFull() {
        return e == capacity - 1;
    }

    bool isEmpty() {
        return f == 0;
    }

    void enqueue(int element) {
        if (!isFull()) {
            data[e++] = element;
        }
    }

    int dequeue() {
        if (!isEmpty()) {
            return data[f++];
        }
    }

    ~Queue() {
        delete data;
    }
}; 