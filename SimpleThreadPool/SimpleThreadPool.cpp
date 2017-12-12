// SimpleThreadPool.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ThreadPool.h"

int main()
{

	ThreadPool pool(4);
	std::vector< std::future<int> > results;

	for (int i = 0; i < 3; ++i) {
		// Appends a new element to the end of the results vector.
		// this would be result of the Lambda function that is queued
		results.emplace_back(
			// Lambda added to pool queue - that takes the iterative 'i' and incorporate into a split "hello world" message (with 1 second delay) finally returning the square of the iterative
			pool.enqueue([i] {
			std::cout << "hello " << i << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << "world " << i << std::endl;
			return i*i;
		})
		);
	}

	std::cout << "\nResult = ";
	for (auto && result : results)
		std::cout << result.get() << ' ';
	std::cout << std::endl;

	return 0;
}