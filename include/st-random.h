#pragma once

namespace StyyxUtil {

	struct RandomiserUtil
	{
		/// @brief Get random integer between 2 values
		/// @param a_min lower value for the random integer
		/// @param a_max higher value for the random integer
		/// @return random integer between low and high value
		static int GetRandomInt(const int a_min, const int a_max)
		{
			std::uniform_int_distribution<int> distrib(a_min, a_max);
			return distrib(GetRNG());
		}

		/// @brief Get random float between 2 values
		/// @param a_min lower value for the random float
		/// @param a_max higher value for the random float
		/// @return random float between low and high value
		static float GetRandomFloat(const float a_min, const float a_max)
		{
			std::uniform_real_distribution<float> distrib(a_min, a_max);
			return distrib(GetRNG());
		}

		/// @brief Get random float rounded to a set amount of decimals
		/// @param a_min lower value for the random float
		/// @param a_max higher value for the random float
		/// @param decimals amount of decimals the float is rounded to
		/// @return random float rounded to the amount of decimals specified
		static float GetRandomRoundedFloat(const float a_min, const float a_max, const int decimals = 2)
		{
			const auto value = GetRandomFloat(a_min, a_max);
			const double factor = std::pow(10.0, static_cast<double>(decimals));
			return static_cast<float>(std::round(value * factor) / factor);
		}

		/// @brief Get random double between 2 values
		/// @param a_min lower value for the random double
		/// @param a_max higher value for the random double
		/// @return random double between low and high value
		static double GetRandomDouble(const double a_min, const double a_max) {
			std::uniform_real_distribution<double> distrib(a_min, a_max);
			return distrib(GetRNG());
		}

		/// @brief Rolls a random chance check against a given percentage
		/// @param a_chancePercent The success threshold (0-100). A value of 30.0 means a 30% chance of returning true
		/// @return true if the random roll succeeds, false otherwise
		static bool IsPercentageChanceFloat(const float a_chancePercent) {
			return GetRandomFloat(0.0, 100.0) <= a_chancePercent;
		}
	private:
		static std::mt19937& GetRNG()
		{
			static std::mt19937 gen(std::random_device{}());
			return gen;
		}

	};
}