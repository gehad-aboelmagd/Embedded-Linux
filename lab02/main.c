#include <stdio.h>

int binarySearch(int *arr, int start, int end, int num)
{
	int mid;
	if(start <= end)
	{
		mid = (start + end) / 2;
		if(num == arr[mid])
		{
			return mid;
		}
		else if(num > arr[mid])
		{
			start = mid+1;
			return binarySearch(arr, start, end, num);
		}
		else
		{
			end = mid-1;
			return binarySearch(arr, start, end, num);
		}
	}
	else
	{
		return -1;
	}
}

int main(void)
{
	int sortedArr[] = {1, 2, 3, 4, 5};
	int searchElement = 10;
	int i = binarySearch(sortedArr, 0, 4, searchElement);
	printf("Element %d is found at %d\n", searchElement, i);

	return 0;
}
