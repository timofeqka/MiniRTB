#pragma once
#include "vector.hpp" 
#include <type_traits>
#include <functional>
#include <cstddef>
#include <utility> 
#include <stdexcept>

namespace rtb {

template
    <
        typename T1, 
        typename T2
    >
using pair = std::pair<T1, T2>;


inline  size_t Hash(int key, size_t count_) {
    return key % count_; 
}

template
    <
        typename ElemType, 
        typename Key, 
        typename Hash = std::hash<Key>
    >
class HashTable {

    static constexpr size_t DEFAULT_BUCKET_COUNT = 16;
    static constexpr size_t BUCKET_GROWTH_FACTOR = 2; 

private:
    struct Node {
        const Key key_{};
        ElemType  data_{};
        Node*     next_{};

        template <typename... Args>
        Node(const Key& key, Args&&... args)
            : key_(key)
            , data_(std::forward<Args>(args)...)
            , next_(nullptr)
        {}
    };

    Vector<Node*> buckets_;
    size_t        count_;
    Hash          hasher_;

    float max_load_factor_ = 1.0f;

    size_t bucket_index(const Key& key) const {
        return hasher_(key) % buckets_.size();
    }

    template <typename Table>
    static decltype(auto) at_impl(Table& table, const Key& key) {
        auto* node = find_node(table, key);

        if (node == nullptr) {
            throw std::out_of_range("HashTable::at: key not found");
        }

        return (node->data_);
    }

    template <typename Table>
    static auto* find_impl(Table& table, const Key& key) {
        auto* node = find_node(table, key);

        return node ? &node->data_ : nullptr;
    }

    // read-only lookup
    template <typename Table> 
    static auto find_node(Table& table, const Key& key) {
        size_t index = table.bucket_index(key);
        auto current = table.buckets_[index];

        while (current != nullptr) {
            if (current->key_ == key) {
                return current;
            }
            current = current->next_;
        }
        return current;
    }

    // mutating lookup
    Node** find_slot(const Key& key) {
        size_t index = bucket_index(key);
        Node** slot = &buckets_[index];

        while (*slot != nullptr) {
            if ((*slot)->key_ == key) {
                return slot;
            }

            slot = &((*slot)->next_);
        }

        return slot;
    }

public:
    HashTable() 
        : buckets_(DEFAULT_BUCKET_COUNT)
        , count_ {0} 
        , hasher_ {}
    {}

    explicit HashTable(size_t bucket_count) 
        : buckets_(bucket_count == 0 ? DEFAULT_BUCKET_COUNT : bucket_count)
        , count_ {0}
        , hasher_ {}
    {}

    HashTable(const HashTable& other) 
        : buckets_(other.buckets_.size())
        , count_(0)
        , hasher_(other.hasher_)
        , max_load_factor_(other.max_load_factor_)
    {
        for (size_t i = 0; i < other.buckets_.size(); ++i) {
            const Node* current = other.buckets_[i];

            while (current != nullptr) {
                insert(current->key_, current->data_);
                current = current->next_;
            }
        }
    }       

    HashTable& operator=(const HashTable& other) {
        if (this != &other) {
            HashTable temp(other);
            swap(temp);
        }
        return *this;
    }

    HashTable(HashTable&& other) noexcept 
        : buckets_(std::move(other.buckets_))
        , count_(other.count_)
        , hasher_(std::move(other.hasher_))
        , max_load_factor_(other.max_load_factor_)
    {
        other.count_ = 0;
    }

    HashTable& operator=(HashTable&& other) noexcept {
        if (this != &other) {
            clear();

            buckets_ = std::move(other.buckets_);
            count_ = other.count_;
            hasher_ = std::move(other.hasher_);
            max_load_factor_ = other.max_load_factor_;

            other.count_ = 0;
        }
        return *this;
    }

    ~HashTable() {
        clear();
    }

    size_t size() const noexcept {
        return count_;
    }

    bool empty() const noexcept {
        return count_ == 0;
    }

    float load_factor() const noexcept {
        return static_cast<float>(count_) /
               static_cast<float>(buckets_.size());
    }

