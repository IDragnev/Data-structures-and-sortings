#include "Event.h"


short Event::getHour()const
{
	return hour;
}


const char* Event::getDescription()const
{
	return description;
}


void Event::setHour(short hour)
{
	if (hour > 0 && hour < 25)
		this->hour = hour;
	else
		throw std::invalid_argument("Hour must be between 1 and 24");
}



void Event::setDescription(const char* description)
{
	if (!description)
		throw std::invalid_argument("Description must be a valid string!");

	int size = strlen(description) + 1;

	char* buff = new char[size];
	strcpy_s(buff, size, description);

	delete[] this->description;
	this->description = buff;
}



void Event::init(short hour, const char* descr)
{
	setHour(hour);
	setDescription(descr);
}


Event::Event(short hour, const char* description)
	:
	description(nullptr)
{
	init(hour, description);
}



Event::Event(const Event& other)
	:
	description(nullptr)
{
	init(other.hour, other.description);
}



Event& Event::operator=(const Event& other)
{
	if (this != &other)
	{
		init(other.hour, other.description);
	}

	return *this;
}


Event::Event()
	:
	hour(12),
	description(nullptr)
{
	setDescription("No description");
}


Event::~Event()
{
	delete[] description;
}


std::ostream& operator<<(std::ostream& out, const Event& event)
{
	out
		<< "To do: " << event.getDescription()
		<< " at " << event.getHour() << " o'clock.";

	return out;
}


bool operator<(const Event& ev1, const Event& ev2)
{
	return ev1.getHour() < ev2.getHour();
}