//
// Created by dimab on 26.09.2024.
//

#ifndef SORT_H
#define SORT_H
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <concepts>
#include <type_traits>
#include <algorithm>


template<typename T>
class Sorting {
public:
    virtual std::vector<T> sort(std::vector<T> const &, std::function<bool(T const &,T const &)> const &) const = 0;
    virtual ~Sorting() = default;
};

template<typename T>
class CountingSorting final : public Sorting<T>  {
public:
    std::vector<T> sort(std::vector<T> const &, std::function<bool(T const &,T const &)> const &) const override;
};

template<typename T>
std::vector<T> CountingSorting<T>::sort(std::vector<T> const &vec, std::function<bool(T const &,T const &)> const &comp) const{
    std::vector<T> res(vec.size(), 0);
    std::vector<int> count(vec.size(), 0);
    for(int i = vec.size() - 1; i >= 1; --i) {
        for(int j = i-1; j >= 0; --j) {
            if(comp(vec[i], vec[j])) ++count[j];
            else ++count[i];
        }
    }
    for(auto i = 0; i < vec.size(); i++) {
        res[count[i]] = vec[i];
    }
    return res;
}

template<typename T>
class InsertingSotring final : public Sorting<T> {
public:
    std::vector<T> sort(std::vector<T> const &, std::function<bool(T const &, T const &)> const &) const override;
};

template<typename T>
std::vector<T> InsertingSotring<T>::sort(std::vector<T> const &vec, std::function<bool(T const &, T const &)> const &comp) const {
    std::vector<T> res(vec);
    for(auto j = 1; j < res.size(); j++) {
        auto i = j-1;
        auto k = res[j];
        while(comp(k, res[i]) && i >= 0) {
            res[i+1] = res[i];
            i--;
        }
        res[i+1] = k;
    }
    //std::reverse(res.begin(), res.end());
    return res;
}

template<typename T>
class ShellSotring final : public Sorting<T> {
public:
    std::vector<T> sort(std::vector<T> const &, std::function<bool(T const &, T const &)> const &) const override;
};

template<typename T>
std::vector<T> ShellSotring<T>::sort(std::vector<T> const &vec, std::function<bool(T const &, T const &)> const &comp) const {
    auto R = vec;
    for(auto h = R.size()/2; h; h /=2) {
        int curH = h, j = curH;
        while(j < R.size()) {
            int i = j-curH;
            T k = R[j];
            while(i>=0 && comp(k, R[i])) {
                R[i+curH] = R[i];
                i -= curH;
            }
            R[i+curH] = k;
            ++j;
        }
    }
    return R;
}

template<typename T>
class BubbleSotring final : public Sorting<T> {
public:
    std::vector<T> sort(std::vector<T> const &, std::function<bool(T const &, T const &)> const &) const override;
};

template<typename T>
std::vector<T> BubbleSotring<T>::sort(std::vector<T> const &vec, std::function<bool(T const &, T const &)> const &comp) const {
    auto R = vec;
    for(auto i = 0; i < vec.size(); ++i) {
        for(auto j = 1; j < vec.size() - i; ++j) {
            if(comp(R[j], R[j-1])) std::swap(R[j], R[j-1]);
        }
    }
    return R;
}

template<typename T>
class QuickSotring final : public Sorting<T> {
private:
    void qSort(typename std::vector<T>::iterator &, typename std::vector<T>::iterator &, std::function<bool(T const &, T const &)> const &) const;
public:
    std::vector<T> sort(std::vector<T> const &, std::function<bool(T const &, T const &)> const &) const override;
};

template<typename T>
void QuickSotring<T>::qSort(typename std::vector<T>::iterator &first, typename std::vector<T>::iterator &last, std::function<bool(T const &, T const &)> const &comp) const {
    if (first >= last) return;
    T pivo = *(first + std::distance(first, last) / 2);
    auto iLeft = first;
    auto iRight = last;
    while (iLeft <= iRight) {
        while (comp(*iLeft, pivo)) {
            ++iLeft;
        }
        while (comp(pivo, *iRight)) {
            --iRight;
        }
        if (iLeft <= iRight) {
            std::iter_swap(iLeft, iRight);
            ++iLeft;
            --iRight;
        }
    }
    if (first < iRight) qSort(first, iRight, comp);
    if (iLeft < last) qSort(iLeft, last, comp);
}

