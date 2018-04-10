#pragma once

#include <iostream>
#include <string>
#include <list>

struct Jobs
{
	std::string name;
	int arrival;
	int duration;

	float turnaround;
	float turnaround_1;
	float turnaround_2;
	float turnaround_3;
	float turnaround_4;

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
		std::list<Jobs>					addJobsToList();
		std::list<scheduling>			schedulingJobs(std::list<std::string> fifo, std::list<std::string> sjf,
			std::list<std::string> stct, std::list<std::string> rr, std::list<std::string> rrt, std::list<std::string> c_fifo, 
			std::list<std::string> c_sjf, std::list<std::string> c_stct, std::list<std::string> c_rr, std::list<std::string> c_rrt);

		void							prinSchedule(std::list<scheduling> list);
		void							pullInfo();
		void							printDemofile();

		
	private:
		//allowing myself to add 5 Jobs to the struct
		Jobs							JOB[5];
		scheduling						schedules[500];

		std::list<Jobs>					initial_list;
		std::list<scheduling>			to_print;

		//std::list<scheduling>			scheduling;
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