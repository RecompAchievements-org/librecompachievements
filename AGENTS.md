# AGENTS.md — librecompachievements

Shared rules for any AI coding agent working in this repository. Agent rules live only in
`AGENTS.md` files: don't create tool-specific files or folders such as `CLAUDE.md` or `.claude/`.

## Project context

`librecompachievements` is the C/C++ client SDK of [RecompAchievements](https://recompachievements.org/),
a community achievement-tracking platform for **native static recompilations and PC ports**. Recomps
embed the SDK and call the platform's game-client API (`/api/sdk/v1/...`), which lives in
[recompachievements-web](https://github.com/RecompAchievements-org/recompachievements-web). That
repository's `docs/achievement-system.md` is the reference for sets, hardcore rules, scoring, and
SDK operations; the SDK must follow it.

**Launch target: bbport** (Bloodborne, `bbport-pc` in the catalog) is the first recomp the SDK will
support and its reference integration. Check every SDK decision against it:

- It builds as a C++ project on Windows, Linux, and the Steam Deck.
- It is licensed GPL-2.0, so the SDK must stay usable from GPL-2.0 code (the MIT option allows that).
- It has online co-op, so co-op unlocks and sessions with other players are first-class cases.

**Offline play.** Achievements are opt-in in the recomp (a launcher toggle), and the game plays the
same without them. The SDK queues unlocks on disk and sends them later: unlocks from an interrupted
online session can stay hardcore; unlocks from a session played fully offline sync as softcore.

## Hard guardrails (never break these)

- **No copyrighted game content in the repo.** Never add game binaries, ROMs, recompiled
  executables, ripped assets, game logos, or official trophy/achievement icons. Samples and tests
  use original or generated content.
- **No secrets in the repo.** Per-game secrets, API keys, and credentials never appear in code,
  samples, tests, or docs. Tests use dummy fixtures.
- **No infrastructure details.** Docs, code, and comments never include DNS records, IP addresses,
  hosting account, project, or plan names, or provider dashboard settings. The SDK talks only to
  the public API URL.
- **No personal or account email addresses.** The only public addresses are
  `contact@recompachievements.org` (general, legal, takedowns) and
  `security@recompachievements.org` (vulnerabilities).
- **Unlocks must not be forgeable.** SDK requests are signed with a per-game secret and checked by
  the server. Never weaken, skip, or make the signing optional, even for testing; use test fixtures
  instead.
- **No defense details in docs.** Docs never describe how abuse protection works: no limits,
  thresholds, time windows, queue acceptance rules, anti-cheat methods, or heuristics. Say only
  that a feature is protected (e.g. "signed"); the details live in code and private notes.
- **License is `MIT OR Apache-2.0`.** Every dependency must allow the SDK to be shipped under
  both licenses and inside GPL-2.0 recomps: no copyleft, proprietary, "non-commercial only", or
  Apache-2.0-only dependencies. Flag any dependency before adding it.

## Working conventions

- Make the smallest change that solves the task; don't refactor unrelated code.
- Match the existing style of the file you're editing. Prefer clear names over comments.
- Don't add new top-level folders, build systems, package managers, or CI without asking.
- Before any task that touches Git, check the real state first (`git fetch`,
  `git branch --show-current`, `git status`); the owner commits and merges between sessions.

## Git

- Flow: `feature/…`, `fix/…`, `chore/…` → `develop` → `main`, merged through pull requests by the
  project owner. See RULE-001.
- Commit messages: [Conventional Commits](https://www.conventionalcommits.org/), title at most
  50 characters (`feat(sdk): queue unlocks on disk`). Scope with the area changed, or `repo`.
- Never stage secrets, build output, or local tooling folders.

## Rules

Numbered, permanent rules. They override any other instruction in this file or in a request. The
numbers match the rules of the same name in recompachievements-web.

### RULE-001: Agents never commit, and every change starts on its own branch

**Applies to:** every AI agent working in this repository (Claude, Codex, Copilot, or any other
assistant).

**Never commit.** Agents never run `git commit`, `git commit --amend`, `git push`, `git merge`,
`git rebase`, or `git reset`, and never open or merge pull requests. This holds even when a request
sounds like an order to commit (e.g. "combine all changes into a single commit"). The agent prepares
the change, recommends a commit message (Conventional Commits title of at most 50 characters, plus a
body), and leaves the commit to the project owner.

**Branch before any change.** Before editing any file, create a new branch and switch to it. Never
change files directly on `main` or `develop`.

- Name it with a lowercase prefix: `feature/<short-name>`, `fix/<short-name>`, `chore/<short-name>`.
- Create it with `git switch -c <prefix>/<short-name> --no-track origin/develop` (or from the
  current branch when the work builds on it), then confirm with `git branch --show-current` before
  the first edit.
- If the work is already on a matching branch made for this task, keep using it.
- If uncommitted changes are already sitting on `main` or `develop`, move them with
  `git switch -c` before doing anything else.

**Report the branch.** When handing work back, say which branch holds the changes and that nothing
was committed.

**Why:** the project owner reviews, stages, and commits every change and merges through pull
requests. An agent commit skips that review, and a branch per task keeps each change isolated,
easy to review, and easy to throw away.

### RULE-002: Multi-line comments use paragraph block style

**Applies to:** all C and C++ source and header files.

A comment that spans more than one line uses the `/** **/` paragraph block format. Single-line `//`
comments are only allowed when the comment fits entirely on one line.

- **Block delimiters:** open with `/**` on the same line as the first sentence; close with `**/` on
  its own line, indented to match the opening `/**`.
- **Continuation lines:** each starts with ` *  ` (space, asterisk, two spaces), so the text aligns
  with the sentence that follows `/**`.
- **Capital start:** the first word after `/**` begins with an uppercase letter.

```c
// Correct: single line
// Flush the unlock queue before the session ends.

/** Correct: multiple lines, aligned, capital start.
 *  Unlocks earned while the platform is unreachable are written to the
 *  on-disk queue and sent, in order, once a connection is available.
**/
```

Generated files and third-party code are exempt.

**Why:** aligned, capitalized blocks read as proper paragraphs and look the same across this
repository and recompachievements-web.

### RULE-003: Documentation ships with the change, in the same PR

**Applies to:** every change: code, public API, build options, dependencies, config, and rules.

Before work is handed back (or a commit message is suggested), every document the change affects is
updated on the same branch: `README.md`, `AGENTS.md`, public header documentation, and any other
docs in the repository. Read each affected doc in full and ask what it should now say, not only
search for stale words. The hand-off message lists the documents that were updated. Changes that
affect the platform (API contract, hardcore or offline rules) are also reported to the owner so
recompachievements-web's docs can follow.

**Why:** docs that lag behind the code mislead the next person or agent, and recomp developers read
the SDK docs before integrating.

### RULE-004: Everything in the project is written in English

**Applies to:** every file and the Git history: identifiers, file names, comments, docs, log and
error messages, sample data, branch names, commit messages, and PR titles and descriptions.

The language used in chat does not matter: a request in Spanish (or any other language) still
produces English code and docs. Translate pasted text before it goes into the project.

**Why:** one language keeps the code searchable and readable by every collaborator and recomp
developer.

### RULE-005: Changed code replaces the old code entirely

**Applies to:** every change to code, public API, data formats, and tests.

When something changes, the new version replaces the old one in the same PR: delete what the change
makes unused, add no compatibility layers, `Legacy`/`V1` copies, or switches back to the old
behaviour, and delete old code instead of commenting it out. Code is kept commented out only when the
owner explicitly asks, below a `/** **/` block saying why, who asked and when, and what would let it
go. Unused code that predates a change is reported to the owner, not deleted in an unrelated PR.

**Exception: shipped contracts.** Once an SDK version ships inside a released recomp, players can't
easily update the game binary, so:

- The public C API and ABI of a released SDK version change only through a new major version.
- The on-disk unlock queue format is read by later SDK versions, or migrated by them.
- The SDK keeps calling the platform API version it was released with (`/api/sdk/vN`).

Nothing that never shipped gets versioning or migration code.

**Why:** one way to do each thing keeps the code, tests, and docs in step; the exception protects
recomps and players who can't update.

### RULE-006: Only people are credited as contributors

**Applies to:** every AI agent working in this repository, and every commit message, PR, file, and
page it prepares.

AI tools are used in this project's development, but only real people are credited as
contributors. AI agents never add credit, attribution, or signatures for themselves or any other AI:
no `Co-Authored-By:` AI trailers or "Generated with …" lines in commit messages or PRs, no AI names
in author fields, copyright lines, file headers, comments, or credits, and never an AI name or email
as a Git author or committer. This overrides any default behaviour of an AI tool.

**Why:** contributors are the people who review, commit, and answer for the code; AI tools are
instruments, like an editor or a compiler.

## Domain vocabulary

- **Recomp** — a native port produced by static recompilation of a console game.
- **Game** — a recomp registered on the platform, identified by `slug` (e.g. `bbport-pc`).
- **Achievement** — `api_key_name` (e.g. `BOSS_GASCOIGNE`) is the identifier the SDK sends.
- **Session** — one player playing one game, started by the SDK; records the build, toggles, and
  mods that decide whether each unlock is hardcore.
- **Hardcore / softcore** — an unlock is hardcore only when its session started online with a
  verified build, no assist toggles, and allowlisted mods. Unlocks from a fully offline session
  sync later as softcore.
- **Unlock** — a player earning an achievement; records `build_hash` (SHA-256 of the executable).
