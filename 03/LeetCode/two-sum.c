/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    int *old;
    old = (int*)malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; i++) old[i] = nums[i];
    int *ans;
    ans = (int*)malloc(2 * sizeof(int));
    int temp;
    *returnSize = 2;
    for (int i = 0; i < numsSize - 1; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[i] > nums[j]) {
                temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
            }
        }
    }
    for (int i = 0; i < numsSize; i++) {
            int l = 0, r = numsSize-1, m;
            while (r - l > 1) {
                m = (l + r)/2;
                if (nums[m] + nums[i] >= target) r = m;
                else l = m;
            }
            if (r != i && nums[i] + nums[r] == target) {
                for (int k = 0; k < numsSize; k++) {
                    if (old[k] == nums[i]) {
                        ans[0] = k;
                        break;
                    }
                }
                for (int k = 0; k < numsSize; k++) {
                    if (old[k] == nums[r] && k != ans[0]) {
                        ans[1] = k;
                        break;
                    }
                }
                return ans;
            }
        }
        return ans;
}

// https://leetcode.com/submissions/detail/816671208/
