#include "Job.hpp"
#include "Scheduler.hpp"


Job jobs;
Scheduler sheduler;

Job::Job()
{
}

int main()
{
	jobs.myJobs();

	system("pause");
	return 0;
}

void Job::myJobs()
{
	TICK = 0;
	//create Jobs
	jobs.createJobs();

	//Jobs to list
	jobs.addJobsToList();

	//Printing Jobs
	//jobs.printJobs();

	//Sort jobs by arrival time for FIFO
	initial_list.sort();

	//Running the schedules
	fifo_list = sheduler.FirstInFirstOut(initial_list, TICK);
	sjf_list = sheduler.ShortestJobFirst(initial_list, TICK);
	stcf_list = sheduler.ShortestTimeToCompletion(initial_list, TICK);
	rr_list = sheduler.RoundRobin(initial_list, TICK);
	rrTwo_list = sheduler.RoundRobinTwo(initial_list, TICK);

	sjf_completed = sheduler.getCompleted();
	fifo_completed = sheduler.fifo_getCompleted();
	stcf_completed = sheduler.stcf_getCompleted();
	rr_completed = sheduler.rr_getCompleted();
	rrt_completed = sheduler.rrt_getCompleted();

	//Add Jobs to print
	Job::schedulingJobs();

	//print
	Job::prinSchedule();

}

void Job::addJobsToList()
{
	//Adding Jobs to a list
	for (int i = 0; i < 5; i++)
	{
		initial_list.push_back(JOB[i]);
	}

}

int Job::incrementTick()
{
	TICK++;

	return TICK;
}


void Job::createJobs()
{
	// **Manually seeting up Jobs**

	//Job one's information
	JOB[0].name = "JOB_A";
	JOB[0].arrival = 21;
	JOB[0].duration = 8;

	////Job two's information
	JOB[1].name = "JOB_B";
	JOB[1].arrival = 10;
	JOB[1].duration = 6;

	////Job three's information
	JOB[2].name = "JOB_C";
	JOB[2].arrival = 9;
	JOB[2].duration = 3;

	////Job four's information
	JOB[3].name = "JOB_D";
	JOB[3].arrival = 8;
	JOB[3].duration = 30;

	////Job five's information
	JOB[4].name = "JOB_E";
	JOB[4].arrival = 15;
	JOB[4].duration = 5;

}

void Job::resetJobs()
{
	int i = 0;
	for (auto v : initial_list)
	{
		JOB[i].name = v.name;
		JOB[i].arrival = v.arrival;
		JOB[i].duration = v.duration;
		i++;
	}
}

void Job::printJobs()
{
	//Printing Jobs to see what goes into each schedule
	std::cout << "Initial input" << std::endl;
	for (auto v : initial_list)
	{
		//printing as we loop
		std::cout << v.name << " " << v.arrival << " " << v.duration << std::endl;
	}
	std::cout << " " << std::endl;
}

void Job::schedulingJobs()
{
	int count = 0;
	for (auto list : fifo_list)
	{
		schedules[count].FIFO = list;
		count++;
		//std::cout << list << std::endl;
	}
	count = 0;
	for (auto list : sjf_list)
	{
		schedules[count].SJF = list;
		count++;
	}
	count = 0;
	for (auto list : stcf_list)
	{
		schedules[count].STTC = list;
		count++;
	}
	count = 0;
	for (auto list : rr_list)
	{
		schedules[count].RR = list;
		count++;
	}
	count = 0;
	for (auto list : rrTwo_list)
	{
		schedules[count].RRT = list;
		count++;
	}
	count = 0;
	for (auto list : fifo_completed)
	{
		schedules[count].Notifications = list;
		count++;
	}
	count = 0;
	for (auto list : sjf_completed)
	{
		schedules[count].Notifications = schedules[count].Notifications + " " + list;
		count++;
	}
	count = 0;
	for (auto list : stcf_completed)
	{
		schedules[count].Notifications = schedules[count].Notifications + " " + list;
		count++;
	}

	count = 0;
	for (auto list : rr_completed)
	{
		schedules[count].Notifications = schedules[count].Notifications + " " + list;
		count++;
	}

	count = 0;
	for (auto list : rrt_completed)
	{
		schedules[count].Notifications = schedules[count].Notifications + " " + list;
		count++;
	}


}

void Job::prinSchedule()
{
	std::cout << "T" << "\t |" << "FIFO" << "\t |" << "SJF" << "\t |" << "STCF" << "\t |" << "RR" << "\t |" << "RRT" << "\t |" << "Notifications" << "\n" << std::endl;
	//std::cout << "____________________________________" << std::endl;

	int count = 0;
	Job::resetJobs();
	int time = JOB[0].arrival;
	for (int i = JOB[0].arrival; i < fifo_list.size() + JOB[0].arrival + 5; i++)
	{
		std::cout << time << "\t |" << schedules[count].FIFO << "\t |" << schedules[count].SJF << "\t |" << schedules[count].STTC <<
			"\t |" << schedules[count].RR << "\t |" << schedules[count].RRT << "\t |" << schedules[count].Notifications << std::endl;
		time++;
		count++;
	}

}