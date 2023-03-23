#include <stdio.h>
int ans = 100;
// the answer is stored in ans
// we call this function solve
// max function is used to find max of two elements
int max(int a, int b) { return a > b ? a : b; }
// min function is used to find min of two elements
int min(int a, int b) { return a < b ? a : b; }

void sprint(int* arr,int h,int t){
    int i;
    for(i=h;i<t;i++){
        printf("%d ",arr[i]);
    }
}
void solve(int a[], int n, int k, int indx, int sum,int maxsum, int deep){
    // K=1 is the base Case
    if (k == 1) {
        maxsum = max(maxsum, sum);
        sum = 0;
        for (int i = indx; i < n; i++) {
            sum += a[i];
        }
        // we update maxsum
        maxsum = max(maxsum, sum);
        // the answer is stored in ans
        ans = min(ans, maxsum);
        printf("-------------------------k=1---\n");
        return;
    }
    sum = 0;
    // using for loop to divide the array into K-subarray
    for (int i = indx; i < n; i++) {
        sum += a[i];
        // for each subarray we calculate sum ans update
        // maxsum
        maxsum = max(maxsum, sum);
        // calling function again

        printf("ind %d sum %d maxsum %d a[i] %d ans %d deep %d\t\t" ,i,sum,maxsum,a[i],ans,deep);
        sprint(a,indx,n);
        printf("\n");
        solve(a, n, k - 1, i + 1, sum, maxsum,deep+1);
    }
}
// Driver Code
int main(){
    int deep=0;
    int arr[] = { 3,9,6,7,8,11,1,4,7 };
    int k = 4; // K divisons
    int n = 9; // Size of Array
    solve(arr, n, k, 0, 0, 0,deep);
    printf("%d", ans);
}
