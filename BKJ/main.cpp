public class Solution {
	public int RemoveDuplicates(int[] nums) {
		int ret = 0;
		Dictionary<int, int> dic = new Dictionary<int, int>();

		int idx = 0;
		for (int i = 0; i < nums.Length; i++)
		{
			if (!dic.ContainsKey(nums[i]))
				dic.Add(nums[i], 0);

			dic[nums[i]]++;
			if (dic[nums[i]] <= 2)
			{
				ret++;
				nums[idx++] = nums[i];
			}
		}

		return ret;
	}
}