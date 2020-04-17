#include <stdio.h>
#include <chrono>
#include <ctime>
#include <utility>
#include <string>

using namespace std;
using namespace std::chrono;

class TimerClass {
    system_clock::time_point *start;
    string name;
public:
    TimerClass(const string& name) {
        start = new system_clock::time_point(system_clock::now());
        this->name = name;
    }

    ~TimerClass() {
        if(start) {
            system_clock::time_point end = system_clock::now();

            duration<double> elapsed_seconds = end - *start;
            time_t end_time = system_clock::to_time_t(end);

            printf("Name: %s\nTime now: %sElapsed = %lg\n", name.c_str(), ctime(&end_time), elapsed_seconds.count());
            delete start;
        }
    }

    TimerClass(const TimerClass& other) {
        printf("Copy constructor\n");
        start = new system_clock::time_point(other.start->time_since_epoch());
        name = other.name;
    }

    TimerClass(TimerClass&& other) noexcept : start(other.start), name(other.name) {
        printf("Move constructor\n");
        other.name = "";
        other.start = nullptr;
    }

    TimerClass& operator=(const TimerClass& other) {
        printf("Copy operator\n");
        if (this == &other) return *this;
        start = new system_clock::time_point(other.start->time_since_epoch());
        name = other.name;
        return *this;
    }

    TimerClass& operator=(TimerClass&& other) noexcept {
        printf("Move operator\n");
        if (this == &other) return *this;
        start = other.start;
        name = other.name;
        other.name = "";
        other.start = nullptr;
        return *this;
    }

    void SetName(const string& new_name) {
        name = new_name;
    }
};

int main() {
    TimerClass timer_a("A");
    TimerClass timer_b(timer_a);
    timer_b.SetName("B");
    TimerClass timer_c = timer_a;
    timer_c.SetName("C");
    TimerClass timer_d = move(timer_c);
    timer_d.SetName("D");
    return 0;
}