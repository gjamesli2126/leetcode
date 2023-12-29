class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        if(!m) nums1=nums2;
        else if(!n) return;
        for(int p1=m-1,p2=n-1,i=m+n-1;p1>=0 || p2>=0 || i>=0;i--){
            if(p1>=0 && p2>=0){
                if(nums1[p1]>nums2[p2]){
                    nums1[i]=nums1[p1];
                    p1--;
                }
                else if(nums1[p1]<=nums2[p2]){
                    nums1[i]=nums2[p2];
                    p2--;
                } 
            }
            else if(p1>=0){
                nums1[i]=nums1[p1];
                p1--;
            }
            else if(p2>=0){
                nums1[i]=nums2[p2];
                p2--;
            }

        }
    }
};