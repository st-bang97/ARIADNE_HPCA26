# ARIADNE

Artifact for **ARIADNE: Adaptive UVM Management for Efficient GPU Memory Oversubscription**, published at **HPCA 2026**.

**Authors:** Hyunkyun Shin, Seongtae Bang, Hyungwon Park, and Daehoon Kim.

[Paper](https://doi.org/10.1109/HPCA68181.2026.11408564)

## Overview

ARIADNE is a runtime framework implemented within NVIDIA's Unified Virtual Memory (UVM) driver to reduce page fault overhead and thrashing under GPU memory oversubscription. It combines:

- **Pipelined fault handling** to hide memory migration latency.
- **Sharing Degree**, a runtime metric that captures thread-level access locality.
- **Dynamic memory placement** between GPU memory and host memory accessed through Zero-copy.

ARIADNE requires no application recompilation or hardware modifications. The paper reports average speedups of **1.9x, 5.0x, and 4.8x** over a state-of-the-art method at **130%, 175%, and 300%** oversubscription, respectively.

## Repository Contents

This repository contains the artifact downloaded from Zenodo.

| Path | Contents |
| --- | --- |
| `ARIADNE/` | ARIADNE driver implementation |
| `UVM/` | Baseline UVM driver |
| `SUV-MICRO24/` | SUV comparison artifact, including LLVM and driver sources |
| `benchmarks/` | Evaluation workloads |
| `results/` | Result plotting and analysis scripts |
| `Install_*.sh`, `run_*.sh` | Driver installation and experiment scripts |

See the component READMEs and root-level scripts for build and experiment details.
