//Lab01
//QUESTION 1

class Solution {
public:
    vector<int> smallerNumbersThanCurrent(vector<int>& nums) {

        vector <int> result(nums.size(),0);

        for (int i = 0; i < nums.size(); i++)
        {
            int count = 0;
            for (int j = 0; j < nums.size(); j++)
            {
                if (i != j && nums[i] > nums[j])
                {
                    count++;
                }
            }
            result[i] = count;
        }
        return result;
    }
};

//QUESTION 2

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int count = 0;

        for (int idx = 0; idx < nums.size(); idx++)
        {
            if (nums[idx] != val)
            {
                nums[count] = nums[idx];
                count++;
            }


        }
        return count;

    }
};

//QUESTION 3

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        for (int x = 0; x < matrix.size(); x++)
        {
            for (int y = 0; y < matrix.size();y++)
            {
                if (matrix[x][y] == target)
                {
                    return true;
                }

            }
        }

        return false;
    }
};


//QUESTION 4

    class Solution {
    public:
        int removeDuplicates(vector<int>& nums) {
            int count = 1;
            if (nums.size() <= 1)
            {
                return nums.size();
            }
            for (int i = 1; i < nums.size(); i++)
            {
                if (nums[i] != nums[i - 1])
                {
                    nums[count] = nums[i];
                    count++;
                }
            }
            return count;

        }
    };

//QUESTION 5

    class Solution {
    public:
        int maxSubArray(vector<int>& nums) {
            int maxsum = nums[0];
            int currentsum = nums[0];

            for (int idx = 1; idx < nums.size(); idx++)
            {
                currentsum = max(nums[idx], currentsum + nums[idx]);

                maxsum = max(maxsum, currentsum);
            }

            return maxsum;
        }
    };

//QUESTION 6

    class Solution {
    public:
        int firstBadVersion(int n) {
            int left = 1;
            int right = n;

            while (left < right) {
                int mid = left + (right - left) / 2;

                if (isBadVersion(mid)) {
                    right = mid;
                }
                else {
                    left = mid + 1;
                }
            }

            return left;


        }
    };

//QUESTION 7

    class Solution {
    public:
        int firstMissingPositive(vector<int>& nums) {

            int n = nums.size();

            for (int i = 0; i < n; ++i) {
                while (nums[i] > 0 && nums[i] <= n && nums[i] != nums[nums[i] - 1]) {
                    std::swap(nums[i], nums[nums[i] - 1]);
                }
            }

            for (int i = 0; i < n; ++i) {
                if (nums[i] != i + 1) {
                    return i + 1;
                }
            }

            return n + 1;
        }
    };