#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>

#include <string>
#include <vector>
#include <chrono>

#include <windows.h> 

#include <thread>
#include <mutex>
#include <future>

#include "Notification.h"

using namespace std::chrono_literals;

std::vector<Notification> g_notif;

std::condition_variable cv;

std::mutex g_mForVec;
std::mutex g_mPrint;

bool endOfWork;         //if detach() thread -- error when exit

//create a thread for a messagebox and show the message
void showMessage(const std::string& message)
{

    std::thread th([message]()
        {
            std::wstring widestr = std::wstring(message.begin(), message.end());
            const wchar_t* widecstr = widestr.c_str();
            MessageBox(NULL, (LPCWSTR)(widecstr), (LPCWSTR)L"Notification", NULL);
        });

    if (th.joinable())
        th.detach();

    std::unique_lock<std::mutex> printLocker(g_mPrint);

}

// checking in loop time to show message
void checkNotifications() {
    std::vector<int> toDelete;
    while(true)
    {
        
        std::unique_lock<std::mutex> locker(g_mForVec);         
        cv.wait(locker, []() 
            { 
                return !g_notif.empty(); 
            });                                      //waiting addin notif in empty vector
        locker.unlock();

        while (!g_notif.empty()) {
            
            int pos = 0;

            locker.lock();

            for (auto i : g_notif)
            {
                auto now = std::chrono::steady_clock::now();
                int passedTime = std::chrono::duration_cast<std::chrono::seconds>(now - i.startTime()).count();
                if (i.duration() <= passedTime)
                {
                    showMessage(i.message());

                    toDelete.push_back(pos);

                }
                pos++;
            }

            for (auto i : toDelete)
            {
                g_notif.erase(g_notif.begin() + i);
            }
            locker.unlock();
            toDelete.clear();

            if (endOfWork)              // the same crutch because of crushin with detach()
                break;
        }

        if (endOfWork)                  // the same crutch because of crushin with detach()
            break;
    }
}

void New(int delay, const std::string& message)
{
    std::unique_lock<std::mutex> locker(g_mForVec);
    g_notif.push_back(Notification(delay, message));
    cv.notify_one();
}

void List()
{
    std::unique_lock<std::mutex> locker(g_mForVec);

    if (g_notif.empty())
    {
        std::unique_lock<std::mutex> printLocker(g_mPrint);
        std::cout << "List is empty" << std::endl;
    }
    else
    for (int i = 0; i < g_notif.size(); i++)
    {
        auto now = std::chrono::steady_clock::now();
        int passedTime = std::chrono::duration_cast<std::chrono::seconds>(now - g_notif[i].startTime()).count();

        g_notif[i].set_posInList(i + 1);

        std::unique_lock<std::mutex> printLocker(g_mPrint);
        std::cout
            << std::setw(3) << i + 1 << "."
            << std::setw(50) << g_notif[i].message()
            << " ( in " << g_notif[i].duration() - passedTime << " seconds)"
            << std::endl;
    }
}

void Cancel(int index)
{   
    if (index < 0)
    {
        std::unique_lock<std::mutex> printLocker(g_mPrint);
        std::cout << "There is no notification with index " << index << " in the list";
    }
    else if (g_notif.empty())
    {
        std::unique_lock<std::mutex> printLocker(g_mPrint);
        std::cout << "There is no notifications in the list";
    }
    else
    {   
        bool isFound = false;

        std::unique_lock<std::mutex> locker(g_mForVec);
        for (int i = 0; i < g_notif.size(); i++) 
        {
            if (g_notif[i].posInList() == index) 
            {
                g_notif.erase(g_notif.begin() + i);
                isFound = true;
                break;
            }
        }
        locker.unlock();

        if(isFound) {
            std::unique_lock<std::mutex> printLocker(g_mPrint);
            std::cout << "message " << index << " is successfully deleted" << std::endl;
        }
        else 
        {
            std::unique_lock<std::mutex> printLocker(g_mPrint);
            std::cout << "There is no message with id " << index << std::endl;
        }
    }
}

void Exit()
{
    endOfWork = true;
}

enum class CommandType
{
    None,
    New,
    List,
    Cancel,
    Exit
};

struct Command
{
    CommandType type{};
    int delay{};
    std::string message;
    int index{};

    Command() = default;
    Command(CommandType type) : type(type) {}
    Command(CommandType type, int delay, const std::string& message) : type(type), delay(delay), message(message) {}
    Command(CommandType type, int index) : type(type), index(index) {}
};

Command ReadCommand()
{
    std::string input;
    std::getline(std::cin, input);

    std::stringstream parser(input);
    std::string command;
    if (parser >> command)
    {
        if (command == "exit" || command == "x")
            return Command(CommandType::Exit);
        else if (command == "list" || command == "l")
            return Command(CommandType::List);
        else if (command == "cancel" || command == "c")
        {
            int index = 0;
            if (parser >> index)
                return Command(CommandType::Cancel, index);
            else
            {
                std::cerr << "Usage: cancel index" << std::endl
                    << "   index : index of the item to remove" << std::endl;
            }
        }
        else if (command == "new" || command == "n")
        {
            int delay = 0;
            if (parser >> delay)
            {
                if (delay > 0)
                {
                    std::string message;
                    std::getline(parser, message);
                    if (!message.empty())
                        message = message.substr(1);
                    return Command(CommandType::New, delay, message);
                }
                else
                    std::cerr << "Delay must be positive" << std::endl;
            }
            else
            {
                std::cerr << "Usage: new delay message" << std::endl
                    << "   delay   : positive delay in seconds" << std::endl
                    << "   message : message to show without quotes" << std::endl;
            }
        }
        else
        {
            std::cerr << "Unknown command" << std::endl;
        }
    }

    return Command(CommandType::None);
}

int main()
{
    std::cout
        << "Commands:" << std::endl
        << "   new <delay> <message>" << std::endl
        << "      Schedule a notification with given message and delay in seconds" << std::endl
        << "      delay   : positive delay in seconds" << std::endl
        << "      message : message to show without quotes" << std::endl
        << "   list" << std::endl
        << "      Show the list of active notifications" << std::endl
        << "   cancel <index>" << std::endl
        << "      Cancel active notification with given index" << std::endl
        << "      index   : index in the previously shown list" << std::endl
        << "   exit" << std::endl
        << "      Exit application" << std::endl;

    
    std::thread th(checkNotifications);
    endOfWork = false;

    while (true)
    {   
        std::unique_lock<std::mutex> printLocker(g_mPrint);
        std::cout << std::endl << "> ";
        printLocker.unlock();
        const auto command = ReadCommand();
        switch (command.type)
        {
        case CommandType::None:
            continue;
        case CommandType::Exit:
            Exit();
            th.join();
            return 0;
        case CommandType::New:
            New(command.delay, command.message);
            break;
        case CommandType::List:
            List();
            break;
        case CommandType::Cancel:
            Cancel(command.index);
            break;
        default:
            assert(0);
        }
    }
}