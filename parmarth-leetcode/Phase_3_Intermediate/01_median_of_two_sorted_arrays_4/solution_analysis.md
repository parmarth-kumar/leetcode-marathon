# Solution Analysis — Median of Two Sorted Arrays

## Verdict

Current implementation **correct nahi hai**. Harness compile hota hai, lekin run karte waqt pehle test par hi vector bounds assertion fail hoti hai. Iska matlab function invalid index se vector element access kar raha hai. Sanitizer run karne ki koshish bhi ki gayi thi, lekin installed MinGW toolchain mein AddressSanitizer/UBSan libraries available nahi the; normal runtime check ne failure confirm kar diya.

## Current Attempt Mein Problems

### 1. `while` condition hamesha true hai

```cpp
while ((n > 0 || m > 0) || ((n + m) != 1 || (n + m) != 2))
```

`(n + m) != 1 || (n + m) != 2` kabhi false nahi ho sakta. Total size `1` ho, toh `!= 2` true; total size `2` ho, toh `!= 1` true; aur baaki totals ke liye dono true hain. `||` ke kaaran poori condition hamesha true rahegi.

Sirf loop condition badalna kaafi nahi hoga, kyunki body mein bhi invalid access aur size tracking ke bugs hain.

### 2. Empty vector par indexing

```cpp
nums1[0]
nums2[0]
```

Agar corresponding vector empty hai, toh index `0` valid nahi hai. Harness mein ek array empty hone wale tests hain, isliye is case ko algorithm mein explicitly handle karna zaroori hota.

### 3. `nums1[-1]` valid last-element access nahi hai

`vector::operator[]` ka index unsigned hota hai. `-1` ek bahut bada positive index ban jaata hai; isse out-of-bounds access hota hai. C++ mein last element ke liye `back()` use karte hain, lekin `back()` bhi empty vector par invalid hai.

### 4. `n` aur `m` galat update ho rahe hain

Pehle removal ke baad `n` decrement hota hai, chahe element `nums1` se nikla ho ya `nums2` se. Doosre removal ke baad `m` decrement hota hai, chahe element kisi bhi vector se nikla ho. Isliye `n` aur `m` actual vector sizes ko represent nahi karte.

### 5. Even-length median mein integer division

```cpp
(nums1[mid - 1] + nums1[mid]) / 2
```

Dono values `int` hain, isliye division integer division hogi. Example: `2` aur `3` ka result `2` milega, jabki median `2.5` hona chahiye. Floating-point division chahiye, jaise `sum / 2.0`.

Ek aur edge case: do bade `int` values ko add karne par overflow ho sakta hai. Addition ko `long long` mein karna safer hai.

### 6. Input vectors mutate ho rahe hain aur front erase costly hai

`erase(begin())` baaki elements ko shift karta hai. Is operation ko baar-baar karne se total time worst case mein **O((n + m)^2)** tak ho sakta hai. Median nikalne ke liye input arrays ko mutate karna zaroori nahi hai.

## Behtar Algorithm Tak Reasoning

### Step 1: Correct baseline socho

Dono arrays sorted hain. Do pointers/indices se merge order mein values dekh sakte hain. Poora merged array store karne ke bajay sirf median position tak process karo.

- Time: **O(n + m)** worst case
- Auxiliary space: **O(1)**
- Isse correct median logic aur odd/even total ka difference samajhna aasaan hota hai.

### Step 2: Optimization ka observation

Humein poora merged order nahi chahiye; sirf uska middle chahiye. Isliye dono arrays ko ek point par divide karne ki koshish karo:

```text
A: [ left part | right part ]
B: [ left part | right part ]
```

A aur B ke left parts mein total elements ki sankhya yeh honi chahiye:

```text
leftSize = (n + m + 1) / 2
```

`+1` odd total mein left side ko ek extra element deta hai. Isse odd aur even totals ko ek hi partition rule se handle kar sakte hain.

### Step 3: Partition valid kab hai?

Partition valid hai jab dono cross-boundary conditions satisfy hon:

```text
A ke left ka maximum <= B ke right ka minimum
B ke left ka maximum <= A ke right ka minimum
```

In conditions ka matlab hai ki dono left parts ke saare elements, dono right parts ke saare elements se chhote ya barabar hain. Toh yeh wahi division hai jo merged sorted array ke middle par hota.

- Total length odd ho toh median = left parts ka maximum.
- Total length even ho toh median = (left parts ka maximum + right parts ka minimum) / 2.

### Step 4: Binary search kahan lagti hai?

A ke left part mein kitne elements hon, us count ko `cut1` maan lo. Phir total left size fix hone ke kaaran B ka cut automatically milta hai:

```text
cut2 = leftSize - cut1
```

`cut1` ko **chhoti array** mein binary search karo. Agar A ka left boundary B ke right boundary se bada hai, toh A mein bahut zyada elements left side par hain; `cut1` ghatao. Warna doosri direction mein search karo.

Boundary par left ya right part empty ho sakta hai. Aise cases ko comparison mein handle karne ke liye `INT_MIN` aur `INT_MAX` sentinel values use kar sakte hain.

## Binary Search Ka Dry Run

Neeche `cut1` aur `cut2` batate hain ki respective array ke kitne elements left partition mein rakhe gaye hain. `left1` / `left2` left partitions ke last elements hain; `right1` / `right2` right partitions ke first elements hain.

### Dry Run 1: Odd Total, Pehle Partition Galat

