# Security Policy

librecompachievements is the client SDK that recomps embed to send achievement unlocks to
RecompAchievements. It relies on the integrity of those unlocks and on keeping player tokens and
game secrets safe. We appreciate responsible reports and will work with you to fix issues quickly.

## Reporting a vulnerability

**Please do not report security issues through public GitHub issues, discussions, or pull requests.**

Report privately through either channel:

- **GitHub:** [Report a vulnerability](https://github.com/RecompAchievements-org/librecompachievements/security/advisories/new)
  (private security advisory)
- **Email:** [security@recompachievements.org](mailto:security@recompachievements.org)

Please include:

- A description of the issue and its impact
- Steps to reproduce or a proof of concept
- The SDK version (`rca_version()`) or commit, and the platform

## What to expect

- Acknowledgement within **3 business days**
- An initial assessment and next steps within **10 business days**
- Credit in the release notes once fixed, if you'd like it

This is a volunteer-run project, so timelines are best effort.

## Scope

In scope:

- Forging, replaying, or tampering with unlocks sent through the SDK (e.g. bypassing request
  signing)
- Exposure of player tokens or game secrets by the SDK (in logs, files, or memory it hands out)
- Memory-safety bugs in the SDK reachable from network responses or its on-disk files
- Weaknesses in how the SDK connects to the platform (e.g. TLS checks)

Out of scope:

- Cheating within a game by modifying your local executable or memory; report suspicious unlocks
  to [contact@recompachievements.org](mailto:contact@recompachievements.org) instead
- Issues in the website and its APIs: see the
  [platform's security policy](https://github.com/RecompAchievements-org/recompachievements-web/security/policy)
- Denial-of-service or volumetric attacks
- Social engineering of maintainers or users
- Findings from automated scanners without a demonstrated impact

## Safe harbor

We will not pursue action against research done in good faith that respects user privacy, avoids
data destruction and service disruption, and stays within this policy. Only test against accounts
you own.

## Supported versions

The SDK is in alpha; only the latest version on `main` receives security fixes.
