#pragma once

namespace rtb {
template <typename T>
class LinkedList {
    struct Node {
        T     data_;
        Node* next_;

        explicit Node(T value) 
            : data_(value), 
              next_(nullptr)
        {}
    };

    Node*  head_;
    Node*  tail_;
    size_t size_;

public:
    LinkedList()
        : head_(nullptr),
          tail_(nullptr),
          size_(0)
    {}

    ~LinkedList(){
        clear();
    }

    LinkedList(const LinkedList& other) 
        : head_(nullptr),
          tail_(nullptr), 
          size_(0)
    {
        Node* current = other.head_;

        while (current != nullptr) {
            push_back(current->data_);
            current = current->next_;
        }
    }

    LinkedList(LinkedList&& other) noexcept {
        head_ = other.head_;
        tail_ = other.tail_;
        size_ = other.size_;

        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
    }

    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear();

            Node* current = other.head_;

            while (current != nullptr) {
                push_back(current->data_);
                current = current->next_;
            }
        }
        return *this;
    }

    LinkedList& operator=(LinkedList&& other) noexcept {
        if (this != &other) {
            clear();

            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;

            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    bool empty() const {
        return head_ == nullptr;
    }

    size_t size() const {
        return size_;
    }

    T& front() {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        return head_->data_;
    }

    const T& front() const {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        return head_->data_;
    }

    T& back() {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        return tail_->data_;
    }

    const T& back() const {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        return tail_->data_;
    }

    void push_back(const T& value) {
        Node* newNode = new Node(value);

        if (head_ == nullptr) {
            head_ = newNode;
            tail_ = newNode;
        } else {
            tail_->next_ = newNode;
        }

        ++size_;
    }

    void push_front(const T& value) {
        Node* newNode = new Node(value);

        if (head_ == nullptr) {
            head_ = newNode;
            tail_ = newNode;
        } else {
            newNode->next_ = head_;
            head_ = newNode;
        }

        ++size_;
    }

    void pop_front() {
        if (head_ == nullptr) {
            return;
        }

        Node* deleted_node = current;
        current = current->next_;
        delete deleted_node;
        
    }

    void pop_back() {
        if (tail_ == nullptr) {
            return;
        }

    }

    void insert(size_t pos, const T& value) {

        if (pos == 0) {
            push_front(value);
            return;
        }

        if (pos > size_) {
            return;
        }

        if (pos == size_) {
            push_back(value);
            return;
        }

        Node* prev_node = head_; 
        Node* cur_node = head_->next_; 
        Node* newNode = new Node(value);
        size_t i = 0;

        while (i < pos - 1) {
            prev_node = cur_node;
            cur_node = cur_node->next_;
            ++i;
        }

        prev_node->next_ = newNode;
        newNode->next_ = cur_node;
        ++size_;

    }
    
    // void erase(size_t pos) {
        
    // }

    void clear() noexcept {
        Node* current = head_;
        while (current != nullptr) {
            Node* deleted_node = current;
            current = current->next_;
            delete deleted_node;
        }

        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
    }


};
}

// void reverse();

// bool contains(const T& value) const;
// int find(const T& value) const;     // вернуть индекс или -1

// void print() const;                 // для тестов