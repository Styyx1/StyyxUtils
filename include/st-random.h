#pragma once

namespace StyyxUtil {

	struct RandomiserUtil
	{
		static std::mt19937& GetRNG()
		{
			static std::mt19937 gen(std::random_device{}());
			return gen;
		}

		/// <summary>
		/// Get random integer
		/// </summary>
		/// <param name="a_min"></param>
		/// <param name="a_max"></param>
		/// <returns></returns>
		static int GetRandomInt(int a_min, int a_max)
		{
			std::uniform_int_distribution<int> distrib(a_min, a_max);
			return distrib(GetRNG());
		}

		/// <summary>
		/// Get random float
		/// </summary>
		/// <param name="a_min"></param>
		/// <param name="a_max"></param>
		/// <returns></returns>
		static float GetRandomFloat(float a_min, float a_max)
		{
			std::uniform_real_distribution<float> distrib(a_min, a_max);
			return distrib(GetRNG());
		}

		/// <summary>
		/// Get random float but rounded
		/// </summary>
		/// <param name="a_min"></param>
		/// <param name="a_max"></param>
		/// <param name="decimals"></param>
		/// <returns></returns>
		static float GetRoundedFloat(float a_min, float a_max, int decimals = 2)
		{
			auto value = GetRandomFloat(a_min, a_max);
			float factor = std::pow(10.0f, static_cast<float>(decimals));
			return std::round(value * factor) / factor;
		}

		/// <summary>
		/// Get random double
		/// </summary>
		/// <param name="a_min"></param>
		/// <param name="a_max"></param>
		/// <returns></returns>
		static double GetRandomDouble(double a_min, double a_max) {
			std::uniform_real_distribution<double> distrib(a_min, a_max);
			return distrib(GetRNG());
		}

		/// <summary>
		/// Helper function to check if a random float is within a specific percentage range
		/// </summary>
		/// <param name="a_chancePercent"></param>
		/// <returns></returns>
		static bool IsPercentageChanceFloat(float a_chancePercent) {
			auto rng = GetRandomFloat(0.0, 100.0);
			if (rng <= a_chancePercent)
				return true;
			return false;
		}

	};
}