```text
A = [1, 3, 8]
B = [2, 4, 6, 9]
Combined sorted order: [1, 2, 3, 4, 6, 8, 9]
Expected median: 4
```

`A` chhoti array hai, isliye isi par binary search hoti hai. `n = 3`, `m = 4`, aur `leftSize = (3 + 4 + 1) / 2 = 4`.

| Iteration | `low` | `high` | `cut1` | `cut2 = leftSize - cut1` | `left1, right1` | `left2, right2` | Decision                                                         |
| --------- | ----: | -----: | -----: | -----------------------: | --------------- | --------------- | ---------------------------------------------------------------- |
| 1         |     0 |      3 |      1 |                        3 | `1, 3`          | `6, 9`          | `left2 > right1` (`6 > 3`), so `cut1` badhaane ke liye `low = 2` |
| 2         |     2 |      3 |      2 |                        2 | `3, 8`          | `4, 6`          | Dono checks true: `3 <= 6` and `4 <= 8`; partition valid         |

Valid partition ko dekho:

```text
A: [1, 3 | 8]
B: [2, 4 | 6, 9]
    left       right
```

Left side ke total elements `4` hain. Total length odd hai, toh median `max(left1, left2) = max(3, 4) = 4`.

### Dry Run 2: Even Total, Boundary Sentinel

```text
A = [1, 2]
B = [3, 4, 5, 6]
Combined sorted order: [1, 2, 3, 4, 5, 6]
Expected median: (3 + 4) / 2 = 3.5
```

Yahan `n = 2`, `m = 4`, aur `leftSize = (2 + 4 + 1) / 2 = 3`.

| Iteration | `low` | `high` | `cut1` | `cut2` | `left1, right1` | `left2, right2` | Decision                                 |
| --------- | ----: | -----: | -----: | -----: | --------------- | --------------- | ---------------------------------------- |
| 1         |     0 |      2 |      1 |      2 | `1, 2`          | `4, 5`          | `left2 > right1` (`4 > 2`), so `low = 2` |
| 2         |     2 |      2 |      2 |      1 | `2, INT_MAX`    | `3, 4`          | Dono checks true; partition valid        |

Final partition:

```text
A: [1, 2 | ]
B: [3 | 4, 5, 6]
```

`cut1 == n`, isliye A ka right partition empty hai aur `right1 = INT_MAX` sentinel banta hai. Even total ke liye median dono middle boundaries ka average hota hai:

```text
max(left1, left2) = max(2, 3) = 3
min(right1, right2) = min(INT_MAX, 4) = 4
median = (3 + 4) / 2.0 = 3.5
```

### Code Ki Conditions Ko Yaad Rakhne Ka Tarika

- `left1 > right2`: A ke left mein values zyada badi hain; `cut1` ko left le jao (`high = cut1 - 1`).
- Warna agar partition valid nahi: B ke left mein values zyada badi hain; `cut1` ko right le jao (`low = cut1 + 1`).
- Dono cross-boundary checks true: sahi partition mil gaya; odd/even rule se answer nikalo.

## Optimized C++17 Implementation

```cpp
#include <algorithm>
#include <climits>
#include <vector>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }

        int n = static_cast<int>(nums1.size());
        int m = static_cast<int>(nums2.size());
        int leftSize = (n + m + 1) / 2;

        int low = 0;
        int high = n;

        while (low <= high) {
            int cut1 = low + (high - low) / 2;
            int cut2 = leftSize - cut1;

            int left1 = (cut1 == 0) ? INT_MIN : nums1[cut1 - 1];
            int right1 = (cut1 == n) ? INT_MAX : nums1[cut1];
            int left2 = (cut2 == 0) ? INT_MIN : nums2[cut2 - 1];
            int right2 = (cut2 == m) ? INT_MAX : nums2[cut2];

            if (left1 <= right2 && left2 <= right1) {
                int maxLeft = max(left1, left2);

                if ((n + m) % 2 == 1) {
                    return maxLeft;
                }

                int minRight = min(right1, right2);
                return (static_cast<long long>(maxLeft) + minRight) / 2.0;
            }

            if (left1 > right2) {
                high = cut1 - 1;
            } else {
                low = cut1 + 1;
            }
        }

        return 0.0; // Valid sorted inputs ke liye yahan nahi pahunchna chahiye.
    }
};
```

## Complexity

- **Time:** `O(log(min(n, m)))` — binary search chhoti array ke possible cuts par hoti hai.
- **Auxiliary space:** `O(1)` — kuch counters aur boundary values hi use hote hain.

## Important Edge Cases

- Ek array empty ho.
- Dono arrays mein ek-ek element ho.
- Total elements odd aur even hon.
- Arrays ke values interleave karte hon ya ranges disjoint hon.
- Duplicate aur negative values hon.
- Partition bilkul start ya end par aaye.
- Even median ke liye values ka sum `int` range se bada ho sakta ho.

## Learning Takeaway

Aapka initial idea elements hata kar middle tak pahunchne ki direction mein tha, lekin is problem mein repeated deletion avoid karna chahiye. Pehle two-pointer merge se correct **O(n + m)** baseline samjho. Phir yeh observe karo ki median ke liye poora merge nahi, sirf correct middle partition chahiye. Sorted arrays par partition ki validity monotonic hoti hai, isliye chhoti array mein binary search karke **O(log(min(n, m)))** solution milta hai.
