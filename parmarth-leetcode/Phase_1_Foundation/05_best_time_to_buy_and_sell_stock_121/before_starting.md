# 121. Best Time to Buy and Sell Stock

## Problem Statement
Maximize profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.

### Invariant:
For each day `i`, the maximum possible profit if sold on day `i` is `prices[i] - min_price_seen_so_far`.
