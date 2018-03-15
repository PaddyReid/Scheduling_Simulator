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

struct scheduling
{
	std::string FIFO;
	std::string SJF;
	std::string STTC;
	std::string RR;
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
		void							STTC(std::list<Jobs> joblist, int tick);
		void							SJF(std::list<Jobs> joblist, int tick);
		void							RR(std::list<Jobs> joblist, int tick);
		void							prinSchedule();

		
	private:
		//allowing myself to add 5 Jobs to the struct
		Jobs							JOB[5];
		scheduling						schedules[100];

		std::list<Jobs>					initial_list;

		std::list<scheduling>			scheduling;
		std::list<std::string>			fifo_list;
		std::list<std::string>			sjf_list;
		std::list<std::string>			stcf_list;
		std::list<std::string>			rr_list;

		//integrating time
		int								TICK;


		

		
};