template<typename T>
std::vector<T> QuickSotring<T>::sort(std::vector<T> const &vec, std::function<bool(T const &, T const &)> const &comp) const {
    std::vector<T> R = vec;
    auto b = R.begin(), e = R.end() - 1;
    qSort(b, e, comp);
    return R;
}

template<typename T>
class SelectingSotring final : public Sorting<T>{
public:
    SelectingSotring() = default;
    std::vector<T> sort(std::vector<T> const &, std::function<bool(T const &, T const &)> const &) const override;
};

template<typename T>
std::vector<T> SelectingSotring<T>::sort(std::vector<T> const &vec, std::function<bool(T const &, T const &)> const &comp) const {
    auto R = vec;
    typename std::vector<T>::iterator iMax = R.begin(), iLast = (R.end() - 1), iCur = R.begin() + 1;
    for(auto i = 0; i < R.size(); ++i) {
        while(iCur <= (iLast - i)) {
            if(!comp(*iCur, *iMax)) iMax = iCur;
            ++iCur;
        }
        std::iter_swap(iMax, iCur - 1);
        iMax = R.begin();
        iCur = iMax + 1;
    }
    return R;
}

template <typename T>
class HeapSorting final : public Sorting<T> {
private:

    void heapify(typename std::vector<T>::iterator, typename std::vector<T>::iterator,
             typename std::vector<T>::iterator, std::function<bool(const T &, const T &)> const &) const;

public:
    HeapSorting() = default;
    std::vector<T> sort(std::vector<T> const &, std::function<bool(T const &, T const &)> const &) const override;

};

template<typename T>
void HeapSorting<T>::heapify(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end,
             typename std::vector<T>::iterator root, std::function<bool(const T &, const T &)> const &comparator) const {
    auto size = std::distance(begin, end);
    auto rootIndex = std::distance(begin, root);
    T k = *root;
    auto j = rootIndex;
    while (2 * j + 1 < size) {
        auto i = 2 * j + 1;
        auto childIt = begin + i;
        if (i + 1 < size && comparator(*(childIt), *(childIt + 1))) {
            ++i;
            ++childIt;
        }
        if (comparator(*childIt, k)) {
            break;
        }
        *(begin + j) = *childIt;
        j = i;
    }
    *(begin + j) = k;
}

template<typename T>
std::vector<T> HeapSorting<T>::sort(std::vector<T> const &v, std::function<bool(T const &, T const &)> const &comp) const{
    auto vec = v;
    auto begin = vec.begin();
    auto end = vec.end();
    for (auto it = begin + (vec.size() / 2) - 1; it >= begin; --it) {
        heapify(begin, end, it, comp);
    }
    for (auto it = end - 1; it > begin; --it) {
        std::swap(*begin, *it);
        heapify(begin, it, begin, comp);
    }
    return vec;
}

template <typename T>
concept Integral = std::is_integral_v<T>;

template <Integral T>
class RadixSorting final : public Sorting<T>
{
    CountingSorting<T> count;
public:
    RadixSorting() = default;
    std::vector<T> sort(std::vector<T> const &, std::function<bool(T const &, T const &)> const &) const override;

};

template <Integral T>
std::vector<T> RadixSorting<T>::sort(std::vector<T> const &vec, std::function<bool(T const &, T const &)> const &comp) const
{
    if (vec.empty()) {
        return vec;
    }
    T maxElement = *std::max_element(vec.begin(), vec.end(), comp);
    int maxDigits = static_cast<int>(std::log10(maxElement)) + 1;
    std::vector<T> result = vec;
    for (int exp = 1; maxDigits > 0; exp *= 10, --maxDigits) {
        result = count.sort(result, [&exp](T const &a, T const &b) {
            return (a / exp) % 10 < (b / exp) % 10;
        });
    }
    return result;
}


#endif //SORT_H
