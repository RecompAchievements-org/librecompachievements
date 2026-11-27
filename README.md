# librecompachievements

C/C++ client SDK for [RecompAchievements](https://recompachievements.org/): achievement tracking
for native static recompilations.

> 🚧 **Status: in development, heading to Alpha v1.0.** The build, packaging, and CI are in place;
> the SDK only reports its version so far. Logging in, sessions, unlocks, offline play, and
> presence come next. The API may change during the alpha.

The SDK is written in C++17 and exposes a plain C API (`include/rca/rca.h`), so any C or C++
recomp can use it. It builds on Windows, Linux (including the Steam Deck), and macOS.

## Building

Requirements: **CMake 3.21+**, **Ninja**, and a C++17 compiler (GCC 10+, Clang, Apple Clang, or
Visual Studio 2022+).

```bash
cmake --preset debug          # configure into build/debug
cmake --build --preset debug  # build the library, tests, and example
ctest --preset debug          # run the tests
./build/debug/examples/rca_example_minimal
```

On Windows, use the `msvc` preset (Visual Studio) for all three commands.

| Preset | Purpose |
|---|---|
| `debug`, `release` | Everyday builds |
| `ci` | Debug build with warnings as errors, as CI runs it |
| `asan`, `tsan` | AddressSanitizer + UndefinedBehaviorSanitizer, and ThreadSanitizer (GCC or Clang) |
| `tidy` | Builds the library with `clang-tidy` checks as errors (`clang-tidy` on `PATH`) |
| `msvc` | Visual Studio on Windows |

Add `-DBUILD_SHARED_LIBS=ON` to the configure step for a shared library instead of a static one.
Format C and C++ files with `clang-format` 23 (`.clang-format`) before opening a pull request.

## Using the SDK in a recomp

With CMake, add the SDK as a subdirectory (or with `FetchContent`) and link its target:

```cmake
add_subdirectory(third_party/librecompachievements)
target_link_libraries(my_recomp PRIVATE rca::rca)
```

Or install it (`cmake --install build/release --prefix <dir>`) and use
`find_package(librecompachievements 1 REQUIRED)` with the same `rca::rca` target. A full
integration guide comes with the SDK's first features.

## Repository structure

```
librecompachievements/
├── include/rca/        # Public C API (the only binary interface)
├── src/                # Implementation (C++17)
├── cmake/              # Build helpers, version header, and package config templates
├── tests/              # Unit tests (doctest), a C header test, and an install test (tests/package)
├── examples/           # Example programs that use the SDK
├── third_party/        # Vendored libraries, listed with versions and licenses in its README
├── CMakePresets.json   # Build, test, sanitizer, and lint presets
└── .github/workflows/  # CI
```

Release notes are in [CHANGELOG.md](CHANGELOG.md).

## Contributing

The project is in its early stages. Issues and ideas are welcome; please open an issue to discuss
larger changes before a pull request. Write code, comments, docs, and commit messages in English,
and update any documentation your change affects in the same pull request. AI-assisted
contributions should follow [`AGENTS.md`](AGENTS.md).

**On AI assistance:** AI tools are used in the development of this project. Every change is
reviewed and committed by a human maintainer, and only people are credited as contributors.

Security vulnerabilities: please **do not** open a public issue; see [SECURITY.md](SECURITY.md).
General questions:
[contact@recompachievements.org](mailto:contact@recompachievements.org).

## License

Licensed under either of

- Apache License, Version 2.0 ([LICENSE-APACHE](LICENSE-APACHE) or
  <https://www.apache.org/licenses/LICENSE-2.0>)
- MIT license ([LICENSE-MIT](LICENSE-MIT) or <https://opensource.org/licenses/MIT>)

at your option.

SPDX-License-Identifier: `MIT OR Apache-2.0`

The MIT option keeps the SDK usable from GPL-2.0 projects such as
[bbport](https://github.com/deadinside28/bloodborne_pc). Apache-2.0 alone is not compatible with
GPL-2.0.

### Contribution

Unless you explicitly state otherwise, any contribution intentionally submitted for inclusion in
this work by you, as defined in the Apache-2.0 license, shall be dual licensed as above, without
any additional terms or conditions.
