#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using TCont = std::vector<int>;

bool isInclude(const TCont& arr, const TCont& subArr)
{
    if (subArr.empty())
        return true;

    // ищем начало подмассива в массиве arr - сложность log(N)
    auto it = std::lower_bound(arr.cbegin(), arr.cend(), subArr.front());
    if (it == arr.cend() || *it > subArr.front())
        return false;

    // начало нашли, идем до первого несовпадения - сложность O(K)
    auto first = *it;
    auto innerIt = subArr.cbegin();
    while (*it == *innerIt)
    {
        if (++innerIt == subArr.cend())
            return true;

        if (++it == arr.cend())
            return false;
    }

    // первое несовпадение может быть из-за того, что в исходном массиве 
    // повторется число, оказавыщееся началом подмассива, тогда всё ок, нужно их все пропустить
    // сдвинув, таким образом, начала подмассива
    if (*it != first)
        return false;

    // конец повторяющихся чисел - сложность log(N)
    it = std::upper_bound(it, arr.cend(), first);
    if (it == arr.cend())
        return false;

    // сравниваем уже до конца - сложность O(K)
    while (*it == *innerIt)
    {
        if (++innerIt == subArr.cend())
            return true;

        if (++it == arr.cend())
            return false;
    }

    // итого, сложность O(logN + K), N - размер исходного массива, K - размер искомого подмассива

    return false;
}


int main()
{
    assert( isInclude({ 1, 2, 3, 5, 7, 9, 11 }, {}) );
    assert( isInclude({ 1, 2, 3, 5, 7, 9, 11 }, { 3, 5, 7 }) );
    assert( !isInclude({ 1, 2, 3, 5, 7, 9, 11 }, { 4, 5, 7 }) );

    assert( isInclude({ 1, 2, 3, 4, 5, 6 }, { 1 }) );
    assert( isInclude({ 1, 2, 3, 4, 5, 6 }, { 6 }) );
    assert( isInclude({ 1, 2, 3, 4, 5, 6 }, { 4 }) );
    assert( isInclude({ 1, 2, 3 }, { 1, 2, 3 }) );
    assert( isInclude({ 1, 2, 3, 4, 5, 6}, {3, 4, 5}) );
    assert( isInclude({ 1, 2, 3, 4, 5, 6 }, { 1, 2, 3 }) );
    assert( isInclude({ 1, 2, 3, 4, 5, 6 }, { 3, 4, 5, 6 }) );
    assert( isInclude({ 1, 2, 3, 3, 3, 3, 4, 5, 6 }, { 3, 3, 3, 4, 5, 6 }) );
    assert( isInclude({ 1, 2, 3, 3, 3, 3, 4, 5, 6 }, { 3, 3, 3, 3, 4, 5 }) );
    assert( isInclude({ 1, 1, 1, 2, 2, 2, 2, 2 }, { 1, 2, 2, 2 }) );
    assert( isInclude({ 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 4, 5, 6 }, { 1, 2, 2, 2, 2, 2 }) );
    assert( isInclude({ 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 4, 5, 6 }, { 1, 1, 2, 2, 2, 2, 2, 3, 3 }) );
    assert( isInclude({ 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 4, 5, 6 }, { 4, 5, 6 }));
    assert( isInclude({ 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 10 }, { 2, 10 }) );
    assert( !isInclude({}, { 4, 5, 6 }) );
    assert( !isInclude({ 1 }, { 4, 5, 6 }) );
    assert( !isInclude({ 7, 8, 9 }, { 8, 9, 10 }) );
    assert( !isInclude({ 7, 8, 9, 10 }, { 8, 10 }) );

    std::cout << "Success!" << std::endl;
}