#pragma once

namespace StyyxUtil
{
	/// @brief Timer class used to do x after y time
	/// @par Example
	/// @code
	/// StyyxUtil::TimerUtil timer;
	/// timer.Start();
	/// // check if elapsed
	/// if (timer.Elapsed() >= 5.0) {
	///     // do something
	/// }
	/// @endcode
	struct TimerUtil {


		///@brief Start the timer
		void Start()
		{
			if (!running) {
				startTime = std::chrono::steady_clock::now();
				running = true;
			}
		}
		///@brief Stop the timer
		void Stop()
		{
			running = false;
		}
		///@brief Reset timer. Basically set it back to 0
		void Reset()
		{
			startTime = std::chrono::steady_clock::now();
		}

		/// @brief Get the time the timer runs for
		/// @return double for the elapsed seconds
		[[nodiscard]] double ElapsedSeconds() const
		{
			if (!running) {
				return 0.0;
			}
			const auto now = std::chrono::steady_clock::now();
			return std::chrono::duration<double>(now - startTime).count();
		}

		/// @brief Check if the timer is running or not
		/// @return bool true if the timer is running
		[[nodiscard]] bool IsRunning() const {
			return running;
		}

		/// @brief Start a time for a limited amount of time
		/// @param a_seconds amount of time the timer will run for
		void StartLimited(double a_seconds) {
			limitSeconds = a_seconds;
			limited = true;
			startTime = std::chrono::steady_clock::now();
			running = true;
		}

		/// @brief Check if a limited timer has ran out or not
		/// @return true if the limited timer is run out
		bool IsExpired()
		{
			if (!running || !limited) {
				return false;
			}

			if (ElapsedSeconds() >= limitSeconds) {
				Stop();
				return true;
			}
			return false;
		}

		/// @brief Get the remaining seconds a limited timer runs for
		/// @return double for the remaining seconds a limited timer has left
		[[nodiscard]] double RemainingSeconds() const
		{
			if (!running || !limited) {
				return 0.0;
			}

			return std::max(0.0, limitSeconds - ElapsedSeconds());
		}

	private:
		bool limited{ false };
		double limitSeconds{0.0};
		std::chrono::steady_clock::time_point startTime{};
		bool running{false};
	};
}
