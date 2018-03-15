#include "Scheduler.hpp"

std::list<std::string>	Scheduler::stcf_getCompleted()
{
	return stcf_completed;
}

std::list<std::string>	Scheduler::ShortestTimeToCompletion(std::list<Jobs> joblist, int tick)
{
	Scheduler::addJobs(joblist);
	int count = 0, jobNumber = 0, smallest = shedule[0].duration;
	int jobToPrint = 0; stcf_completed.push_back("");
	bool print = false;
	tick = 0;
	while (joblist.size() > 0)
	{
		//Check for arrivals
		for (int i = 0; i < 5; i++)
		{
			if (shedule[i].arrival == tick)
			{
				jobNumber = i;
				print = true;
				count++;
				break;
			}
		}
		if (print)
		{
			print = false;
			//stcf_list.push_back("ARRIVED : [" + shedule[jobNumber].name + "]");
		}

		//Look for smallest
		if (count > 1)
		{
			for (int i = 0; i < count; i++)
			{
				if (shedule[i].duration < smallest)
				{
					if (shedule[i].duration != 0)
					{
						smallest = shedule[i].duration;
						jobToPrint = i;
					}
				}
			}
			if (shedule[jobToPrint].duration < 1)
			{
				//smallest needs to chage to a large number
				smallest = 200;
				//stcf_list.push_back("COMPLETED : [" + shedule[jobToPrint].name + "]");
				stcf_completed.push_back(" *STCF. " + shedule[jobToPrint].name + " COMPLETED");
				joblist.pop_back();

			}
			else
			{
				if (shedule[jobToPrint].duration > 1)
				{
					stcf_completed.push_back("");
				}
				
				shedule[jobToPrint].duration--;
				stcf_list.push_back(shedule[jobToPrint].name);
			}
		}
		else if (count >= 1)
		{
			shedule[count - 1].duration--;
			stcf_list.push_back(shedule[count - 1].name);
		}
		tick++;
	}

	return stcf_list;
}