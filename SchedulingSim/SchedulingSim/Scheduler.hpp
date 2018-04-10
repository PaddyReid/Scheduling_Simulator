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

	std::list<float>				sendStats_FIFO();
	std::list<float>				sendStats_SJF();
	std::list<float>				sendStats_STCF();
	std::list<float>				sendStats_RR();
	std::list<float>				sendStats_RRT();

	std::list<float>				getFIFOResponse();
	std::list<float>				getSJFResponse();
	std::list<float>				getSTCFResponse();
	std::list<float>				getRResponse();
	std::list<float>				getRRTesponse();

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

	std::list<float>				sjf_stats;
	std::list<float>				fifo_stats;
	std::list<float>				stcf_stats;
	std::list<float>				rr_stats;
	std::list<float>				rrt_stats;

private:
	int								shortest;
	int								isBigger;
	sheduling						shedule[5];
	float							average;

	float							turnAround;
	float							response;

};
