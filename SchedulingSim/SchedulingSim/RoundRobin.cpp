#include "Scheduler.hpp"

std::list<std::string>	Scheduler::rr_getCompleted()
{
	return rr_completed;
}
std::list<std::string>	Scheduler::rrt_getCompleted()
{
	return rrt_completed;
}

std::list<std::string> Scheduler::RoundRobin(std::list<Jobs> joblist, int tick)
{
	int Slice = 5;
	Scheduler::addJobs(joblist);
	int count = 0, jobNumber = 0, smallest = shedule[0].duration;
	int jobToPrint = 0;
	bool print = false;
	tick = 0; rr_completed.push_back("");
	int end = joblist.size();
	while (end > 0)
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

		//Look for nex
		if (count > 1)
		{
			if (Slice >= 5)
			{

				for (int i = 0; i < count - 1; i++)
				{
					//find next in RR Que
					if (shedule[i].arrival < smallest)
					{
						if (shedule[i].arrival > 0 && shedule[i].duration > 0)
						{
							smallest = shedule[i].arrival;
							jobToPrint = i;
						}
					}
				}
			}
			

			if (shedule[jobToPrint].duration != 0)
			{
				shedule[jobToPrint].duration--;
				Slice--;
				//rr_completed.push_back("");
				rr_list.push_back(shedule[jobToPrint].name);
			}
			else
			{
				//smallest needs to change to a large number
				smallest = 200;
				Slice = 0;
				end = end - 1;
				//rr_completed.push_back(" *RR. " + shedule[jobToPrint].name + " COMPLETED");
			}
				
			
		}
		else if (count >= 1)
		{
			if (Slice <= 5)
			{
				shedule[count - 1].duration--;
				Slice--;
				rr_list.push_back(shedule[count - 1].name);
			}
		}

		if (print)
		{
			print = false;
		}

		if (Slice < 1)
		{
			shedule[jobToPrint].arrival = shedule[jobToPrint].arrival + 5;
			Slice = 5;
			smallest = 1000;
		}
		tick++;
	}

	return rr_list;
}


std::list<std::string> Scheduler::RoundRobinTwo(std::list<Jobs> joblist, int tick)
{
	int Slice = 3;
	Scheduler::addJobs(joblist);
	int count = 0, jobNumber = 0, smallest = shedule[0].duration;
	int jobToPrint = 0;
	bool print = false;
	tick = 0;
	int end = joblist.size();
	while (end > 0)
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
			//rrTwo_list.push_back("ARRIVED : [" + shedule[jobNumber].name + "]");
		}
		//Look for nex
		if (count > 1)
		{
			if (Slice >= 3)
			{

				for (int i = 0; i < count - 1; i++)
				{
					//find next in RR Que
					if (shedule[i].arrival < smallest)
					{
						if (shedule[i].arrival > 0 && shedule[i].duration > 0)
						{
							smallest = shedule[i].arrival;
							jobToPrint = i;
						}
					}
				}
			}
			if (shedule[jobToPrint].duration != 0)
			{
				shedule[jobToPrint].duration--;
				Slice--;
				rrTwo_list.push_back(shedule[jobToPrint].name);
			}
			else
			{
				//smallest needs to change to a large number
				smallest = 200;
				Slice = 0;
				end = end - 1;
			}
		}
		else if (count >= 1)
		{
			if (Slice <= 3)
			{
				shedule[count - 1].duration--;
				Slice--;
				rrTwo_list.push_back(shedule[count - 1].name);
			}
		}

		

		if (Slice < 1)
		{
			shedule[jobToPrint].arrival = shedule[jobToPrint].arrival + 5;
			Slice = 3;
			smallest = 1000;
		}
		tick++;
	}

	return rrTwo_list;
}
