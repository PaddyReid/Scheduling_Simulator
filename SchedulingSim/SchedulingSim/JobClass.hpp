#include <iostream>

#include <stack>  
#include <string>
#include <array>

struct Jobs
{
	std::string name;
	int arrival;
	int duration;
};

class JobClass
{
	public:
										JobClass();
		//int							tick();
		void							createJobs();
		void							printJobs();

		int								incrementTick();
		

		
	private:
		//Job Variables -required for each job-
		std::string						JOB_NAME;
		int								ARRIVAL_TIME;
		int								DURATION;

		//allowing myself to add 5 Jobs to the struct
		Jobs							JOB[5];

		//integrating time
		int								TICK;

		//create stack to fill jobs
		std::stack<int>					JOB_STACK;


				
};