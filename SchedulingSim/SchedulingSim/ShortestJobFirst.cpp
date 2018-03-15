#include "Scheduler.hpp"


std::list<std::string> Scheduler::getCompleted()
{
	return completed;
}

std::list<int> Scheduler::sendStats_SJF()
{
	return sjf_stats;
}

std::list<std::string>	Scheduler::ShortestJobFirst(std::list<Jobs> joblist, int tick)
{
	Scheduler::addJobs(joblist);
	int current; bool printing = false;
	int count = 0, jobNumber = 0;
	int smallest = rand();
	bool print = false;
	float avarage = 0;
	int end = joblist.size();
	while (end > 0)
	{
		//job arrived??
		for (int i = 0; i < 5; i++)
		{
			if (shedule[i].arrival == tick)
			{
				//shedule[i].response = tick + shedule[count].arrival;
				jobNumber = i;
				print = true;
				count++;
				break;
			}
		}

		if (print)
		{
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
					if (shedule[i].duration < smallest)
					{
						if (shedule[i].duration != 0)
						{
							smallest = shedule[i].duration;
							current = i;
							printing = true;
						}
					}
				}
			}
		}

		if (printing)
		{
			if (shedule[current].duration > 1)
			{
				completed.push_back("");
			}
			if (shedule[current].duration > 0)
			{
				shedule[current].duration--;
				sjf_list.push_back(shedule[current].name);
				
			}
			else
			{
				//sjf_list.push_back(shedule[current].name + " COMPLETED");
				shedule[current].turnaround = shedule[current].arrival - tick;
				sjf_stats.push_back(shedule[current].turnaround);
				completed.push_back("*SJF. " + shedule[current].name + " COMPLETED");
				end = end - 1;
				smallest = 10000;
				printing = false;
			}
		}
		tick++;
	}
	

	return sjf_list;
}