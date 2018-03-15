
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
	JobClass::FIFO(initial_list, TICK);

	//RUN JOB SJF
	JobClass::SJF(initial_list, TICK);

	//RUN JOB STTC
	JobClass::STTC(initial_list, TICK);

	//RUN JOB RR
	JobClass::RR(initial_list, TICK);

	JobClass::prinSchedule();

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

void JobClass::prinSchedule()
{
	std::cout << "T" << "\t |" << "FIFO" << "\t |" << "SJF" << "\t |" << "STCF" << "\t |" << "RR" << "\n" << std::endl;
	//std::cout << "____________________________________" << std::endl;

	int time = 0;
	for (auto s : fifo_list)
	{
		schedules[time].FIFO = s;
		time++;
	}
	time = 0;
	for (auto s : sjf_list)
	{
		schedules[time].SJF = s;
		time++;
	}
	time = 0;
	for (auto s : stcf_list)
	{
		schedules[time].STTC = s;
		time++;
	}
	time = 0;
	for (auto s : rr_list)
	{
		schedules[time].RR = s;
		//std::cout << s << JOB[0].arrival << std::endl;
		time++;

		
	}
	time = JOB[0].arrival;
	int count = 0;
	for (int i = JOB[0].arrival; i < fifo_list.size(); i++)
	{
		std::cout << time << "\t |" << schedules[count].FIFO << "\t |" << schedules[count].SJF << "\t |" << schedules[count].STTC << "\t |" << schedules[count].RR << std::endl;
		time++;
		count++;
	}


}

void JobClass::RR(std::list<Jobs> joblist, int tick)
{
	int Slice = 5;
	std::cout << "Running RR" << std::endl;
	std::cout << " " << std::endl;
	JobClass::resetJobs();
	int count = 0, jobNumber = 0, smallest = JOB[0].duration;
	int jobToPrint = 0;
	bool print = false;
	tick = 0;
	int end = joblist.size();
	while (end > 0)
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

		//Look for nex
		if (count > 1)
		{
			if (Slice >= 5)
			{
				
				for (int i = 0; i < count -1; i++)
				{
					//find next in RR Que
					if (JOB[i].arrival < smallest)
					{
						if (JOB[i].arrival > 0 && JOB[i].duration > 0)
						{
							smallest = JOB[i].arrival;
							jobToPrint = i;
						}
					}
				}
			}
			if (JOB[jobToPrint].duration != 0)
			{
				//std::cout << "Elapsed time " << tick << " Job: [" << JOB[jobToPrint].name << "] Running, time remaining = " << JOB[jobToPrint].duration-- << " ARRIVAL: " << JOB[jobToPrint].arrival << std::endl;
				JOB[jobToPrint].duration--;
				Slice--;
				rr_list.push_back(JOB[jobToPrint].name);
			}
			else
			{
				//smallest needs to change to a large number
				smallest = 200;
				//std::cout << " JOB: " << JOB[jobToPrint].name << " * Completed";
				//std::cout << "" << std::endl;
				Slice = 0;
				end = end - 1;
			}
		}
		else if (count >= 1)
		{
			if (Slice <= 5)
			{
				//std::cout << "Elapsed time " << tick << " Job: [" << JOB[count - 1].name << "] Running, time remaining = " << JOB[count - 1].duration-- << std::endl;
				JOB[count - 1].duration--;
				Slice--;
				rr_list.push_back(JOB[count - 1].name);
			}
		}

		if (print)
		{
			//std::cout << " JOB: " << JOB[jobNumber].name << " *ARRIVED*" << std::endl;
			print = false;
		}

		if (Slice < 1)
		{
			JOB[jobToPrint].arrival = JOB[jobToPrint].arrival + 5;
			Slice = 5;
			smallest = 1000;
		}

		//Need to remove need for this when nothing is printed

		tick++;
	}
	JobClass::resetJobs();
}

void JobClass::SJF(std::list<Jobs> joblist, int tick)
{
	//std::cout << "Running SJF" << std::endl;
	//std::cout << " " << std::endl;
	JobClass::resetJobs();
	int current; bool printing = false;
	int count = 0, jobNumber = 0;
	int smallest = rand();
	bool print = false;
	int end = joblist.size();
	while (end > 0)
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
		//std::cout << " JOB: " << JOB[jobNumber].name << " *ARRIVED*" << std::endl;
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
			if (JOB[current].duration > 0)
			{
				//std::cout << "Elapsed time " << tick << " Job: [" << JOB[current].name << "] Running, time remaining = " << JOB[current].duration-- << std::endl;
				JOB[current].duration--;
				sjf_list.push_back(JOB[current].name);
			}
			else
			{
				//std::cout << " JOB: " << JOB[current].name << " * Completed" << std::endl;
				end = end - 1;
				smallest = 10000;
				printing = false;
			}
		}

		//std::cout << end << std::endl;
		tick++;
	}

}

void JobClass::STTC(std::list<Jobs> joblist, int tick)
{
	//std::cout << "Running STTC" << std::endl;
	//std::cout << " " << std::endl;
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
				//std::cout << " JOB: " << JOB[jobToPrint].name << " * Completed";
				//std::cout << "" << std::endl;
				joblist.pop_back();
			}
			else
			{
				//std::cout << "Elapsed time " << tick << " Job: [" << JOB[jobToPrint].name << "] Running, time remaining = " << JOB[jobToPrint].duration-- << std::endl;
				JOB[jobToPrint].duration--;

				stcf_list.push_back(JOB[jobToPrint].name);
			}
		}
		else if (count >= 1)
		{
			//std::cout << "Elapsed time " << tick << " Job: [" << JOB[count - 1].name << "] Running, time remaining = " << JOB[count - 1].duration-- << std::endl;
			JOB[count - 1].duration--;
			stcf_list.push_back(JOB[count - 1].name);
		}
		

		if (print)
		{
			//std::cout << " JOB: " << JOB[jobNumber].name << " *ARRIVED*" << std::endl;
			print = false;
		}

		//Need to remove need for this when nothing is printed

		tick++;
	}
}

void JobClass::FIFO(std::list<Jobs> joblist, int tick)
{
	//std::cout << "Running FIFO" << std::endl;
	//std::cout << " " << std::endl;
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
			//std::cout << "Elapsed time " << tick << " Job: [" << JOB[count].name << "] Running, time remaining = " << JOB[count].duration--;
			JOB[count].duration--;

			//fifo_list.push_front(JOB[count].name + " " + JOB[jobNumber].name + "* Arrived");


			fifo_list.push_back(JOB[count].name);

			if (JOB[count].duration < 1)
			{
				count++;
				//std::cout << " JOB: " << JOB[count].name << " * Completed";
				//std::cout << "" << std::endl;
			}

		}

		if (print)
		{
			//std::cout << " JOB: " << JOB[jobNumber].name << " *ARRIVED*";
			print = false;
		}

		//Need to remove need for this when nothing is printed
		//std::cout << "" << std::endl;

		tick++;
	}

	//std::cout << "All Jobs have finished" << "\n" << std::endl;


}