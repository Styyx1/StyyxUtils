#pragma once

namespace StyyxUtil {

    struct RandomiserUtil
    {
        static std::mt19937& GetRNG()
        {
            static std::mt19937 gen(std::random_device{}());
            return gen;
        }

        static int GetRandomInt(int a_min, int a_max)
        {
            std::uniform_int_distribution<int> distrib(a_min, a_max);
            return distrib(GetRNG());
        }

        static float GetRandomFloat(float a_min, float a_max)
        {
            std::uniform_real_distribution<float> distrib(a_min, a_max);
            return distrib(GetRNG());
        }

        static float GetRoundedFloat(float a_min, float a_max, int decimals = 2)
        {
            auto value = GetRandomFloat(a_min, a_max);
            float factor = std::pow(10.0f, static_cast<float>(decimals));
            return std::round(value * factor) / factor;
        }
    };
}