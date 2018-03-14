
#include "JobClass.hpp"
#include "Scheduler.hpp"

//Scheduler sheduler;

int main()
{
	JobClass();

	system("pause");
	return 0;
}

JobClass::JobClass()
{
	TICK = 0;
	//create Jobs
	JobClass::createJobs();

	//Jobs to list
	JobClass::addJobsToList();

	//Printing Jobs
	JobClass::printJobs();

	//Sort jobs by arrival time for FIFO
	initial_list.sort();

	//FIFO
	//JobClass::FIFO(initial_list, TICK);

	//RUN JOB SJF
	JobClass::SJF(initial_list, TICK);

	//RUN JOB STTC
	//JobClass::STTC(initial_list, TICK);

	//RUN JOB RR

}

void JobClass::addJobsToList()
{
	//Adding Jobs to a list
	for (int i = 0; i < 5; i++)
	{
		initial_list.push_back(JOB[i]);
	}
}

int JobClass::incrementTick()
{
	TICK++;

	return TICK;
}


void JobClass::createJobs()
{
	// **Manually seeting up Jobs**

	//Job one's information
	JOB[0].name = "A";
	JOB[0].arrival = 21;
	JOB[0].duration = 8;

	////Job two's information
	JOB[1].name = "B";
	JOB[1].arrival = 10;
	JOB[1].duration = 6;

	////Job three's information
	JOB[2].name = "C";
	JOB[2].arrival = 9;
	JOB[2].duration = 3;

	////Job four's information
	JOB[3].name = "D";
	JOB[3].arrival = 8;
	JOB[3].duration = 3;

	////Job five's information
	JOB[4].name = "E";
	JOB[4].arrival = 15;
	JOB[4].duration = 5;
}

void JobClass::resetJobs()
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


void JobClass::printJobs()
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


void JobClass::SJF(std::list<Jobs> joblist, int tick)
{
	std::cout << "Running SJF" << std::endl;
	std::cout << " " << std::endl;
	JobClass::resetJobs();
	int current; bool printing = false;
	int count = 0, jobNumber = 0;
	int smallest = rand();
	bool print = false;
	while (joblist.size() > 0)
	{
		//job arrived??
		for (int i = 0; i < 5; i++)
		{
			if (JOB[i].arrival == tick)
			{
				jobNumber = i;
				print = true;
				count++;
				break;
			}
		}

		if (print)
		{
			std::cout << " JOB: " << JOB[jobNumber].name << " *ARRIVED*" << std::endl;
			print = false;
			smallest = 10000;
		}

		if (count >= 1)
		{
			//Look for smallest
			if (!printing)
			{
				//look for smallest available job
				for (int i = 0; i < count; i++)
				{
					if (JOB[i].duration < smallest)
					{
						if (JOB[i].duration != 0)
						{
							smallest = JOB[i].duration;
							current = i;
							printing = true;
						}
					}
				}
			}
		}

		if (printing)
		{
			if (JOB[current].duration != 0)
			{
				std::cout << "Elapsed time " << tick << " Job: [" << JOB[current].name << "] Running, time remaining = " << JOB[current].duration-- << std::endl;
			}
			else
			{
				std::cout << " JOB: " << JOB[current].name << " * Completed" << std::endl;
				smallest = 10000;
				printing = false;
			}
		}

		

		tick++;
	}

}

void JobClass::STTC(std::list<Jobs> joblist, int tick)
{
	std::cout << "Running STTC" << std::endl;
	std::cout << " " << std::endl;
	JobClass::resetJobs();
	int count = 0, jobNumber = 0, smallest = JOB[0].duration;
	int jobToPrint = 0;
	bool print = false;
	tick = 0;
	while (joblist.size() > 0)		
	{
		//Check for arrivals
		for (int i = 0; i < 5; i++)
		{
			if (JOB[i].arrival == tick)
			{
				jobNumber = i;
				print = true;
				count++;
				break;
			}
		}

		//Look for smallest
		if(count > 1)
		{
			for (int i = 0; i < count; i++)
			{
				if (JOB[i].duration < smallest)
				{
					if (JOB[i].duration != 0)
					{
						smallest = JOB[i].duration;
						jobToPrint = i;
					}
				}
			}
			if (JOB[jobToPrint].duration < 1)
			{
				//smallest needs to chage to a large number
				smallest = 200;
				std::cout << " JOB: " << JOB[jobToPrint].name << " * Completed";
				std::cout << "" << std::endl;
				joblist.pop_back();
			}
			else
			{
				std::cout << "Elapsed time " << tick << " Job: [" << JOB[jobToPrint].name << "] Running, time remaining = " << JOB[jobToPrint].duration--;
			}
		}
		else if (count >= 1)
		{
			std::cout << "Elapsed time " << tick << " Job: [" << JOB[count - 1].name << "] Running, time remaining = " << JOB[count - 1].duration--;
		}
		

		if (print)
		{
			std::cout << " JOB: " << JOB[jobNumber].name << " *ARRIVED*";
			print = false;
		}

		//Need to remove need for this when nothing is printed
		std::cout << "" << std::endl;

		tick++;
	}
}

//temp
void JobClass::FIFO(std::list<Jobs> joblist, int tick)
{
	std::cout << "Running FIFO" << std::endl;
	std::cout << " " << std::endl;
	JobClass::resetJobs();
	int count = 0, jobNumber = 0;
	bool print = false;
	//We know jobs are in order according to their arrival time
	while (JOB[4].duration > 0)
	{
		//Check for arrivals
		for (int i = 0; i < joblist.size() - 1; i++)
		{
			if (JOB[i].arrival == tick)
			{
				jobNumber = i;
				print = true;
				break;
				//std::cout << "JOB: " << JOB[i].name << " *ARRIVED* Tick [" << tick << "] ";
			}
		}

		if (JOB[count].arrival <= tick)
		{
			std::cout << "Elapsed time " << tick << " Job: [" << JOB[count].name << "] Running, time remaining = " << JOB[count].duration--;

			if (JOB[count].duration < 0)
			{
				count++;
				std::cout << " JOB: " << JOB[count].name << " * Completed";
				std::cout << "" << std::endl;
			}

		}

		if (print)
		{
			std::cout << " JOB: " << JOB[jobNumber].name << " *ARRIVED*";
			print = false;
		}

		//Need to remove need for this when nothing is printed
		std::cout << "" << std::endl;

		tick++;
	}

	std::cout << "All Jobs have finished" << "\n" << std::endl;


}