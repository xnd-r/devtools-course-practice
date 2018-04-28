// Copyright 2018 Roman Kudalin

#ifndef MODULES_QUEUE_INCLUDE_QUEUE_H_
#define MODULES_QUEUE_INCLUDE_QUEUE_H_

#include <cstddef>
#include <algorithm>
#include <utility>
#include <stdexcept>

template <typename Ty>
class Queue
{
public:
    Queue();
    explicit Queue(std::size_t size);
    Queue(const Queue<Ty>& rhs);
    Queue(Queue<Ty>&& rhs);
    ~Queue();

    Ty& front();
    const Ty& front() const;
    Ty& back();
    const Ty& back() const;
    bool empty() const;
    std::size_t size() const;
    void push(const Ty& data);
    void push(Ty&& data);
    void pop();
    void swap(Queue<Ty>& other);

    Queue<Ty>& operator=(Queue<Ty> rhs);
    bool operator==(const Queue<Ty>& rhs) const;
    bool operator!=(const Queue<Ty>& rhs) const;

private:
    Ty* mem;
    std::size_t dataCount;
    std::size_t capacity;
    int head;
    int tail;
    int nextIndex(int oldIndex);
    void resize();
};


//----------IMPLEMENTATION----------

//----------PUBLIC METHODS----------

template <typename Ty>
Queue<Ty>::Queue() : mem(nullptr), dataCount(0), capacity(0),
head(0), tail(-1) {}

template <typename Ty>
Queue<Ty>::Queue(std::size_t size) : dataCount(0), capacity(size),
head(0), tail(-1)
{
    capacity ? mem = new Ty[capacity]() : mem = nullptr;
}

template <typename Ty>
Queue<Ty>::Queue(const Queue<Ty>& rhs) : dataCount(rhs.dataCount),
capacity(rhs.capacity), head(rhs.head), tail(rhs.tail)
{
    capacity ? mem = new Ty[capacity]() : mem = nullptr;
    std::copy(rhs.mem, rhs.mem + rhs.dataCount, mem);
}

template <typename Ty>
Queue<Ty>::Queue(Queue<Ty>&& rhs) : Queue() { swap(rhs); }

template <typename Ty>
Queue<Ty>::~Queue()
{
    if (mem != nullptr)
        delete[] mem;
}

template <typename Ty>
Ty& Queue<Ty>::front()
{
    if (empty())
        throw std::runtime_error("Queue is empty");
    return mem[head];
}

template <typename Ty>
const Ty& Queue<Ty>::front() const
{
    if (empty())
        throw std::runtime_error("Queue is empty");
    return mem[head];
}

template <typename Ty>
Ty& Queue<Ty>::back()
{
    if (empty())
        throw std::runtime_error("Queue is empty");
    return mem[tail];
}

template <typename Ty>
const Ty& Queue<Ty>::back() const
{
    if (empty())
        throw std::runtime_error("Queue is empty");
    return mem[tail];
}

template <typename Ty>
bool Queue<Ty>::empty() const { return dataCount == 0; }

template <typename Ty>
std::size_t Queue<Ty>::size() const { return dataCount; }

template <typename Ty>
void Queue<Ty>::push(const Ty& data)
{
    if (dataCount == capacity)
        resize();
    tail = nextIndex(tail);
    mem[tail] = data;
    dataCount++;
}

template <typename Ty>
void Queue<Ty>::push(Ty&& data)
{
    if (dataCount == capacity)
        resize();
    tail = nextIndex(tail);
    mem[tail] = std::move(data);
    dataCount++;
}

template <typename Ty>
void Queue<Ty>::pop()
{
    if (empty())
        throw std::runtime_error("Queue is empty");
    mem[head].~Ty();
    dataCount--;
    head = nextIndex(head);
}

template <typename Ty>
void Queue<Ty>::swap(Queue<Ty>& other)
{
    using std::swap;
    swap(dataCount, other.dataCount);
    swap(capacity, other.capacity);
    swap(head, other.head);
    swap(tail, other.tail);
    swap(mem, other.mem);
}

#endif // MODULES_QUEUE_INCLUDE_QUEUE_H_

