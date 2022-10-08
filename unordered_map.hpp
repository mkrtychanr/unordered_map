#include <vector>
#include <cstdio>
#include <iostream>
#ifndef UNORDERED_MAP_HPP
#define UNORDERED_MAP_HPP


template <typename K, typename V>
struct List {
    K first;
    V second;
    List(const std::pair<K, V>& _value, List<K, V>* _previous, List<K, V>* _next) : first(_value.first), second(_value.second), previous(_previous), next(_next) {}
    List<K, V>* previous {nullptr};
    List<K, V>* next {nullptr};
};

template<typename K, typename V>
class unordered_map {
private:
    std::vector<List<K, V>*> pointers {nullptr};
    List<K, V>* head {nullptr};
    List<K, V>* nodes {nullptr};
    double max_load_factor {0.25};
    size_t size {0};
public:
    typedef List<K, V>* iterator;
    unordered_map() {
        pointers.resize(1/max_load_factor);
    }

    void insert(const std::pair<K, V>& rhs) {
        if ( double(size + 1) / double(pointers.size()) > max_load_factor ) rehash(pointers.size() * 1/max_load_factor);
        size_t hash = std::hash<K>{}(rhs.first);
        size_t index = hash%pointers.size();
        if (head == nullptr) {
            head = new List<K, V>(rhs, nullptr, nullptr);
            nodes = head;
        } else {
            if (pointers[index] == nullptr) {
                nodes -> next = new List<K, V>(rhs, nodes, nullptr);
                nodes = nodes -> next;
            } else {
                auto ptr = pointers[index];
                while (ptr -> next != nullptr) {
                    if (hash == std::hash<K>{}(ptr -> next -> first)) {
                        ptr = ptr -> next;
                    } else {
                        break;
                    }
                }
                if (ptr -> next != nullptr) {
                    ptr -> next = new List<K, V>(rhs, ptr, nullptr);
                    nodes = ptr -> next;
                } else {
                    auto oldNext = ptr -> next;
                    ptr -> next = new List<K, V>(rhs, ptr, oldNext);
                    oldNext -> previous = ptr -> next;
                }
            }
        }
        pointers[index] = nodes;
        size++;
    }
    
    std::pair<K, V>* find(const K key) const {
        size_t hash = std::hash<K>{}(key);
        size_t index = hash%pointers.size();
        if (pointers[index] == nullptr) {
            return nullptr;
        } else {
            if (key == pointers[index] -> first) {
                return &pointers[index] -> value;
            }
        }
    }

    void rehash(size_t new_capacity) {
        std::vector<List<K, V>*> newPointers {nullptr};
        newPointers.resize(new_capacity);
        for (auto ptr = begin(); ptr != nullptr; ptr = ptr -> next) {
            newPointers[std::hash<K>{}(ptr -> first)%new_capacity] = ptr;
        }
        pointers = newPointers;
    }

    double load_factor() const {
        return size/pointers.size();
    }

    iterator begin() const { return head; }

    iterator end() const { return nullptr; }

    ~unordered_map() {
        List<K, V>* ptr = head;
        while (ptr != nullptr) {
            printf("%p\n", ptr);
            ptr = ptr -> next;
        }
        while (head != nullptr) {
            ptr = head;
            head = head -> next;
            delete(ptr);
        }
    }
};

#endif /* UNORDERED_MAP_HPP */