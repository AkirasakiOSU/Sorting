//
// Created by dimab on 26.09.2024.
//

#ifndef SORT_H
#define SORT_H
#include <functional>
#include <vector>
#include <algorithm>
#include <cmath>


template<typename T>
class Sorting {
public:
    virtual std::vector<T> sort(std::vector<T> const &, std::function<bool(T const &,T const &)> const &) const = 0;
    virtual ~Sorting() = default;
};

template<typename T>
class CountingSorting final : public Sorting<T>  {
public:
    CountingSorting() = default;
    std::vector<T> sort(std::vector<T> const &, std::function<bool(T const &,T const &)> const &) const override;
    ~CountingSorting() override = default;
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
class InsertingSotring : public Sorting<T> {
public:
    InsertingSotring() = default;
    std::vector<T> sort(std::vector<T> const &, std::function<bool(T const &, T const &)> const &) const override;
    ~InsertingSotring() override = default;
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
class ShellSotring : public Sorting<T> {
public:
    ShellSotring() = default;
    std::vector<T> sort(std::vector<T> const &, std::function<bool(T const &, T const &)> const &) const override;
    ~ShellSotring() override = default;
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
class BubbleSotring : public Sorting<T> {
public:
    BubbleSotring() = default;
    std::vector<T> sort(std::vector<T> const &, std::function<bool(T const &, T const &)> const &) const override;
    ~BubbleSotring() override = default;
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
class QuickSotring : public Sorting<T> {
private:
    void qSort(typename std::vector<T>::iterator , typename std::vector<T>::iterator , std::function<bool(T const &, T const &)> const &) const;
public:
    QuickSotring() = default;
    std::vector<T> sort(std::vector<T> const &, std::function<bool(T const &, T const &)> const &) const override;
    ~QuickSotring() override = default;
};

template<typename T>
void QuickSotring<T>::qSort(typename std::vector<T>::iterator first, typename std::vector<T>::iterator last, std::function<bool(T const &, T const &)> const &comp) const {
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
    qSort(R.begin(), R.end() - 1, comp);
    return R;
}

template<typename T>
class SelectingSotring : public Sorting<T> {
public:
    SelectingSotring() = default;
    std::vector<T> sort(std::vector<T> const &, std::function<bool(T const &, T const &)> const &) const override;
    ~SelectingSotring() override = default;
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
#endif //SORT_H
