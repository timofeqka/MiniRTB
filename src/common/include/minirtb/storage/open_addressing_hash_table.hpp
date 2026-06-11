#pragma once
#include "vector.hpp"
#include <functional>
#include <utility>
#include <stdexcept>

namespace rtb
{
template
<
    typename ElemType, 
    typename Key, 
    typename Hash = std::hash<Key>
>
class FlatHashTable {
    static constexpr size_t DEFAULT_BUCKET_COUNT = 16;
    static constexpr size_t BUCKET_GROWTH_FACTOR = 2;
private:
    enum class State {
        Empty,
        Occupied,
        Deleted
    };

    struct Bucket 
    {
        State    state_ = State::Empty;
        Key      key_;
        ElemType data_; //std::optional<std::pair<Key, ElemType>>
    };
    
    Vector<Bucket> buckets_;
    size_t         count_;
    Hash           hasher_;

    float max_load_factor_ = 0.7f;

    size_t bucket_index(const Key& key) const {
        return hasher_(key) % buckets_.size();
    }

public:
    FlatHashTable() 
        : buckets_(DEFAULT_BUCKET_COUNT)
        , count_ {0}
        , hasher_ {}
    {}

    explicit FlatHashTable(size_t bucket_count) 
        : buckets_(bucket_count == 0 ? DEFAULT_BUCKET_COUNT : bucket_count)
        , count_ {0}
        , hasher_ {}
    {}

    FlatHashTable(const FlatHashTable& other)
        : buckets_(other.buckets_.size())
        , count_(0)
        , hasher_(other.hasher_)
        , max_load_factor_(other.max_load_factor_)
    {
        for (size_t i = 0; i < other.buckets_.size(); ++i) {
            const Bucket& bucket = other.buckets_[i];

            if (bucket.state_ == State::Occupied) {
                insert(bucket.key_, bucket.data_);
            }
        }
    }

    FlatHashTable(FlatHashTable&& other) noexcept 
        : buckets_(std::move(other.buckets_))
        , count_(other.count_)
        , hasher_(std::move(other.hasher_))
        , max_load_factor_(other.max_load_factor_)
    {
        other.count_ = 0;
    }

    FlatHashTable& operator=(const FlatHashTable& other) {
        if (this != &other) {
            FlatHashTable temp(other);
            swap(temp);
        }
        return *this;
    }

    FlatHashTable& operator=(FlatHashTable&& other) noexcept {
        if (this != &other) {
            buckets_ = std::move(other.buckets_);
            count_ = other.count_;
            hasher_ = std::move(other.hasher_);
            max_load_factor_ = other.max_load_factor_;

            other.count_ = 0;
        }
        return *this;
    }

    ~FlatHashTable() = default;

    size_t size() const {
        return count_;
    }

    bool empty() const {
        return count_ == 0;
    }

    size_t bucket_count() const {
       return buckets_.size();
    }

    float load_factor() const noexcept {
        return static_cast<float>(count_) /
               static_cast<float>(buckets_.size());
    }

    float max_load_factor() const noexcept {
        return max_load_factor_;
    }

    void set_max_load_factor(float value) {
        if (value <= 0.0f || value > 1.0f) {
            throw std::invalid_argument("max_load_factor must be > 0.0 and <= 1.0");
        }

        max_load_factor_ = value;

        if (load_factor() > max_load_factor_) {
            rehash(buckets_.size() * BUCKET_GROWTH_FACTOR);
        }
    }

    void insert(const Key& key, const ElemType& data) {
        if ((count_ + 1) > max_load_factor_ * buckets_.size()) {
            rehash(buckets_.size() * BUCKET_GROWTH_FACTOR);
        }

        size_t start  = bucket_index(key);

        for (size_t offset = 0; offset < buckets_.size(); ++offset) {
            size_t index = (start + offset) % buckets_.size();

            if (buckets_[index].state_ == State::Occupied) {
                if (buckets_[index].key_ == key) {
                    return;
                }
                continue;
            }
            
            buckets_[index].key_   = key;
            buckets_[index].data_  = data;
            buckets_[index].state_ = State::Occupied;
            ++count_;
            return;
        }
    }

    bool erase(const Key& key) {
        size_t start = bucket_index(key);

        for (size_t offset = 0; offset < buckets_.size(); ++offset) {
            size_t index = (start + offset) % buckets_.size();

            if (buckets_[index].state_ == State::Empty) {
                return false;
            }

            if (buckets_[index].state_ == State::Occupied) {
                if (buckets_[index].key_ == key) {
                    buckets_[index].state_ = State::Deleted;
                    --count_;
                    return true;
                }
            }
        }
        return false;
    }

    ElemType* find(const Key& key) {
        size_t start = bucket_index(key);
        
        for (size_t offset = 0; offset < buckets_.size(); ++offset) {
            size_t index = (start + offset) % buckets_.size();

            if (buckets_[index].state_ == State::Empty) {
                return nullptr;
            }

            if (buckets_[index].state_ == State::Occupied) {
                if (buckets_[index].key_ == key) {
                    return &buckets_[index].data_;
                }
            }
        }
        return nullptr;
    }

    const ElemType* find(const Key& key) const {
        size_t start = bucket_index(key);
        
        for (size_t offset = 0; offset < buckets_.size(); ++offset) {
            size_t index = (start + offset) % buckets_.size();

            if (buckets_[index].state_ == State::Empty) {
                return nullptr;
            }

            if (buckets_[index].state_ == State::Occupied) {
                if (buckets_[index].key_ == key) {
                    return &buckets_[index].data_;
                }
            }
        }
        return nullptr;
    }

    bool contains(const Key& key) const {
        return find(key) != nullptr;
    }

    void rehash(size_t new_buckets_count) {
        if (new_buckets_count < 1) {
            new_buckets_count = 1;
        }
        if (new_buckets_count == buckets_.size()) return;

        Vector<Bucket> new_buckets(new_buckets_count);

        for (size_t i = 0; i < buckets_.size(); ++i) {
            Bucket& old_bucket = buckets_[i];

            if (old_bucket.state_ == State::Occupied) {
                size_t new_index = hasher_(old_bucket.key_) % new_buckets_count;
            
                for (size_t offset = 0; offset < new_buckets_count; ++offset) {
                    size_t index = (new_index + offset) % new_buckets_count;
                    if (new_buckets[index].state_ == State::Occupied) {
                        continue;
                    }
                    new_buckets[index] = std::move(old_bucket);
                    break;
                }
            }
        }
        buckets_.swap(new_buckets);
    }

    void reserve(size_t expected_capacity) {
        buckets_.reserve(expected_capacity);
    }

    void resize(size_t new_bucket_count) {
        if (bucket_count() > new_bucket_count) return;
        rehash(new_bucket_count);
    }

    void swap(FlatHashTable& other) noexcept {
        buckets_.swap(other.buckets_);
        std::swap(count_, other.count_);
        std::swap(hasher_, other.hasher_);
        std::swap(max_load_factor_, other.max_load_factor_);
    }

    void clear() noexcept {
        for (size_t i = 0; i < buckets_.size(); ++i) {
            buckets_[i].state_ = State::Empty;
        }
        count_ = 0; 
    }

    
};

} // namespace rtb

