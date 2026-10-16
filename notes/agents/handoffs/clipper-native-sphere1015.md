# Native ClipSphere continuation for issue 2410

Task issue2410-clipper-sphere1015 follows accepted PR3900 (5fd54e39d307634d1580330ca5984163ff8c0906), with all42 prior findings preserved. This API checkpoint remains WIP. It does not complete Monkey or close issue2410.

ClipSphere is an inferred descriptive name for arm9:0x020150e8 (0x478 bytes), not a recovered ROM identifier. The genuine member takes Vector3&, scalar Fix12i radius and optional rejecting-plane hint. It preserves near/far tests, side-plane rounding, hint caching, opt_propagation-off and the measured goto/temporary form. TransformAndClip calls it natively. Canonical address/extent/enrollment and original authors are preserved; no compatibility alias or banked declaration-baseline rewrite is added.

Only dClipper.h and d_clipper.cpp are changed source here. Actor's one caller remains reserved to its original producer and will be adopted as an exact owned API-only commit on this frozen input. No dActor header change is proposed. The existing scalar camera-position-to-Vector3 view in Actor remains explicit layout/aliasing debt. Actor manifest/output inventory needs no mechanical change in the measured preview.

Private scout preview: all9 header consumers rebuilt in control/candidate,342 strict checks per side with zero blind relocations, complete allocated storage/symbol/order/typed-relocation equality under only the canonical function rename, no compiler-local shifts. This is not production acceptance. Actual canonical production gates/fullROM, owned Actor contribution and exact-head independent Source remain pending before the next PR.

All10 touched/read source/config preimages are literally equal to fresh main composition fe7f1868ec5714db783c0e1081a1a9a05df49a46 (main d6edd59a6a476acfdf8325980be709d129313923 plus accepted Monkey/Clipper stack). That composition independently passed106/106 modules,11334 functions and336 source-owned data claims with4396 stable tracked inputs. The publication stack retains PR3900 as its base; future current-main composition is a separate actual gate, not inferred from old file identity.
