class Solution {
private:
    struct wall{
        int left,right;
    };
public:
    int trap(vector<int>& height) {
        int n=height.size();
        vector<wall> wallInd(n);
        int maxH=0;
        //left wall
        for(int i=0;i<n;i++){
            maxH=max(maxH,height[i]);
            wallInd[i].left=maxH;
        }        
        maxH=0;
        //right wall
        for(int i=n-1;i>=0;i--){
            maxH=max(maxH,height[i]);
            wallInd[i].right=maxH;
        }
        //calc water avail
        int acc=0;
        for(int i=0;i<n;i++){
            acc+=min(wallInd[i].left,wallInd[i].right)-height[i];
        } 
        return acc;     
    }
};