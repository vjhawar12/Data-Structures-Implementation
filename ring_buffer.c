#define CAPACITY 100

// circular queue not stack
typedef struct ring_buffer {
    int data[CAPACITY];
    int front;
    int end;
} ring_buffer;

static int empty(ring_buffer* buffer) {
    return buffer->front == buffer->end;
}


static int full(ring_buffer* buffer) {
    return ((buffer->end + 1) % CAPACITY) == buffer->front;   
}

static void push(ring_buffer* buffer, int value) {
    if (!full(buffer)) {
        buffer->data[buffer->end++] = value;
        buffer->end = buffer->end % CAPACITY;
    }
}

static int pop(ring_buffer* buffer) {
    if (!empty(buffer)) {
        int value = buffer->data[buffer->front++]; 
        buffer->front = buffer->front % CAPACITY;
        return value;
    }

    return -1;
} 

