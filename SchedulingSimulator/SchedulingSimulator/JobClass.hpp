#include <iostream>

class JobClass
{
public:
	JobClass();

private:
	//Job Variables -required for each job-
	std::string			JOB_NAME;
	int					ARRIVAL_TIME;
	int					DURATION;

};