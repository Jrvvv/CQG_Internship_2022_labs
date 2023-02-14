#include "Notification.h"

Notification::Notification(int seconds, const std::string& message) : m_duration(seconds),
m_message(message),
m_startTime(std::chrono::steady_clock::now())
{}

int Notification::duration()
{
    return m_duration;
}

std::chrono::steady_clock::time_point Notification::startTime()
{
    return m_startTime;
}

std::string Notification::message()
{
    return m_message;
}

bool Notification::isInList()
{
    return m_isInList;
}

void Notification::set_inList(bool b)
{
    m_isInList = b;
}