#include <iostream>

#include <string>
#include <list>

struct Jobs
{
	std::string name;
	int arrival;
	int duration;

	bool operator <(const Jobs & playerObj) const
	{
		return arrival < playerObj.arrival;
	}
};

class JobClass
{
	public:
										JobClass();
		void							createJobs();
		void							resetJobs();
		void							printJobs();

		int								incrementTick();
		void							addJobsToList();


		//temp funtions
		void							FIFO(std::list<Jobs> joblist, int tick);


		
	private:
		//allowing myself to add 5 Jobs to the struct
		Jobs							JOB[5];
		std::list<Jobs>					initial_list;

		//integrating time
		int								TICK;


		

		
};