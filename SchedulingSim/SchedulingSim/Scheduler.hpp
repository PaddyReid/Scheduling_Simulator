#include "Job.hpp"

#include <iostream>
#include <string>
#include <list>


struct sheduling
{
	std::string name;
	int arrival;
	int duration;

	int turnaround;
	int waittime;
	int response;

	bool operator <(const sheduling & playerObj) const
	{
		return arrival < playerObj.arrival;
	}
};

class Scheduler : public Job
{

public:
	void							addJobs(std::list<Jobs>);

	std::list<std::string>			FirstInFirstOut(std::list<Jobs> joblist, int tick);
	std::list<std::string>			ShortestTimeToCompletion(std::list<Jobs> joblist, int tick);
	std::list<std::string>			ShortestJobFirst(std::list<Jobs> joblist, int tick);
	std::list<std::string>			RoundRobin(std::list<Jobs> joblist, int tick);
	std::list<std::string>			RoundRobinTwo(std::list<Jobs> joblist, int tick);

	std::list<int>					sendStats_FIFO();
	std::list<int>					sendStats_SJF();
	std::list<int>					sendStats_STCF();
	std::list<int>					sendStats_RR();
	std::list<int>					sendStats_RRT();

	std::list<std::string>			getCompleted();
	std::list<std::string>			fifo_getCompleted();
	std::list<std::string>			stcf_getCompleted();
	std::list<std::string>			rr_getCompleted();
	std::list<std::string>			rrt_getCompleted();

	std::list<std::string>			fifo_list;
	std::list<std::string>			sjf_list;
	std::list<std::string>			stcf_list;
	std::list<std::string>			rr_list;
	std::list<std::string>			rrTwo_list;

	std::list<std::string>			completed;
	std::list<std::string>			fifo_completed;
	std::list<std::string>			stcf_completed;
	std::list<std::string>			rr_completed;
	std::list<std::string>			rrt_completed;

	std::list<int>					sjf_stats;
	std::list<int>					fifo_stats;
	std::list<int>					stcf_stats;
	std::list<int>					rr_stats;
	std::list<int>					rrt_stats;

private:
	int								shortest;
	int								isBigger;
	sheduling						shedule[5];
	float							average;

};
