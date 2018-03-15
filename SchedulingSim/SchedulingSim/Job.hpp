#pragma once

#include <iostream>
#include <string>
#include <list>

struct Jobs
{
	std::string name;
	int arrival;
	int duration;

	int turnaround;
	int waittime;
	int response;


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
	std::string RRT;


	std::string Notifications;
};

class Job
{
	public:
		Job();
		void							myJobs();
		void							createJobs();
		void							resetJobs();
		void							printJobs();

		int								incrementTick();
		void							addJobsToList();
		void							schedulingJobs();
		float							preJobs();

		void							prinSchedule();
		void							pullInfo();
		void							printDemofile();

		
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
		std::list<std::string>			rrTwo_list;

		std::list<std::string>			sjf_completed;
		std::list<std::string>			fifo_completed;
		std::list<std::string>			stcf_completed;
		std::list<std::string>			rr_completed;
		std::list<std::string>			rrt_completed;

		//integrating time
		int								TICK;
		float							average_pre_FiFo;
		


		

		
};