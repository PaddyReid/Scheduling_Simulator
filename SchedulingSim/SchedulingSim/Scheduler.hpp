#pragma once

#include <iostream>
#include <string>
#include <stack>



class Scheduler
{

public:
	int					getJobs();
	static void			FirstInFirstOut(std::string, int, int, int, int, int);

private:
	std::stack<int>		FIFOStack;
	
	


};
