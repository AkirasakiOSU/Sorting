//
// Created by dimab on 26.09.2024.
//

#ifndef SORT_H
#define SORT_H
#include <functional>
#include <vector>


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


#endif //SORT_H
