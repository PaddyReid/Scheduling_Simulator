
#include "JobClass.hpp"
#include "Scheduler.hpp"

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

	//RUN JOB FIFO

	//RUN JOB SJF

	//RUN JOB STTO

	//RUN JOB RR


	std::cout << JOB_STACK.size() << std::endl;



}

void JobClass::incrementTick()
{

}


void JobClass::createJobs()
{
	// **Manually seeting up Jobs**

	//Job one's information
	JOB[0].name = "A";
	JOB[0].arrival = 21;
	JOB[0].duration = 34;

	////Job two's information
	JOB[1].name = "B";
	JOB[1].arrival = 84;
	JOB[1].duration = 53;

	////Job three's information
	JOB[2].name = "C";
	JOB[2].arrival = 49;
	JOB[2].duration = 64;

	////Job four's information
	JOB[3].name = "D";
	JOB[3].arrival = 8;
	JOB[3].duration = 23;

	////Job five's information
	JOB[4].name = "E";
	JOB[4].arrival = 23;
	JOB[4].duration = 63;

	//Printing Jobs to see what goes into each schedule
	std::cout << "JOB LIST" << std::endl;
	for (int i = 0; i < 5; i++)
	{

		std::cout << JOB[i].name << " " << JOB[i].arrival << " " << JOB[i].duration << std::endl;

		//Adding Job arrival time to stack
		JOB_STACK.push(JOB[i].arrival);
	}
}