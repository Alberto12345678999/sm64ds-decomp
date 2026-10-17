# PR3955 prospective Smartball angle repair

Task:pr3955-smartball-angle1016. Producer:codex-pr3955-smartball-repair1016.
Successful claim at input a317608eecf3906dfc6dcc01376c711903350b9f precedes all edits.
Scope:src/minigames/d_s_mg_smartball.cpp and this report.

IsSettled and RebuildVerts use the documented wing-only GetAngle accessor.
It casts existing unk_032 byte storage as s16 for this reader only. The header's
other readers require unsigned-halfword, independent-byte and cell-array views;
therefore no shared signed-angle field is introduced. mVertices and every
vertex expression remain intact. This is a reusable reader interface, not a
claim that the shared byte region has one type or that the class is complete.

Fresh pinned b56 compile is fully production-prepared-object-identical to a317;
all132 Smartball functions strictly verify. The combined header/source change
also preserves BSC's object and21 owned functions/initializer. Tiers tests pass
59 (one skip), and header offsets pass. Source-style finds exactly one truthful
unknown storage reference in the accessor; the separately prepared counted
exception is not applied to the reserved config. Independent review and explicit
prospective adoption remain pending. No PR branch push or merge was performed.