    float max_load_factor() const noexcept {
        return max_load_factor_;
    }

    bool contains(const Key& key) const {
        return find_node(*this, key) != nullptr;
    }

    ElemType& at(const Key& key) {
        return at_impl(*this, key);
    }

    const ElemType& at(const Key& key) const {
        return at_impl(*this, key);
    }

    ElemType* find(const Key& key) {
        return find_impl(*this, key);
    }

    const ElemType* find(const Key& key) const {
        return find_impl(*this, key);
    }

    template <typename... Args>
    void emplace(const Key& key, Args&&... args) {
        Node** slot = find_slot(key);

        if (*slot != nullptr) {
            return;
        }

        if ((count_ + 1) > max_load_factor_ * buckets_.size()) {
            rehash(buckets_.size() * BUCKET_GROWTH_FACTOR);
            slot = find_slot(key);
        }

        *slot = new Node(key, std::forward<Args>(args)...);

        ++count_;
    }

    void insert(const Key& key, const ElemType& data) {
        emplace(key, data);
    }

    void insert(const Key& key, ElemType&& data) {
        emplace(key, std::move(data));
    }

    void insert_or_assign(const Key& key, const ElemType& data) {
        Node** slot = find_slot(key);

        if (*slot != nullptr) {
            (*slot)->data_ = data;
            return;
        }

        if ((count_ + 1) > max_load_factor_ * buckets_.size()) {
            rehash(buckets_.size() * BUCKET_GROWTH_FACTOR);
            slot = find_slot(key);
        }

        *slot = new Node(key, data);

        ++count_;
    }

    void insert_or_assign(const Key& key, ElemType&& data) {
        Node** slot = find_slot(key);

        if (*slot != nullptr) {
            (*slot)->data_ = std::move(data);
            return;
        }

        if ((count_ + 1) > max_load_factor_ * buckets_.size()) {
            rehash(buckets_.size() * BUCKET_GROWTH_FACTOR);
            slot = find_slot(key);
        }

        *slot = new Node(key, std::move(data));

        ++count_;
    }

    void erase(const Key& key) {
        Node** slot = find_slot(key);

        if (*slot == nullptr) {
            return;
        }

        Node* deleted = *slot;
        *slot = deleted->next_;

        delete deleted;
        --count_;
    }

    void clear() noexcept {
        for (size_t i = 0; i < buckets_.size(); ++i) {
            Node* current = buckets_[i];

                while (current != nullptr) {
                    Node* deleted_node = current;
                    current = current->next_;
                    delete deleted_node;
                }

            buckets_[i] = nullptr;
        }
        count_ = 0;
    }

    void set_max_load_factor(float value) {
        if (value <= 0.0f) {
            throw std::invalid_argument("max_load_factor must be positive");
        }

        max_load_factor_ = value;

        if (load_factor() > max_load_factor_) {
            rehash(buckets_.size() * BUCKET_GROWTH_FACTOR);
        }
    }

    void reserve(size_t expected_capacity) {
        buckets_.reserve(expected_capacity);
    }

    void resize(size_t new_bucket_count) {
        if (bucket_count() > new_bucket_count) return;
        rehash(new_bucket_count);
    }

    void rehash(size_t new_bucket_count) {

        if (new_bucket_count < 1) {
            new_bucket_count = 1;
        }
        if (new_bucket_count == buckets_.size()) return; 

        Vector<Node*> new_buckets(new_bucket_count);

        for (size_t i = 0; i < buckets_.size(); ++i) {
            Node* current = buckets_[i];

            while (current != nullptr) {
                Node* next = current->next_;

                size_t new_index = hasher_(current->key_) % new_bucket_count;

                current->next_ = new_buckets[new_index];
                new_buckets[new_index] = current;

                current = next;
            }
        }

        buckets_.swap(new_buckets);
    }

    void swap(HashTable& other) noexcept {
        buckets_.swap(other.buckets_);
        std::swap(count_, other.count_);
        std::swap(hasher_, other.hasher_);
        std::swap(max_load_factor_, other.max_load_factor_);
    }
};
}