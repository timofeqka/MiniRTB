namespace rtb {

template <typename Iterator, typename T>
Iterator find(Iterator first, Iterator last, const T& value) {
    for (auto it = first; it != last; ++it) {
        if (*it == value) { return it; }
    }
    return last;
}

template <typename Iterator, typename Predicate>
Iterator find_if(Iterator first, Iterator last, Predicate pred) {
    for (auto it = first; it != last; ++it) {
        if (pred(*it)) { return it; }
    }
    return last;
}



template <typename Iterator, typename T>
size_t count(Iterator first, Iterator last, const T& value) {
    size_t count = 0;
    for (auto it = first; it != last; ++it) {
        if (*it == value) { ++count; }
    }
    return count;
}

template <typename Iterator, typename Predicate>
size_t count_if(Iterator first, Iterator last, Predicate pred) {
    size_t count = 0;
    for (auto it = first; it != last; ++it) {
        if (pred(*it)) { ++count; }
    }
    return count;
}




template <typename Iterator, typename T>
void fill(Iterator first, Iterator last, const T& value) {
    for (auto it = first; it != last; ++it) {
        *it = value;
    }
}

template <typename Iterator, typename Generator>
void generate(Iterator first, Iterator last, Generator gen) {
    for (auto it = first; it != last; ++it) {
        *it = gen();
    }
}

template <typename Iterator, typename T>
void replace(Iterator first, Iterator last, const T& oldValue ,const T& newValue) {
    for (auto it = first; it != last; ++it) {
        if (*it == oldValue) {
            *it = newValue;
        }
    }
}

template <typename Iterator, typename Predicate, typename T>
void replace_if(Iterator first, Iterator last, Predicate pred, const T& newValue) {
    for (auto it = first; it != last; ++it) {
        if (pred(*it)) { *it = newValue; }
    }
}

template <typename Iterator>
Iterator min_element(Iterator first, Iterator last) {
    if (first == last) { return last; }

    auto min = first;
    for (auto it = first; it != last; ++it) {
        if (*it < *min) { min = it; }
    }
    return min;
}

template <typename Iterator>
Iterator max_element(Iterator first, Iterator last) {
    if (first == last) { return last; }

    auto max = first;
    for (auto it = first; it != last; ++it) {
        if (*it > *max) { max = it; }
    }
    return max;
}



}