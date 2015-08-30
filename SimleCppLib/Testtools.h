#ifndef TESTTOOLS_H
#define TESTTOOLS_H

#include <chrono>
#include <ctime>
#include <exception>
#include <iostream>
#include <memory>
#include <ratio>
#include <utility>

#include <Windows.h>
#include <Psapi.h>
#pragma comment(lib, "psapi.lib")

//////////////////////Copy from TinySTL////////////////////////////////////
namespace LSTL{
	namespace Profiler{

		class ProfilerInstance{
		public:
			typedef std::chrono::steady_clock SteadyClock;
			typedef SteadyClock::time_point TimePoint;
			typedef std::chrono::duration<double, std::ratio<1, 1>> DurationTime;//µ•Œª√Î
			enum class MemoryUnit{ KB_, MB_, GB_ };
		private:
			#define KB / 1024
			#define MB KB / 1024
			#define GB MB / 1024
		private:
			static DurationTime duringTime;
			static TimePoint startTime;
			static TimePoint finishTime;
		public:
			static void start(){
				startTime = SteadyClock::now();
			}
			static void finish(){
				finishTime = SteadyClock::now();
				duringTime = std::chrono::duration_cast<DurationTime>(finishTime - startTime);
			}
			static void dumpDuringTime(std::ostream& os = std::cout){
				os << "total " << duringTime.count() * 1000 << " milliseconds" << std::endl;
			}
			static double second(){
				return duringTime.count();
			}
			static double millisecond(){
				return duringTime.count() * 1000;
			}
			static size_t memory(MemoryUnit mu = MemoryUnit::KB_){
				size_t memory = 0;
				PROCESS_MEMORY_COUNTERS pmc;
				HANDLE hProcess = GetCurrentProcess();
				if (!GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
					throw std::runtime_error("GetProcessMemoryInfo failed");
				CloseHandle(hProcess);

				switch (mu){
				case MemoryUnit::KB_:
					memory = pmc.WorkingSetSize KB;
					break;
				case MemoryUnit::MB_:
					memory = pmc.WorkingSetSize MB;
					break;
				case MemoryUnit::GB_:
					memory = pmc.WorkingSetSize GB;
					break;
				}
				return memory;
			}
		};
	}
}

#endif