#pragma once

namespace StyyxUtil {
	struct TimerUtil {
		/// <summary>
		/// Timer Class 
		/// mainly used for doing stuff after x time
		/// </summary>
		class Timer
		{
		public:

			/// <summary>
			/// Start Timer
			/// </summary>
			void Start()
			{
				if (!running) {
					startTime = std::chrono::steady_clock::now();
					running = true;
				}
			}
			/// <summary>
			/// Stop Timer
			/// </summary>
			void Stop()
			{
				running = false;
			}
			/// <summary>
			/// Restart Timer
			/// </summary>
			void Reset()
			{
				startTime = std::chrono::steady_clock::now();
			}
			/// <summary>
			/// Returns the amount of time the timer is running already
			/// </summary>
			/// <returns></returns>
			double ElapsedSeconds() const
			{
				if (!running) {
					return 0.0;
				}
				auto now = std::chrono::steady_clock::now();
				return std::chrono::duration<double>(now - startTime).count();
			}
			/// <summary>
			/// checks if timer is running
			/// </summary>
			/// <returns></returns>
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
