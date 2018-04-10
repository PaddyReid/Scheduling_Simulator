#include "Job.hpp"
#include "Scheduler.hpp"
#include <fstream>

Job jobs;
Scheduler sheduler;

Job::Job()
{
}

void Job::pullInfo()
{
	std::ifstream infile("Jobs.txt");
	std::string name;
	int arrival, duration;
	int i = 0;
	while (infile >> name >> arrival >> duration)
	{
		//add Job to satck
		JOB[i].name = name;
		JOB[i].arrival = arrival;
		JOB[i].duration = duration;
		i++;
	}
}

void Job::myJobs()
{
	TICK = 0;
	//create Jobs
	jobs.createJobs();

	//pull jobs from file
	jobs.pullInfo();

	//Jobs to list
	initial_list = jobs.addJobsToList();

	//Printing Jobs
	jobs.printJobs();

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

	to_print = schedulingJobs(fifo_list, sjf_list, stcf_list, rr_list, rrTwo_list, fifo_completed, sjf_completed,
		stcf_completed, rr_completed, rrt_completed);

	//for (auto l : to_print)
	//{
	//	std::cout << "W " << l.FIFO << std::endl;
	//}

	//print
	jobs.prinSchedule(to_print);

}

std::list<Jobs> Job::addJobsToList()
{
	//Adding Jobs to a list
	for (int i = 0; i < 5; i++)
	{
		initial_list.push_back(JOB[i]);
	}

	return initial_list;

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
	JOB[0].arrival = 11;
	JOB[0].duration = 7;

	////Job two's information
	JOB[1].name = "JOB_B";
	JOB[1].arrival = 6;
	JOB[1].duration = 9;

	////Job three's information
	JOB[2].name = "JOB_C";
	JOB[2].arrival = 4;
	JOB[2].duration = 10;

	////Job four's information
	JOB[3].name = "JOB_D";
	JOB[3].arrival = 0;
	JOB[3].duration = 8;

	////Job five's information
	JOB[4].name = "JOB_E";
	JOB[4].arrival = 3;
	JOB[4].duration = 5;

}

void Job::resetJobs()
{
	int i = 0;
	for (Jobs v : initial_list)
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
	for (Jobs v : initial_list)
	{
		//printing as we loop
		std::cout << v.name << " " << v.arrival << " " << v.duration << std::endl;
	}
	std::cout << " " << std::endl;


}

std::list<scheduling> Job::schedulingJobs(std::list<std::string> fifo, std::list<std::string> sjf,
	std::list<std::string> stct, std::list<std::string> rr, std::list<std::string> rrt, std::list<std::string> c_fifo,
	std::list<std::string> c_sjf, std::list<std::string> c_stct, std::list<std::string> c_rr, std::list<std::string> c_rrt)
{
	int count = 0;
	int globalCount = 0;
	for (std::string list : fifo)
	{
		schedules[count].FIFO = list;
		count++;
		globalCount++;
	}
	count = 0;
	for (std::string list : sjf)
	{
		schedules[count].SJF = list;
		count++;
	}
	count = 0;
	for (std::string list : stct)
	{
		schedules[count].STTC = list;
		count++;
	}
	count = 0;
	for (std::string list : rr)
	{
		schedules[count].RR = list;
		count++;
	}
	count = 0;
	for (std::string list : rrt)
	{
		schedules[count].RRT = list;
		count++;
	}
	count = 0;
	for (std::string list : c_fifo)
	{
		schedules[count].Notifications = list;
		count++;
	}
	count = 0;
	for (std::string list : c_sjf)
	{
		schedules[count].Notifications = schedules[count].Notifications  + list;
		count++;
	}
	count = 0;
	for (std::string list : c_stct)
	{
		schedules[count].Notifications = schedules[count].Notifications  + list;
		count++;
	}

	count = 0;
	for (std::string list : c_rr)
	{
		schedules[count].Notifications = schedules[count].Notifications  + list;
		count++;
	}


	for (std::string list : c_rrt)
	{
		schedules[count].Notifications = schedules[count].Notifications  + list;
		count++;
	}

	for (int i = 0; i < globalCount; i++)
	{
		to_print.push_back(schedules[i]);
	}

	return to_print;

}

