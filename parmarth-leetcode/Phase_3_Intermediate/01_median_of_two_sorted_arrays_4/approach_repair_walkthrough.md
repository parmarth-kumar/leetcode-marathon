# Apne Approach Ko Kaise Repair Karein

## Seedha Verdict

Current code ko sirf `while` condition, index, ya decrement fix karke correct banana practical nahi hai. Root issue yeh hai ki hum dono arrays ke ends se elements physically hata rahe hain, lekin median nikalne ke liye humein sorted order ka **middle** chahiye. Beech mein kaunse elements hain, unhe reliably track karne ke liye ek simpler invariant chahiye.

Tumhare original idea ka useful hissa yeh tha: **middle tak pahunchne ke liye poore data ko process karna zaroori nahi**. Is idea ko safe tareeke se implement karne ke liye vectors ko erase/pop karne ke bajay do indices se next smallest value select karenge. Yeh correct baseline hai; binary-search partition wala faster version `solution_analysis.md` mein hai.

## Corrected Soch: Do Sorted Lists Ko Saath-saath Read Karo

Dono arrays sorted hain. Isliye unke current unprocessed elements mein jo chhota hai, wahi combined sorted order ka agla element hoga.

```text
nums1: 1, 3, 8
       ^
nums2: 2, 4, 6, 9
       ^

Current values 1 aur 2 hain; agla combined value 1 hai.
nums1 ka index aage badhao, vector ko modify mat karo.
```

Median ke index:

```text
leftMiddle  = (total - 1) / 2
rightMiddle = total / 2
```

- Odd total mein dono indices same hote hain.
- Even total mein dono indices adjacent middle positions hote hain.
- `rightMiddle` tak values nikalne ke baad loop rok sakte hain; baaki values ki zaroorat nahi.

## Complete C++17 Code

```cpp
#include <vector>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n = static_cast<int>(nums1.size());
        int m = static_cast<int>(nums2.size());
        int total = n + m;

        // LeetCode constraint ke mutabik total elements kam-se-kam 1 hai.
        int leftMiddle = (total - 1) / 2;
        int rightMiddle = total / 2;

        int i = 0;
        int j = 0;
        int previous = 0;
        int current = 0;

        for (int position = 0; position <= rightMiddle; ++position) {
            previous = current;

            // Dono arrays ke unprocessed front elements mein se chhota chuno.
            if (i < n && (j >= m || nums1[i] <= nums2[j])) {
                current = nums1[i];
                ++i;
            } else {
                current = nums2[j];
                ++j;
            }
        }

        if (leftMiddle == rightMiddle) {
            return current;
        }

        return (static_cast<long long>(previous) + current) / 2.0;
    }
};
```

### `if` Condition Kya Guarantee Karti Hai?

```cpp
i < n && (j >= m || nums1[i] <= nums2[j])
```

- `i < n`: pehle check karo ki `nums1[i]` valid hai.
- `j >= m`: agar `nums2` khatam ho gayi, toh `nums1` se lo.
- `nums1[i] <= nums2[j]`: dono mein values available hon, toh chhoti value lo.
- Agar condition false ho, toh `nums2[j]` available aur sahi next value hai.

Is order se empty input array safe hoti hai: jis array mein elements nahi hain uska index access nahi hota. Problem constraint ke mutabik **dono arrays ek saath empty nahi** hain.

### Even Median Mein `long long` Aur `2.0` Kyun?

`previous + current` do `int` values ka sum hai. `long long` mein cast karke sum overflow ke risk ko avoid karta hai. `/ 2.0` floating-point division deta hai, isliye `2` aur `3` ka median `2.5` aata hai, `2` nahi.

## Dry Run: Odd Total

```text
nums1 = [1, 3, 8]
nums2 = [2, 4, 6, 9]
total = 7
leftMiddle = rightMiddle = 3
```

Loop `position = 0` se `3` tak chalega, yaani chaar smallest values process hongi:

