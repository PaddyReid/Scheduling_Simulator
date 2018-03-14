#include "Scheduler.hpp"
#include "JobClass.hpp"

Jobs JOB_FIFO[5];

int Scheduler::getJobs()
{
	return 0;
}

void Scheduler::FirstInFirstOut(std::string name, int arrival, int duration, int jobstack, int count, int tick)
{
	if (count < 5)
	{
		//Add files to stack
		JOB_FIFO[count].name = name;
		JOB_FIFO[count].arrival = arrival;
		JOB_FIFO[count].duration = duration;
	}
	else
	{
		count = 0;
		//Run FIFO 
		std::cout << "" << std::endl;
		std::cout << "First in First Out" << tick << std::endl;
		for (int i = 0; i < jobstack; i++)
		{
			while (JOB_FIFO[count].duration > 0)
			{
				//Used to see process of First in forst out
				//std::cout << "Time [" << tick << "] " << "Job: [" << JOB_FIFO[count].name << "] Ticks Remaining: " << JOB_FIFO[count].duration-- << std::endl;
				JOB_FIFO[count].duration--;
				tick++;
			}
			//Printing Jobs as they are completed
			std::cout << "Job: [" << JOB_FIFO[count].name << "] Completed" << std::endl;
			count++;
		}
		//Print final output of first in first out 
		std::cout << "Total Ticks: " << tick << std::endl;
	}
}
