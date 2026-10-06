import os
import re
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import gmean

# 데이터 읽기
records = []
# Files to exclude from processing
exclude_files = {'runtime_graph.py', '.DS_Store'}
image_extensions = ('.png', '.eps', '.svg')

for filename in os.listdir('.'):
    # Skip excluded files, images, and directories
    if filename in exclude_files or filename.endswith(image_extensions) or filename.startswith('.'):
        continue
    if not os.path.isfile(filename):
        continue
        
    # Determine method name from filename
    # Format changed: "benchmark_METHOD.txt" -> "METHOD" or "METHOD.txt"
    method = filename
    if filename.lower().endswith('.txt'):
        method = filename[:-4]
        
    try:
        with open(filename, "r") as f:
            lines = f.readlines()
    except UnicodeDecodeError:
        # Skip binary files if any accidentally picked up
        continue

    current_oversub = None
    has_valid_data = False
    
    for line in lines:
        line = line.strip()
        if not line:
            continue
        if re.match(r'^(nooversub|\d+)$', line):
            current_oversub = line
        else:
            m = re.match(r'^(.+?)\s+Runtime:\s+([\d\.]+)s$', line)
            if m and current_oversub is not None:
                benchmark = m.group(1).strip()
                runtime = float(m.group(2))
                records.append({
                    'oversub': current_oversub,
                    'benchmark': benchmark,
                    'method': method,
                    'runtime': runtime
                })
                has_valid_data = True

df = pd.DataFrame(records)

if df.empty:
    print("No data found. Please check if benchmark files exist (e.g., 'ARIADNE', 'AC').")
    exit()

# Benchmark 이름에서 " GPU" 제거
df['benchmark'] = df['benchmark'].str.replace(r' GPU$', '', regex=True)

# 평균 runtime 계산: 동일 (oversub, benchmark, method) 조합에 대해 평균
df_mean = df.groupby(['oversub', 'benchmark', 'method'], as_index=False)['runtime'].mean()

# Pivot 및 정규화: SUV 기준
df_pivot = df_mean.pivot(index=['oversub', 'benchmark'], columns='method', values='runtime')
normal_val = 'AC'

# Check if normalization column exists
if normal_val not in df_pivot.columns:
    print(f"Normalization target '{normal_val}' not found in data. Available methods: {df_pivot.columns.tolist()}")
    # Attempt to continue, though normalization might fail if AC is missing entirely
else:
    for col in df_pivot.columns:
        if col == normal_val:
            continue
        df_pivot[col] = df_pivot[col] / df_pivot[normal_val]
    df_pivot[normal_val] = 1

# AVG(산술 평균) 및 GMEAN(기하 평균) 행 계산
summary_rows = []
# Ensure we only iterate over existing index levels
if not df_pivot.empty:
    for oversub in df_pivot.index.get_level_values(0).unique():
        group = df_pivot.loc[oversub]
        
        # 기하 평균 (GMEAN)
        # gmean 결과는 numpy 배열이므로 pandas Series로 변환
        gmean_row_np = gmean(group.select_dtypes(include=np.number))
        gmean_row = pd.Series(gmean_row_np, index=group.columns)
        summary_rows.append(((oversub, 'GMEAN'), gmean_row))

    # 요약 행으로 DataFrame 생성
    df_summary = pd.DataFrame.from_dict(dict(summary_rows), orient='index')

    # 기존 데이터와 요약 데이터 합치기
    df_pivot = pd.concat([df_pivot, df_summary])

rename_map = {
    '2DCONV': '2DC',
    'GESUMMV': 'GEMV',
    'XSBench': 'XSB',
    'hellinger': 'HEL',
    'nw': 'NW',
    'bfs': 'BFS'
}

df_pivot = df_pivot.rename(index=rename_map)

# ---------------------------------------------------------
# Dynamic Column Selection and Coloring
# ---------------------------------------------------------

# Define fixed colors for methods to ensure consistency
method_colors = {
    'SUV': 'sienna',
    'AC': 'steelblue',
    'ARIADNE': 'darkseagreen'
}

# Determine which columns to show based on availability
if 'SUV' in df_pivot.columns:
    column_order = ['SUV', 'AC', 'ARIADNE']
else:
    # If SUV is missing, show 2 bars
    column_order = ['AC', 'ARIADNE']

# Filter dataframe columns
df_pivot = df_pivot[[col for col in column_order if col in df_pivot.columns]]

