#pragma once

namespace StyyxUtil {
	struct TimerUtil{
        class Timer
        {
        public:
            void Start()
            {
                if (!running) {
                    startTime = std::chrono::steady_clock::now();
                    running = true;
                }
            }

            void Stop()
            {
                running = false;
            }

            void Reset()
            {
                startTime = std::chrono::steady_clock::now();
            }

            double ElapsedSeconds() const
            {
                if (!running) {
                    return 0.0;
                }
                auto now = std::chrono::steady_clock::now();
                return std::chrono::duration<double>(now - startTime).count();
            }

            bool IsRunning() const
            {
                return running;
            }

        private:
            std::chrono::steady_clock::time_point startTime{};
            bool running{ false };
        };
	};
}
