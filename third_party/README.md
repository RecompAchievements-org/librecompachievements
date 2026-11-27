# Third-party code

Libraries vendored into this repository, copied unmodified from the version listed. Every one must
allow the SDK to be shipped under `MIT OR Apache-2.0` and inside GPL-2.0 recomps (see `AGENTS.md`).

| Library | Used for | Source | Version | License |
|---|---|---|---|---|
| `doctest/` | Unit tests only; never linked into the SDK | [doctest/doctest](https://github.com/doctest/doctest) | `v2.5.3` (`2d0a935`) | MIT (`doctest/LICENSE.txt`) |

To update a library, replace its files with the new release, update its row, and note the change in
`CHANGELOG.md` when it affects the SDK.
