// ───────────────────────────────────────────────────────────────
// 1) lower_bound(inclusive)
//    → first index i such that arr[i] >= target
//    → returns n if all arr[i] < target
int lower_bound_inclusive(const vector<int>& arr, int target) {
    int l = 0, r = arr.size();
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] < target)
            l = mid + 1;
        else
            r = mid;
    }
    return l;
}

// ───────────────────────────────────────────────────────────────
// 2) lower_bound(exclusive)
//    → last index j such that arr[j] < target
//    → returns ‑1 if all arr[i] >= target
int lower_bound_exclusive(const vector<int>& arr, int target) {
    int l = 0, r = arr.size();
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] < target)
            l = mid + 1;
        else
            r = mid;
    }
    return l - 1;//can return max(0,l-1) to prevent out of bound
}

// ───────────────────────────────────────────────────────────────
// 3) upper_bound(exclusive)
//    → first index i such that arr[i] > target
//    → returns n if all arr[i] <= target
int upper_bound_exclusive(const vector<int>& arr, int target) {
    int l = 0, r = arr.size();
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] <= target)
            l = mid + 1;
        else
            r = mid;
    }
    return l;
}

// ───────────────────────────────────────────────────────────────
// 4) upper_bound(inclusive)
//    → last index j such that arr[j] <= target
//    → returns ‑1 if all arr[i] > target
int upper_bound_inclusive(const vector<int>& arr, int target) {
    int l = 0, r = arr.size();
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] <= target)
            l = mid + 1;
        else
            r = mid;
    }
    return l - 1;//can return max(0,l-1) to prevent out of bound
}