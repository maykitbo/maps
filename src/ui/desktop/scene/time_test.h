#pragma once


#include <chrono>
#include <iostream>


namespace maykitbo
{


template<class Unit = std::chrono::milliseconds>
class TimeTest
{
    public:
        using time_p = std::chrono::_V2::system_clock::time_point;
        using dur_t = std::chrono::duration<float>;

        TimeTest(std::string name = "Time Test") :
            point_(getTime()),
            period_{0},
            name_(name)
        {}
        void stop()
        {
            period_ = dur_t{0};
        }
        void pause()
        {
            period_ += getTime() - point_;
        }
        void resume()
        {
            point_ = getTime();
        }
        friend TimeTest operator+(const TimeTest& a, const TimeTest& b)
        {
            TimeTest r(a.name_ + " + " + b.name_);
            r.period_ = a.period_ + b.period_;
            return r;
        }
        friend std::ostream& operator<<(std::ostream& os, const TimeTest<Unit>& tt)
        {
            os << "Time Test for \"" << tt.name_ << "\" = ";
            os << std::chrono::duration_cast<Unit>(tt.period_).count();
            os << " " << tt.unitName() << "\n";
            return os;
        }
    private:
        time_p point_;
        dur_t period_;
        std::string name_;
        time_p getTime() const
        {
            return std::chrono::high_resolution_clock::now();
        }
        std::string unitName() const
        {
            if constexpr (std::is_same_v<Unit, std::chrono::milliseconds>)
                return "ms";
            else if constexpr (std::is_same_v<Unit, std::chrono::seconds>)
                return "s";
            else if constexpr (std::is_same_v<Unit, std::chrono::microseconds>)
                return "us";
            else if constexpr (std::is_same_v<Unit, std::chrono::nanoseconds>)
                return "ns";
            else
                return "unknown unit";
        }
};


} // namespace maykitbo