print("Columns to plot:", df_pivot.columns.tolist())
print(df_pivot)

unique_methods = df_pivot.columns.tolist()

# ---------------------------------------------------------

desired_order = ['nooversub', '130', '175', '300']
# Filter desired_order to only include those present in the index
existing_levels = df_pivot.index.get_level_values(0).unique()
valid_order = [o for o in desired_order if o in existing_levels]

if valid_order:
    df_pivot = df_pivot.reindex(valid_order, level=0)
    
df_pivot = df_pivot.rename(index={'nooversub':'No oversubscription'})

# 그룹별(oversub) x 위치 계산
grouped = df_pivot.groupby(level=0, sort=False)
bar_centers = []       # 각 benchmark row의 중심 위치
bench_labels = []      # benchmark 이름
group_tick_positions = []  # 각 그룹(oversub)의 중앙 x 위치
group_labels = []          # oversub 레이블
positions = {}         # 그룹별 각 benchmark의 x 위치
current_position = 0
group_gap = 1.0        # 그룹 사이 간격
vline_positions = []
num_groups = len(grouped)

print("Number of groups:", num_groups)

for oversub, group in grouped:
    n = len(group)
    pos = np.arange(current_position, current_position + n)
    positions[oversub] = pos
    group_center = pos.mean()
    group_tick_positions.append(group_center)
    group_labels.append("\n\n\n" + oversub)
    for i, ((os_val, benchmark), _) in enumerate(group.iterrows()):
        bar_centers.append(pos[i])
        bench_labels.append(benchmark)
    
    line_pos = pos[-1] + 0.5 + group_gap / 2
    vline_positions.append(line_pos)

    current_position = pos[-1] + group_gap + 1

# Bar plot 그리기
plt.rcParams['font.family'] = 'Times New Roman'

fig, ax = plt.subplots(figsize=(14, 3))
methods = df_pivot.columns.tolist()
n_methods = len(methods)
bar_width = 0.8 / n_methods

for oversub, group in grouped:
    pos = positions[oversub]
    for i, ((os_val, benchmark), row) in enumerate(group.iterrows()):
        center = pos[i]
        for j, m in enumerate(methods):
            offset = (j - (n_methods - 1) / 2) * bar_width
            x = center + offset
            
            # Use the fixed color map
            color = method_colors.get(m, 'gray') # Default to gray if unknown
            
            ax.bar(x, row[m], width=bar_width, color=color, edgecolor='black')


# Primary x축: benchmark 레이블
ax.set_xticks(bar_centers)
ax.set_xticklabels(bench_labels, rotation=90, ha='center', fontsize=15)

# Y축 레이블 및 제목
ax.set_ylabel("Normalized\nExecution Time", fontsize=20)

ax.tick_params(axis='y', labelsize=13)

ax.grid(axis='y', linestyle='--', alpha=0.7, which='major')

# Secondary x축: 그룹(oversub) 레이블
secax = ax.secondary_xaxis('bottom')
secax.set_xticks(group_tick_positions)
secax.set_xticklabels(group_labels, size=18)
secax.tick_params(axis='x', length=0)

# 그룹 라벨 아래의 기본 눈금(major tick)은 숨김
secax.tick_params(axis='x', which='major', length=0)

# 그룹 경계에 보조 눈금(minor tick)을 추가하고, 선처럼 보이도록 스타일링
vline_positions.append(-1)
secax.set_xticks(vline_positions, minor=True)
secax.tick_params(axis='x', which='minor', direction='out', length=50, width=0.8, color='black')

#Graph x,y limitation
plt.xlim(-1, current_position - group_gap) # Adjusted xlim to fit data dynamically
plt.ylim(0, 3)

# 범례
# Create handles using the specific colors for the current unique_methods
handles = [plt.Rectangle((0,0),1,1, color=method_colors.get(m, 'gray')) for m in unique_methods]
ax.legend(handles, unique_methods, bbox_to_anchor=(0.5, 1.35), loc='upper center', ncols=6, frameon=False, fontsize=18)

#for ha in ax.legend_.legendHandles:
#    ha.set_edgecolor("black")

plt.tight_layout()
plt.subplots_adjust(left=0.065, bottom=0.38, right=0.995, top=0.890)

plt.savefig('./fig_9.png', format='png', bbox_inches='tight', pad_inches=0.01)
plt.show()
