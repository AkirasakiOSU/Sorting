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
    int t = static_cast<int>(std::log2(R.size()));
    std::vector<int> h(t, 0);
    h[t-1] = R.size()/2;
    for(auto i = t-2; i >= 0; i--) {
        h[i] = h[i+1]/2;
    }
    for(int s = t-1; s >= 0; s--) {
        int curH = h[s],
        j = curH;
        while(j < R.size()) {
            int i = j-curH;
            T k = R[j];
            while(i>=0) {
                if(comp(k, R[i])) break;
                R[i+curH] = R[i];
                i -= curH;
            }
            R[i+curH] = k;
            ++j;
        }
    }
    return R;
}
#endif //SORT_H