| Position | `nums1[i]` | `nums2[j]` | Chuni hui value | Update                            |
| -------: | ---------: | ---------: | --------------: | --------------------------------- |
|        0 |          1 |          2 |               1 | `i` aage: `nums1` ka agla value 3 |
|        1 |          3 |          2 |               2 | `j` aage: `nums2` ka agla value 4 |
|        2 |          3 |          4 |               3 | `i` aage: `nums1` ka agla value 8 |
|        3 |          8 |          4 |               4 | `j` aage                          |

`leftMiddle == rightMiddle`, toh odd-length case ka median `current = 4` hai. Iske baad loop aage nahi chalta.

## Dry Run: Even Total

```text
nums1 = [1, 2]
nums2 = [3, 4]
total = 4
leftMiddle = 1, rightMiddle = 2
```

Loop positions `0`, `1`, `2` tak chalta hai:

| Position | Chuni hui value | `previous` | `current` |
| -------: | --------------: | ---------: | --------: |
|        0 |               1 |          0 |         1 |
|        1 |               2 |          1 |         2 |
|        2 |               3 |          2 |         3 |

Even case mein final `previous = 2`, `current = 3`, isliye median `(2 + 3) / 2.0 = 2.5`.

## Harness Ke Saath Comparison

Neeche ke expected values tumhare current `test_harness.cpp` ke wahi 8 test inputs se hain. Purana implementation pehle test par runtime vector-bounds assertion fail karta hai, isliye baaki assertions tak nahi pahunchta. Corrected two-pointer code ko same inputs ke saath alag se run karna chahiye.

| Test | Input summary                | Expected median | Corrected code |
| ---: | ---------------------------- | --------------: | -------------- |
|    1 | `[1, 3]`, `[2]`              |           `2.0` | Pass           |
|    2 | `[1, 2]`, `[3, 4]`           |           `2.5` | Pass           |
|    3 | `[]`, `[1]`                  |           `1.0` | Pass           |
|    4 | `[1]`, `[2]`                 |           `1.5` | Pass           |
|    5 | `[1, 2]`, `[3, 4, 5, 6]`     |           `3.5` | Pass           |
|    6 | `[2, 3, 5]`, `[]`            |           `3.0` | Pass           |
|    7 | `[-5, -3, -1]`, `[-2, 0, 4]` |          `-1.5` | Pass           |
|    8 | `[1, 1, 1]`, `[1, 1, 1]`     |           `1.0` | Pass           |

Validation ke liye corrected method ko harness ke same inputs ke against C++17 mein compile/run kiya gaya: **8/8 cases pass**. Harness file ko student attempt ke roop mein unchanged rakha gaya hai.

## Original Code Se Kya Badla?

- `erase(begin())` aur `pop_back()` hata diye: inputs unchanged rehte hain.
- `nums1[-1]` hata diya: ab sirf bounds-checked conditions ke baad valid indices read hote hain.
- `n` / `m` ko manually mutate nahi karte: `i` / `j` input arrays ke current positions batate hain.
- Complex `while` condition hata kar clear stopping rule rakha: `rightMiddle` process hote hi stop.
- Odd aur even cases ko middle indices ke zariye handle kiya.
- Integer division fix ki aur sum ko `long long` mein kiya.

## Complexity Aur Agla Optimization

Yeh corrected baseline `rightMiddle + 1` values tak chalta hai. Worst case mein yeh **O(n + m) time** aur **O(1) auxiliary space** hai. Poora merged array build nahi hota.

Isse optimize karne ke liye agla observation yeh hai ki humein values ko ek-ek karke nikalna bhi zaroori nahi; bas dono arrays ka sahi middle partition chahiye. Chhoti array par binary search karke time **O(log(min(n, m)))** tak laa sakte hain. Us partition approach ka complete code aur dry runs `solution_analysis.md` mein hain.
