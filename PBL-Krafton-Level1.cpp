#include <iostream>
#include <Windows.h>
#include <ctime>

int main()
{
	std::cout << "Hello World!\n";
	clock_t start = clock();
	for (;;)
	{
		clock_t end = clock();
		if ((end - start) % 1000 == 0)
			std::cout << end << std::endl;
	}
}
