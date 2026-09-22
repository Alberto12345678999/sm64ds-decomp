# Native-destructor declaration checker repair

This commit applies the explicitly approved patch `a44b2a93f02d5e472aee9498fdbdbdc22c689782e345bc8330c3b3c1343219c0` to the checker and its tests, on main `27ca0e1f322b9cdc538c6954c36ddba44066c683`. The scoped exception preserves the existing `pr-2471-source-review-fixes` branch and reservation. The producer is `codex-native-destructor-producer-0922`; independent verification follows this commit. No baseline, source, header, compiler or ROM input is changed.

The checker recognizes native qualified destructors only when their owner exactly matches the marked direct D0/D1/D2 identity. It keeps source return syntax distinct from the direct Arm ABI result and retains the normal implicit-receiver policy. Constructors, thunks, wrappers and ambiguous identities are not inferred. A missing or scalar receiver still produces a real finding.

The actual standalone suite passes **164 tests, zero skips**. The earlier 173-test result was the separate local composition with overload PR #2907; that patch is not included here. The exact current-base diagnostic population is 8,626 files, 38,195 declarations, 10,635 definitions and two unparsed declarators. Rows change from 16,547 to 16,461: 100 keys removed, 15 introduced missing-receiver keys, and 128 reference rows revised. Every changed symbol is a direct destructor identity. All other rows remain unchanged.

## Publication and remaining source debt

Publish as a draft. The whole-tree gate changes from zero to **15 unbanked findings** because it now recognizes the real implicit destructor receiver. These are existing source declarations requiring separate byte-proven repairs, not new baseline exceptions. The PR's tool-only changed scope does not exercise them; a green scoped check is not evidence that the whole-tree gate passes. Next owner: `codex-integrator-0920`. This PR must not be treated as ready to merge until the source dependencies are accounted for and the resulting whole-tree gate passes.

| Destructor | Existing declaration requiring a receiver |
| --- | --- |
| `_ZN10FaderColorD1Ev` | `src/__sinit_02073e6c.c` |
| `_ZN10FaderColorD1Ev` | `src/__sinit_02074edc.c` |
| `_ZN10dScEntry_c6icon_cD1Ev` | `src/d_s_entry_entry.cpp` |
| `_ZN10dScEntry_c6icon_cD1Ev` | `src/d_s_entry_result.cpp` |
| `_ZN11ShadowModelD1Ev` | `src/d_a_wanwan2.cpp` |
| `_ZN11ShadowModelD1Ev` | `src/game/actors/d_a_wanwan.cpp` |
| `_ZN12OamAnimationD1Ev` | `src/d_s_entry_entry.cpp` |
| `_ZN12OamAnimationD1Ev` | `src/d_s_entry_result.cpp` |
| `_ZN15FaderBrightnessD1Ev` | `src/__sinit_02074edc.c` |
| `_ZN15UnknownVsPlayerD1Ev` | `src/d_ent_obj.cpp` |
| `_ZN16dMgJump3DMario_cD1Ev` | `src/d_s_mg_jump.cpp` |
| `_ZN16dMgJump3DMario_cD1Ev` | `src/minigames/d_s_mg_jump2.cpp` |
| `_ZN5ModelD1Ev` | `src/d_a_wanwan2.cpp` |
| `_ZN5ModelD1Ev` | `src/game/actors/d_a_wanwan.cpp` |
| `_ZN7ClipperD1Ev` | `src/__sinit_02074e84.cpp` |

The local Cup follow-up already measures the two Jump declarations and Model/ShadowModel in `d_a_wanwan.cpp`; those source repairs are not part of this tooling PR and have not landed. No complete class reconstruction, source acceptance, or ROM proof is asserted by this tooling-only result.
