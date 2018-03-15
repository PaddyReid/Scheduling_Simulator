#include "Job.hpp"
#include "Scheduler.hpp"
#include <fstream>

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
	//jobs.createJobs();

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
	//std::cout << "____________________________________" << std::endl;

	int print = 0;
	for (int i = JOB[0].arrival; i < fifo_list.size() + JOB[0].arrival; i++)
	{
		std::cout << time << "\t |" << schedules[count].FIFO << "\t |" << schedules[count].SJF << "\t |" << schedules[count].STTC <<
			"\t |" << schedules[count].RR << "\t |" << schedules[count].RRT << "\t |" << schedules[count].Notifications;

		if (startArray[print] == time)
		{
			std::cout << " *" << JOB[print].name << ". Has Arrived";
			print++;
		}
		
		std::cout <<  std::endl;

		//std::cout << time << schedules[count].STTC << std::endl;
		time++;
		count++;
	}

	std::cout << std::endl;
	std::cout << "Pre-Job statistics" << std::endl;
	//print Pre-Job statistics
	int i = 0;
	for (auto l : sheduler.sendStats_FIFO())
	{
		JOB[i].turnaround = l;
		i++;
	}

	count = 0;
	std::cout << "#" << "\t |" << "JOB" << "\t |" << "FIFO" << "\t |" << "SJF" << "\t |" << "STCF" << "\t |" << "RR" << "\t |" << "RRT" << "\t |" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		/*JOB[i] = sheduler.sendStats(i);*/
		std::cout << "T" << "\t |" << JOB[i].name << "\t |" << " " << "\t |" << JOB[i].turnaround <<
			"\t |" << schedules[count].RR << "\t |" << schedules[count].RRT << "\t |" << schedules[count].Notifications << std::endl;
		count++;
	}

	std::cout << std::endl;
	count = 0;
	std::cout << "#" << "\t |" << "JOB" << "\t |" << "FIFO" << "\t |" << "SJF" << "\t |" << "STCF" << "\t |" << "RR" << "\t |" << "RRT" << "\t |" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		/*JOB[i] = sheduler.sendStats(i);*/
		std::cout << "R" << "\t |" << JOB[i].name << "\t |" << JOB[i].turnaround << "\t |" << schedules[count].STTC <<
			"\t |" << schedules[count].RR << "\t |" << schedules[count].RRT << "\t |" << schedules[count].Notifications << std::endl;
		count++;
	}

	std::cout << "Aggregate statistics" << std::endl;
	std::cout << std::endl;
	count = 0;
	std::cout << "#" << "\t |" << "JOB" << "\t |" << "FIFO" << "\t |" << "SJF" << "\t |" << "STCF" << "\t |" << "RR" << "\t |" << "RRT" << "\t |" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		/*JOB[i] = sheduler.sendStats(i);*/
		std::cout << "R" << "\t |" << JOB[i].name << "\t |" << JOB[i].turnaround << "\t |" << schedules[count].STTC <<
			"\t |" << schedules[count].RR << "\t |" << schedules[count].RRT << "\t |" << schedules[count].Notifications << std::endl;
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
		myFile << "Blue Team " << " : " << " Red Team" << "  -  " << std::endl;
		myFile.close();

	}
	else
	{
		// use existing file
		myFile << "Blue Team " << " : " << " Red Team" << "  -  " << std::endl;
		myFile.close();
	}

	

}
