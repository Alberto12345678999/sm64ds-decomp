"""The pinned DSD LCF's minimum alignment for each mwldarm input section.

ALIGNALL applies to every repeated input section, not just the object's first
section. ELF sh_addralign can be smaller (notably for native string literals).
Keep the layout model tied to this policy by validating generated LCFs before
compilation in both the production and scratch-link pipelines.
"""
import pathlib
import re

INPUT_ALIGNMENT = 4


def effective_alignment(elf_alignment):
    return max(INPUT_ALIGNMENT, int(elf_alignment or 1))


def verify_lcf(path):
    """Fail closed if a generated output does not begin with sole ALIGNALL(4).

    This accepts the pinned generator's flat output-block grammar. It does not
    guess the active alignment of a different linker script dialect.
    """
    text = pathlib.Path(path).read_text(encoding="utf-8")
    text = re.sub(r"/\*.*?\*/|//[^\n]*", "", text, flags=re.S)
    memory = re.search(r"\bMEMORY\s*\{([^{}]*)\}", text)
    if memory is None:
        raise ValueError("linker alignment: missing or unsupported MEMORY block")
    regions = re.findall(r"^\s*(\w+)\s*:\s*ORIGIN\s*=[^\n]*>[^\n]+$",
                         memory[1], flags=re.M)
    if not regions or len(regions) != len(set(regions)):
        raise ValueError("linker alignment: missing or duplicate output regions")
    pattern = r"(\.[\w]+)\s*:\s*\{([^{}]*)\}\s*>\s*(\w+)"
    blocks = list(re.finditer(pattern, text))
    starts = re.findall(r"\.[\w]+\s*:\s*\{", text)
    names = [block[1] for block in blocks]
    outputs = [block[3] for block in blocks]
    if (len(starts) != len(blocks) or len(names) != len(set(names))
            or len(outputs) != len(set(outputs)) or set(outputs) != set(regions)):
        raise ValueError("linker alignment: output blocks do not match MEMORY regions")
    for block in blocks:
        body = block[2]
        if (not re.match(r"\s*ALIGNALL\(\s*4\s*\)\s*;", body)
                or len(re.findall(r"\bALIGNALL\b", body)) != 1):
            raise ValueError(f"linker alignment: {block[1]} must begin with sole ALIGNALL(4)")
    if re.search(r"\bALIGNALL\b", re.sub(pattern, "", text)):
        raise ValueError("linker alignment: ALIGNALL outside an output block")
    return {"inputAlignment": INPUT_ALIGNMENT, "outputs": sorted(outputs)}
