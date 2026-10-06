# ARIADNE (HPCA 2026)

Artifact for **ARIADNE: Adaptive UVM Management for Efficient GPU Memory Oversubscription**.

Hyunkyun Shin, Seongtae Bang, Hyungwon Park, and Daehoon Kim.

2026 IEEE International Symposium on High Performance Computer Architecture (HPCA).

[Paper](https://doi.org/10.1109/HPCA68181.2026.11408564) | [Zenodo artifact](https://doi.org/10.5281/zenodo.17829999)

## Environment

The paper's artifact uses an NVIDIA RTX A5000, Linux kernel 6.0, CUDA 12.1, and NVIDIA open kernel modules v535.86.05. Prepare GCC, Make, NVCC, matching kernel headers, and 15 GB of free disk space. Plotting requires Python 3 with `numpy`, `pandas`, `matplotlib`, and `scipy`.

The scripts replace NVIDIA kernel modules. Run experiments with root privileges on a machine where the NVIDIA video kernel modules are not in use. Adjust the memory reservation amounts in `run_bench.sh` if GPU memory capacity differs from the paper's setup.

## Build

Run from the repository root:

```bash
git clone https://github.com/st-bang97/ARIADNE_HPCA26.git
cd ARIADNE_HPCA26
make -C ARIADNE clean
make -C UVM clean
cd benchmarks
nvcc hostpin.cu -o hostpin
bash compile.sh
cd ..
```

## Run Experiments

Following the paper's artifact appendix, run from the repository root:

```bash
sudo bash run_ARIADNE_AC.sh       # ARIADNE and access-counter (AC) comparison
sudo bash run_breakdown.sh        # Component breakdown
sudo env NVIDIA_MODULE_PATH=./ARIADNE/kernel-open/nvidia.ko bash run_sstv_analysis.sh
```

The scripts build and install the required driver modules automatically. The last command supplies `NVIDIA_MODULE_PATH`, which the bundled sensitivity script references without defining.

Generate the plots from the collected data:

```bash
cd results
python3 runtime_graph.py          # Figure 9: performance comparison
python3 breakdown.py              # Figure 11: component breakdown
python3 sstv_analysis_graph.py    # Figure 13: parameter sensitivity
```

Raw results and `fig_9.png`, `fig_11.png`, and `fig_13.png` are stored in `results/`. The paper estimates approximately 30 minutes of preparation and 2 hours of experiments; timings and numerical results depend on the system.

## Optional: SUV Comparison

SUV requires a separate setup: Linux kernel 6.2, CUDA 11.8, NVIDIA open kernel modules v525, 120 GB of main memory, and 210 GB of disk space. See [SUV documentation](SUV-MICRO24/README.md), prepare that environment, and run `bash run_SUV.sh` from the repository root. The paper estimates approximately 6 hours of preparation for SUV.
