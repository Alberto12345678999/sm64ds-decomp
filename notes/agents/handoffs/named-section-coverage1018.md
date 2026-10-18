# Named initialized-section coverage

Task: `tools-named-section-coverage1018`, issue [4088](https://github.com/tangosdev/sm64ds-decomp/issues/4088).
Candidate: this commit. Tested base: `fe73dec6ed2f323d1d009f693d2e98c9c7c29280`.
Workflow: `18af52b49b9fb5663d417bdfa86109b7b157aaa3`.

The coverage parser previously ignored section names containing a second dot.
This omitted newly enrolled native data and made a plain-to-named route conversion
look like lost source ownership. Parse the full section name and reuse the build
router's accepted initialized-section classifier. Normalize valid named `.data`
and `.rodata` routes into their own families before interval unions, difference,
blame, and waiver accounting. Unsupported names retain separate identities.
Both CI event filters include the classifier dependency.

Eight new regression methods cover additions; all four genuine loss mechanisms;
plain/named splits and renames in working trees and refs; overlap unions; separate
data/rodata families; unsupported names; exact waiver extents and module boundaries;
and identical addresses moved between modules. The corrected fixtures produced
22 assertion failures and no fixture errors against the old tool (33 tests).
All 33 tests now pass, as do all nine route helper tests. `git diff --check` passes.

Read-only measurements of the actual source worktrees give Entry +276, DSMT +184,
and Sound +124 bytes, each with zero lost bytes. Their bases and exact ranges are
recorded in `notes/experiments/named-section-coverage1018.json`. These measurements
are not replacements for independent compiler-provider and full-ROM validation.
No source, ownership interval, waiver configuration, compiler or ROM is changed.

The experiment retains all three predecessor findings verbatim, including the
historical Dorifu continuation, and records two fixed coverage/dependency findings.
The later Dorifu source PR does not explain its unclaimed tails. The global data
backlog remains partial. This tool does not claim that all TUs are source-built.

Next: independently review this exact commit and base, rerun tests and real-tree
measurements, then publish a separate tool PR on a pinned base. Sound must explicitly
compose the accepted tool and rerun its final proof. No main merge is authorized.
Private regression logs live under `build/coverage-*`; no private build inputs or
queue receipts are part of this change.
