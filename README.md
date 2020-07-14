# Cirilo's algorithm
> An overkill algorithm for those in a hurry

The following is a description of a--as far as I know--new solution for the [Smallest Difference pair of values between two unsorted Arrays](https://www.geeksforgeeks.org/smallest-difference-pair-values-two-unsorted-arrays) problem.

## The problem

Simply stated, the problem consists of given two arrays of integers, **A** and **B** of size **m** and **n** respectively, find the pair of numbers **(A<sub>i</sub>, B<sub>j</sub>)** with the smallest difference between them.

So, given:

```
A = [1, 12, 150]
B = [32, -20, 11, 8]
```

The solution would be the array:
```
[12, 11]
```

### Classic solution

The solution proposed on GeeksforGeeks and others resources is based on sorting both arrays, and then finding the smallest pair using two pointers logic with linear complexity. The overall solution has a time complexity of **O(m*log(m) + n\*log(n))** and space complexity of **O(1)**.

The solution in pseudocode can be found below:

``` c
find(A, B) {
	A.sort()
	B.sort()

	a = 0
	b = 0

	smallestPair = [A[0], B[0]]

	while (a < A.length && b < B.length) {
		if (abs(A[a] - B[b]) < abs(smallestPair[0] - smallestPair[1]))
			smallestPair = [A[a],  B[b]]

		if (A[a] < B[b])
			a++
		else
			b++
	}

	return smallestPair
}
```

### Cirilo's algorithm

My solution sorts only the smallest array, taking **O(m\*log(m))**. 

After that, it computes and save in a hash map all the closest possible pairs between every number in the array and all numbers between **min(arr)** and **max(arr)**, that being the minimum and maximum value contained in the array. All of that can be done in **O(max(arr) - min(arr))**.

Finally, it only has to find the smallest pair between the two arrays using the previous hash map, that takes **O(n)**.

The final algorithm space complexity is:

**O(m\*log(m) + n + max(A) - min(A))** if the first array is smaller than the second, or:

**O(n\*log(n) + m + max(B) - min(B))** otherwise;

And the space complexity (because of the hash map) is:

**O(max(A) - min(A))** the first array is smaller than the second, or:

**O(max(B) - min(B))** otherwise

Pseudocode:

``` c
find(A, B) {
	if (A.length > B.length) {
		tmp = A
		A = B
		B = tmp
	}

	/* O(n*log(n)) */
	A.sort()

	closestMap = findClosestMap(A)

	smallestPair = [A[0], B[0]]
	
	/* O(m) */
	for (int i = 0; i < n; i++) {
		if (B[i] > A[A.length-1]
			currentFromA = A[A.length-1]
		} else if (B[i] < smallestFromA) {
			currentFromA = A[0]
		} else {
			currentFromA = closestMap[B[i]]
		}

		if (diff(currentFromA, B[i]) < diff(smallestPair[0], smallestPair[1])) {
			smallestPair = [currentFromA, B[i]]
		}
	}

	return smallestPair
}

/* O(max(A) - min(A))
 * iterate over every integer between A[0] and A[A.length-1]
 * and maps it to the closest value in A
 */
findClosestMap(A) {
	closestMap = createMap()
	
	for (i = 0; i < A.length-1; i++) {
		closestMap[A[i]] = A[i]

		middle = (A[i] + A[i+1]) / 2;

		for (num = A[i] + 1; num < A[i+1]; num++) {
			if (num <= middle) {
				closestMap[num] = arr[i]
			} else {
				closestMap[num] = arr[i+1]
			}
		}
	}

	closestMap[arr[n-1]] = arr[n-1]

	return closestMap
}


diff(a, b) {
	return abs(a - b)
}
```

## Comparison

The two algorithms are implemented [here](src/algorithms/classic/classic.c "classic solution") and [here](src/algorithms/cirilo/cirilo.c "my solution"). There is also a program that tests one solution against the other, that can be found [here](src/test.c). 

The following is a result of a comparison with random arrays of same size ranging from 2 to 200000, with integers between -10000 to 10000.

![alt text](data/svg/2-200000-1.svg "Comparison")

## Drawbacks
