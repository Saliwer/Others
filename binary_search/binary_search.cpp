#include <iostream>
#include <chrono> //дл€ класса Timer

class Timer {
private:
	//ѕсевдонимы типов дл€ удобств
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1>>;
	std::chrono::time_point<clock_t> m_beg;
	
public:
	Timer():m_beg(clock_t::now())
	{}
	void reset() {
		m_beg = clock_t::now();
	}
	double elapsed() const
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
	
};


// array - input array
// target - searched value
// The search is carrying out in the range between [min,max]
int binarySearch(int *array, int target, int min, int max);	//Iteration binary search
int binarySearchRec(int *array, int target, int min, int max); //Recursive binary search
int NotBinarySearch(int *array, int target, int countElements); 
int main()
{
	int count_elem = 10000;
	int* array = new int [count_elem];
	for (int i = 0; i < 10000; ++i) {
		array[i] = i + 1;
	}

	std::cout << "Enter a number: ";
	int x;
	std::cin >> x;
	Timer t;
	int index = binarySearch(array, x, 0, count_elem);
	std::cout << "For binarySearch() time elapsed: " << t.elapsed() <<'\n';
	
	t.reset();
	index = binarySearchRec(array, x, 0, count_elem);
	std::cout << "For binarySearchRec() time elapsed: " << t.elapsed() << '\n';

	t.reset();
	index = NotBinarySearch(array, x, count_elem);
	std::cout << "For NotBinarySearch() time elapsed: " << t.elapsed() << '\n';

	if (array[index] == x)
		std::cout << "Good! Your value " << x << " is on position " << index << " in array!\n";
	else
		std::cout << "Fail! Your value " << x << " isn't in array!\n";

	system("pause");
	return 0;
}

int NotBinarySearch(int *array, int target, int countElements) {
	for (int i = 0; i < countElements; ++i) {
		if (array[i] == target)
			return i;
	}
	return -1;
}

//Iteration binary search
int binarySearch(int *array, int target, int min, int max) {
	while (min <= max) {
		int midpoint = min + ((max - min) / 2);
		if (array[midpoint] > target) {
			max = midpoint - 1;
		}
		else if (array[midpoint] < target) {
			min = midpoint + 1;
		}
		else
		{
			return midpoint;
		}
	}
	return -1;
}

//Recursive binary search
int binarySearchRec(int *array, int target, int min, int max) {
	if (min > max)
		return -1;
	int midpoint = min + ((max - min) / 2);
	if (array[midpoint] > target)
		return binarySearch(array, target, min, midpoint - 1);
	else if (array[midpoint] < target)
		return binarySearch(array, target, midpoint + 1, max);
	else
		return midpoint;

}
