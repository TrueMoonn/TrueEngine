/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** pattern
*/

#include <cmath>

#include "entity_spec/components/pattern.hpp"

#include "clock.hpp"

namespace addon {
namespace eSpec {


// static float pattern_1(size_t val) {
//     return ((int(val * 100000) % 800000) - 400000) / 100000;
// }

Pattern::Pattern(std::size_t index)
    : func([](long long val) -> float {

        static te::Timestamp t(size_t(0));

        // float y = 2f * Mathf.Sin(2f * Mathf.PI * 1f * t);

        return 2.f * std::sin(2.f * M_PI * (float(t.getElapsedTime()) / 1000000));

        // std::cout << t.getElapsedTime() << std::endl;
        // return std::sin(float (t.getElapsedTime()) / 100000);

        // // val = val % 400 > 200 ? val : -val;
        // return float((abs(val) % 200) - 100) / 100;
    }) {}

}  // namespace eSpec
}  // namespace addon
