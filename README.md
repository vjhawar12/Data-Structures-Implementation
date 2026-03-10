# Embedded Data Structures (allocated on Stack only)

This repo is a **design guide** for core data structures built for constrained embedded systems.

It focuses on:
- **No dynamic memory allocation**
- **Deterministic operations**
- **Small memory footprint**
- **Embedded-friendly APIs**
- **ISR-safe patterns where possible**

## API style

Containers are simple and predictable:
- initialize with fixed buffers/capacity
- return status codes (`OK`, `FULL`, `EMPTY`, `NOT_FOUND`, etc.)
- avoid exceptions and hidden allocations
- expose `size`, `capacity`, `is_full`, `is_empty`
- make boundary behavior explicit

---

## 1) Ring Buffer (Circular Buffer)

**What it is:** A fixed-size circular array for streaming data.

**Core idea:** Two indices (`head`, `tail`) wrap around capacity using modulo arithmetic.

**Why it fits embedded:**
- O(1) push/pop
- fixed memory
- great for UART/SPI/event buffering

**Key notes:**
- define full/empty rule clearly (`count` field or one-slot-open strategy)
- for ISR + main-loop usage, use SPSC (single producer/single consumer) pattern

---

## 2) Static Queue (FIFO)

**What it is:** First-In-First-Out queue with compile-time or fixed runtime capacity.

**Typical operations:** enqueue, dequeue, front, is_empty, is_full.

**Performance target:** O(1) enqueue/dequeue.

**Embedded notes:**
- best built on top of a ring buffer
- return `FULL`/`EMPTY` instead of blocking or allocating more memory

---

## 3) Static Stack

**What it is:** Last-In-First-Out stack using a fixed array and a top index.

**Typical operations:** push, pop, peek, is_empty, is_full.

**Performance target:** O(1) push/pop.

**Embedded notes:**
- very low overhead
- useful for parsers, temporary work items, DFS-like logic
- overflow/underflow must be explicit status returns

---

## 4) Memory Pool Allocator

**What it is:** Fixed-size block allocator from a preallocated memory region.

**Core idea:** Keep a free list of available blocks; allocate/free are constant-time in common designs.

**Why it matters:**
- replaces heap usage with deterministic allocation
- avoids fragmentation from general-purpose allocators

**Embedded notes:**
- great for message objects, node pools, and RT tasks
- guard against double-free and invalid pointer free

---

## 5) Bitset / Bitmap

**What it is:** Compact bit-level storage where each flag uses 1 bit.

**Typical operations:** set, clear, test, toggle, reset_all.

**Performance target:** O(1) per bit operation.

**Embedded notes:**
- ideal for status flags, resource tracking, feature masks
- memory usage is tiny compared to `bool[]` on many targets

---

## 6) Priority Queue (Binary Heap)

**What it is:** Queue where highest (or lowest) priority item comes out first.

**Core representation:** Fixed array as binary heap.

**Typical operations and cost:**
- insert: O(log n)
- pop top: O(log n)
- peek top: O(1)

**Embedded notes:**
- useful for schedulers/timeouts/event priorities
- fixed capacity keeps behavior predictable

---

## 7) Static Hash Map

**What it is:** Key-value map with fixed capacity and no resizing.

**Recommended approach:** Open addressing (linear/quadratic probing) with controlled load factor.

**Performance target:**
- average-case O(1) lookup/insert/delete
- worst-case degrades with collisions

**Embedded notes:**
- choose a simple, deterministic hash function
- document max load factor and failure behavior when full
- include tombstone handling if supporting delete

---

## Determinism + ISR-safety checklist

For each structure, define:
- exact memory size formula
- worst-case runtime per operation
- overflow/underflow/full behavior
- concurrency assumptions (single-thread, ISR+main, RTOS)
- whether operations are lock-free, atomic-protected, or external-lock required

If ISR is involved, keep operations short, avoid blocking, and minimize shared mutable state.

## Validation plan

- boundary tests: empty/full conditions
- wrap-around tests (ring buffer/queue)
- collision tests (hash map)
- stress tests at max capacity
- timing checks for worst-case paths