void Job::prinSchedule(std::list<scheduling> list)
{
	Job::printDemofile();
	int count = 0;
	Job::resetJobs();
	int time = JOB[0].arrival;

	int startArray[5];

	for (int i = 0; i < 5; i++)
	{
		startArray[i] = JOB[i].arrival;
	}
	std::cout << "T" << "\t |" << "FIFO" << "\t |" << "SJF" << "\t |" << "STCF" << "\t |" << "RR" << "\t |" << "RRT" << "\t |" << "Notifications" << "\n" << std::endl;

	int print = 0;
	for (scheduling schedules : list)
	{
		std::cout << time << "\t |" << schedules.FIFO << "\t |" << schedules.SJF << "\t |" << schedules.STTC <<
			"\t |" << schedules.RR << "\t |" << schedules.RRT << "\t |" << schedules.Notifications;

		if (startArray[print] == time)
		{
			std::cout << " *" << JOB[print].name << ". Has Arrived";
			print++;
		}

		std::cout << std::endl;

		//std::cout << time << schedules[count].STTC << std::endl;
		time++;
		count++;
		print++;
	}

	//for (int i = JOB[0].arrival; i < fifo_list.size() + JOB[0].arrival; i++)
	//{
	//	std::cout << time << "\t |" << schedules[count].FIFO << "\t |" << schedules[count].SJF << "\t |" << schedules[count].STTC <<
	//		"\t |" << schedules[count].RR << "\t |" << schedules[count].RRT << "\t |" << schedules[count].Notifications;

	//	if (startArray[print] == time)
	//	{
	//		std::cout << " *" << JOB[print].name << ". Has Arrived";
	//		print++;
	//	}
	//	
	//	std::cout <<  std::endl;

	//	//std::cout << time << schedules[count].STTC << std::endl;
	//	time++;
	//	count++;
	//}

	std::cout << std::endl;
	std::cout << "Pre-Job statistics" << std::endl;

	//print Pre-Job statistics

	int i = 0;
	for (float l : sheduler.sendStats_FIFO())
	{
		JOB[i].turnaround = l;
		i++;
	}

	i = 0;
	for (float l : sheduler.sendStats_SJF())
	{
		JOB[i].turnaround_1 = l;
		i++;
	}

	i = 0;
	for (float l : sheduler.sendStats_STCF())
	{
		JOB[i].turnaround_2 = l;
		i++;
	}

	i = 0;
	for (float l : sheduler.sendStats_RR())
	{
		JOB[i].turnaround_3 = l;
		i++;
	}

	i = 0;
	for (float l : sheduler.sendStats_RRT())
	{
		JOB[i].turnaround_4 = l;
		i++;
	}

	count = 0;
	std::cout << "#" << "\t" << "JOB" << "\t" << "FIFO" << "\t" << "SJF" << "\t" << "STCF" << "\t" << "RR" << "\t" << "RRT" << "\t" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		/*JOB[i] = sheduler.sendStats(i);*/
		std::cout << "T" << "\t" << JOB[i].name << "\t" << JOB[i].turnaround << "\t" << JOB[i].turnaround_1 <<
			"\t" << JOB[i].turnaround_2 << "\t" << JOB[i].turnaround_3 << "\t" << JOB[i].turnaround_4 << std::endl;
		count++;
	}

	std::cout << std::endl;
	count = 0;
	std::cout << "#" << "\t" << "JOB" << "\t" << "FIFO" << "\t" << "SJF" << "\t" << "STCF" << "\t" << "RR" << "\t" << "RRT" << "\t" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		/*JOB[i] = sheduler.sendStats(i);*/
		std::cout << "R" << "\t" << JOB[i].name << "\t" << JOB[i].turnaround << "\t" << JOB[i].turnaround_1 <<
			"\t" << JOB[i].turnaround_2 << "\t" << JOB[i].turnaround_3 << "\t" << JOB[i].turnaround_4 << std::endl;
		count++;
	}

	std::cout << "Aggregate statistics" << std::endl;
	std::cout << std::endl;
	count = 0;
	std::cout << "#" << "\t" << "JOB" << "\t" << "FIFO" << "\t" << "SJF" << "\t" << "STCF" << "\t" << "RR" << "\t" << "RRT" << "\t" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		/*JOB[i] = sheduler.sendStats(i);*/
		/*JOB[i] = sheduler.sendStats(i);*/
		std::cout << "" << "\t" << JOB[i].name << "\t" << JOB[i].turnaround << "\t" << JOB[i].turnaround_1 <<
			"\t" << JOB[i].turnaround_2 << "\t" << JOB[i].turnaround_3 << "\t" << JOB[i].turnaround_4 << std::endl;
		count++;
	}

}

void Job::printDemofile()
{
	char filename[] = "demo_output1.txt";
	std::fstream myFile;

	myFile.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);

	// If file does not exist, Create new file
	if (!myFile)
	{
		myFile.open(filename, std::fstream::in | std::fstream::out | std::fstream::trunc);


		//myFile << "test" << std::endl;
		//myFile << "T" << "\t |" << "FIFO" << "\t |" << "SJF" << "\t |" << "STCF" << "\t |" << "RR" << "\t |" << "RRT" << "\t |" << "Notifications" << "\n" << std::endl;
		myFile.close();

	}
	else
	{
		// use existing file
		myFile.close();
	}

	

}
