# Changelog

All notable changes to librecompachievements are documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/), and this project
follows [Semantic Versioning](https://semver.org/spec/v2.0.0.html). Alpha versions
(`1.0.0-alpha.N`) may change the API between releases.

## [Unreleased]

### Added

- CMake build with presets, static and shared libraries, and an installable CMake package
  (`find_package(librecompachievements)`, target `rca::rca`).
- `rca_version()` and the `RCA_VERSION_*` macros, to check that a game's headers match the
  library it loads.
- CI on Linux (GCC and Clang), the Steam Runtime, macOS, and Windows, with sanitizers, clang-tidy,
  and clang-format checks.
