# PR3955 prospective header-layout repair

Task:pr3955-header-layout1016. Producer:codex-pr3955-smartball-repair1016.
Successful claim at input a317608eecf3906dfc6dcc01376c711903350b9f precedes all edits.
Scope:include/cMgSmartball_wing_c.h, include/dScMgBSC_c.h, this report.

CollisionVertex remains two s32 coordinates and mVertices remains eight records.
A qualified sizeof(CollisionVertex)==8 assertion supplies the existing layout
checker with compiler-enforced size evidence. CardPos mCardPos[2] stays on one
line with its offset; its constructor/destructor explanation is retained above.
The wing-only GetAngle accessor gives the existing byte pair its signed reader
view, without changing the base header, layout, vtable or any shared field type.

Validation: check_header_offsets.py --changed0301d63f passes with no new waiver.
Fresh BSC and Smartball prepared objects are exactly identical to the independently
accepted a317 objects;153/153 owned functions including BSC initializer verify.
The converted/tiers suite passes59 tests (one historical-shard skip).
Source style has one explicit unknown-byte finding in GetAngle. A one-row cap1
exception proposal is saved under build/pr3955-wing-style-proposal.patch; the
reserved tracked configuration is untouched. Adoption and independent review
remain required before publication. This task does not retroactively claim the
three overlapping earlier PR3955 paths or release another owner's reservation.
