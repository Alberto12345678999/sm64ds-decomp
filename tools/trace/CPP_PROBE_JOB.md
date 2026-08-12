# Runtime C++ evidence job

Use this brief when handing one readable-C++ investigation to an agent or
contributor. Replace the angle-bracket placeholders; do not turn the whole
class into one open-ended task.

## Assignment

Use emulator runtime evidence to answer one concrete question about
`<symbol>`, then carry the answer through to either a verified minimal source
change or a documented negative result.

Question: **<one runtime-observable question>**

Examples of appropriately narrow questions:

- Does this function receive an instance pointer, and which concrete vtable
  reaches it?
- Which named or candidate field changes across this call?
- What values does this timer, flag, pointer, angle, or fixed-point field take
  on the exercised gameplay path?
- Which callers and virtual slots reach this function?

Runtime evidence cannot by itself prove byte identity, unobserved paths, or a
type property such as signedness when the executed operations do not
distinguish it.

## Required workflow

1. Work in a clean feature worktree based on freshly fetched `origin/main`.
   Read `AGENTS.md`, `notes/mwccarm-codegen.md`,
   `notes/matching-style.md`, and `tools/trace/README.md`. Claim the target
   before changing source or headers.
2. Confirm the configured address, module, instruction set, reconstructed
   class, receiver classification, and decodable fields without connecting to
   the emulator:

   ```sh
   python tools/trace/cpp_probe.py <symbol> --resolve-only
   ```

   Use `module:<symbol>` if the name is ambiguous. If automatic receiver
   classification is undecided, inspect the source signature before choosing
   `--this-reg`; do not assume that a mangled name makes `r0` an object pointer.
3. Start the controller-enabled melonDS with `--control-port 45987` and JIT
   disabled. Set `MELONDS_CONTROL_TOKEN` to the launch token. Load a savestate
   or gameplay scene that reaches the target. The normal path does not require
   or consume the ARM9 GDB stub.
4. Capture real calls while exercising the relevant behavior:

   ```sh
   python tools/trace/cpp_probe.py <symbol> \
     --hits 8 \
     --ask "<one runtime-observable question>"
   ```

   Add a candidate field when the header does not yet expose it:

   ```sh
   python tools/trace/cpp_probe.py <symbol> \
     --field 0x5c:Vector3:position \
     --hits 8 \
     --ask "Does +0x5c behave like this object's position?"
   ```

   Use `--no-return` only for recursive, non-returning, or very hot functions
   where entry/return pairing is unsuitable. Do not stop after
   `--resolve-only`; this job requires runtime evidence.

   Use `--backend gdb --port 3333` only with an emulator that lacks protocol 2.
5. Inspect the report and its JSON under `traces/questions/`. Record:

   - accepted hits and overlay-alias rejects;
   - observed callers and return registers;
   - object addresses and module-qualified vtable candidates;
   - live actor ID/catalog class plus the decomp config's symbols for the same
     vtable and behavior pointers, including any contradiction;
   - entry and exit values for named fields;
   - named and unnamed changed byte ranges;
   - which gameplay path was exercised.
6. Separate observations from inferences. An observed write or value is real
   for that captured path; absence is not disproof. If the evidence contradicts
   the proposed interpretation, preserve that negative result instead of
   forcing a source change.
7. If the evidence supports a change, make the smallest coherent source/header
   edit. Never place a near-miss in `src/`, and never mix tooling changes into a
   source-match PR.

For a resumable static + runtime workspace, assemble the result into a C++ job
instead of editing `src/` directly:

```sh
python tools/cpp_job.py create <symbol> \
  --runtime-evidence traces/questions/<capture>.json
```

Edit the generated `candidate.cpp` and use `cpp_job.py verify` until its
linked-byte verdict is `VERIFIED`. See `notes/cpp-research-jobs.md`.

## Validation

For a source change, run the exact per-function `tools/match.py` command with
the configured module/address/size and compiler version, then strict relocation
checking and `tools/linkcheck.py`.

For a header change, also run:

```sh
python tools/affected_src.py <header>
python tools/prepush_linkcheck.py --range origin/main..HEAD
```

For a rename, file move, or `.c` to `.cpp` migration, also run:

```sh
python tools/port_refcheck.py
```

Finish every resulting code change with:

```sh
python tools/rombuild.py -j 16 --no-rom
```

## Deliverable

Return all of the following:

- target symbol and exact question;
- capture command and saved evidence path;
- scene/savestate and behavior exercised;
- observed callers, vtables, values, returns, and writes;
- conclusion, explicitly separating observation from inference;
- minimal code change, or why no code change is justified;
- exact validation commands and results;
- remaining uncertainty and the next useful runtime experiment.

The assignment is incomplete if it only describes the probe, runs
`--resolve-only`, or substitutes another decompiler pass for gameplay evidence.
