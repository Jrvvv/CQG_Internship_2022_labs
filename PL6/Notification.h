#pragma once
#include <string>
#include <chrono>



class Notification {
public:
    Notification() = default;

    Notification(int seconds, const std::string& message);

    int duration();

    std::chrono::steady_clock::time_point startTime();

    std::string message();

    bool isInList();

    void set_inList(bool b);

    int posInList() { return m_posInList;}

    void set_posInList(int pos) { m_posInList = pos; }

private:
    bool m_isInList = true;
    int m_posInList;
    std::chrono::steady_clock::time_point m_startTime;
    int m_duration;
    std::string m_message;
};

