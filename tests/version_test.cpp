#include "rca/rca.h"

#include <doctest/doctest.h>

#include <string>
#include <string_view>

TEST_CASE("rca_version matches the version in the headers") {
    CHECK(std::string_view(rca_version()) == RCA_VERSION_STRING);
}

TEST_CASE("the version string is built from the version numbers") {
    std::string expected = std::to_string(RCA_VERSION_MAJOR) + "." +
                           std::to_string(RCA_VERSION_MINOR) + "." +
                           std::to_string(RCA_VERSION_PATCH);
    if (std::string_view(RCA_VERSION_PRERELEASE).empty() == false) {
        expected += std::string("-") + RCA_VERSION_PRERELEASE;
    }
    CHECK(std::string_view(rca_version()) == expected);
}
