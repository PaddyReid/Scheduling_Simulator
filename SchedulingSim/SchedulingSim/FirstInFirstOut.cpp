#include "Scheduler.hpp"


void Scheduler::addJobs(std::list<Jobs> myList)
{
	int i = 0;
	for (auto v : myList)
	{
		shedule[i].name = v.name;
		shedule[i].arrival = v.arrival;
		shedule[i].duration = v.duration;
		i++;
	}
}

std::list<std::string>	Scheduler::fifo_getCompleted()
{
	return fifo_completed;
}



std::list<std::string> Scheduler::FirstInFirstOut(std::list<Jobs> joblist, int tick)
{

	//std::cout << "Running FIFO" << std::endl;
	//std::cout << " " << std::endl;
	Scheduler::addJobs(joblist);
	int count = 0, jobNumber = 0;
	bool print = false;
	//We know jobs are in order according to their arrival time
	fifo_completed.push_back("");
	while (shedule[4].duration > 0)
	{
		//Check for arrivals
		for (int i = 0; i < joblist.size() - 1; i++)
		{
			if (shedule[i].arrival == tick)
			{
				//fifo_completed.push_back(shedule[jobNumber].name + " ARRIVED");
				jobNumber = i;
				print = true;
				break;

			}

			if (print)
			{
				
				print = false;
			}
		}

		if (shedule[count].arrival <= tick)
		{
			shedule[count].duration--;

			//fifo_list.push_front(JOB[count].name + " " + JOB[jobNumber].name + "* Arrived");
			
			fifo_list.push_back(shedule[count].name);
			

			if (shedule[count].duration == 1)
			{
				fifo_completed.push_back(" *FIFO. " + shedule[count].name + " COMPLETED");
			}
			else
			{
				fifo_completed.push_back("");
			}

			if (shedule[count].duration < 1)
			{
				count++;
			}


		}

		if (print)
		{
			print = false;
		}
		tick++;
	}


	return fifo_list;
}
