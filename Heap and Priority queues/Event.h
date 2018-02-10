#ifndef __EVENT_H_INCLUDED__
#define __EVENT_H_INCLUDED__

#include <iostream>

class Event
{
public:
	Event();
	Event(short hour, const char* description);
	Event(const Event&);
	~Event();

	Event& operator=(const Event&);

	short getHour()const;
	const char* getDescription()const;

	void setHour(short);
	void setDescription(const char*);

private:
	short hour;
	const char* description;

private:
	void init(short, const char*);
};

bool operator<(const Event&, const Event&);
std::ostream& operator<<(std::ostream& out, const Event&);
#endif //__EVENT_H_INCLUDED__