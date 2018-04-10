#include "Scheduler.hpp"


void Scheduler::addJobs(std::list<Jobs> myList)
{
	int i = 0;
	for (Jobs v : myList)
	{
		shedule[i].name = v.name;
		shedule[i].arrival = v.arrival;
		shedule[i].duration = v.duration;
		i++;
	}
}

std::list<float> Scheduler::sendStats_FIFO()
{
	return fifo_stats;
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
				shedule[i].response = tick + shedule[count].waittime;
				shedule[i].waittime = shedule[count].waittime + tick;
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
			//std::cout << shedule[count].name << std::endl;
			fifo_list.push_back(shedule[count].name);


			if (shedule[count].duration == 1)
			{
				//calculations

				//turn around time
				turnAround = tick - shedule[count].arrival;
				fifo_stats.push_back(turnAround);

				//arival until it gets called;
				//response = 

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


std::list<std::string>	Scheduler::rr_getCompleted()
{
	return rr_completed;
}
std::list<std::string>	Scheduler::rrt_getCompleted()
{
	return rrt_completed;
}

std::list<float> Scheduler::sendStats_RR()
{
	return rr_stats;
}

std::list<float> Scheduler::sendStats_RRT()
{
	return rrt_stats;
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
				rr_completed.push_back("");
				rr_list.push_back(shedule[jobToPrint].name);
			}
			else
			{
				//smallest needs to change to a large number
				smallest = 200;
				Slice = 0;
				end = end - 1;

				turnAround = tick - shedule[jobToPrint].arrival;
				rr_stats.push_back(turnAround);

				rr_completed.push_back(" *RR. " + shedule[jobToPrint].name + " COMPLETED");
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
				rrt_completed.push_back("");
			}
			else
			{
				//smallest needs to change to a large number
				smallest = 200;
				Slice = 0;
				end = end - 1;

				turnAround = tick - shedule[jobToPrint].arrival;
				rrt_stats.push_back(turnAround);

				rr_completed.push_back(" *RRT. " + shedule[jobToPrint].name + " COMPLETED");
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

std::list<std::string> Scheduler::getCompleted()
{
	return completed;
}

std::list<float> Scheduler::sendStats_SJF()
{
	return sjf_stats;
}

//float Scheduler::getFIFOResponse()
//{
//	return response;
//}

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
				//sjf_list.push_back(shedule[current].name + " COMPLETED")


				turnAround = tick - shedule[current].arrival;
				sjf_stats.push_back(turnAround);

				completed.push_back(" *SJF. " + shedule[current].name + " COMPLETED");
				end = end - 1;
				smallest = 10000;
				printing = false;
			}
		}
		tick++;
	}


	return sjf_list;
}

std::list<std::string>	Scheduler::stcf_getCompleted()
{
	return stcf_completed;
}

std::list<float> Scheduler::sendStats_STCF()
{
	return stcf_stats;
}

std::list<std::string>	Scheduler::ShortestTimeToCompletion(std::list<Jobs> joblist, int tick)
{
	stcf_completed.push_back("");
	stcf_completed.push_back("");
	Scheduler::addJobs(joblist);
	int count = 0, jobNumber = 0, smallest = shedule[0].duration;
	int jobToPrint = 0; stcf_completed.push_back("");
	bool print = false;
	tick = 0;
	while (joblist.size() > 0)
	{
		//Check for arrivals
		for (int i = 0; i < 10; i++)
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

				turnAround = tick - shedule[jobToPrint].arrival;
				stcf_stats.push_back(turnAround);

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