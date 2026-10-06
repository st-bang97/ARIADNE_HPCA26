import os
import re
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import gmean

# ==================================================================
# ===== 수정된 부분: 확장자가 없는 파일명을 읽도록 변경 =====
# 읽어올 파일명(Key)과 해당 파일이 그래프에서 가질 method 이름(Value) 매핑
target_files = {
    'ARIADNE': 'ARIADNE',
    'no_PL': 'ARIADNE without PL',
    'no_PL_SD': 'ARIADNE without PL, SD'
}

records = []

for filename, method in target_files.items():
    if not os.path.exists(filename):
        print(f"Warning: '{filename}' 파일을 찾을 수 없습니다. (현재 경로: {os.getcwd()})")
        continue
        
    with open(filename, "r") as f:
        lines = f.readlines()
        
    current_oversub = None
    for line in lines:
        line = line.strip()
        if not line:
            continue
        # 정규표현식: nooversub 또는 숫자만 있는 줄을 oversub 정보로 인식
        if re.match(r'^(nooversub|\d+)$', line):
            current_oversub = line
        else:
            # Benchmark 이름과 Runtime 파싱
            m = re.match(r'^(.+?)\s+Runtime:\s+([\d\.]+)s$', line)
            if m and current_oversub is not None:
                benchmark = m.group(1).strip()
                runtime = float(m.group(2))
                records.append({
                    'oversub': current_oversub,
                    'benchmark': benchmark,
                    'method': method, # 위 딕셔너리에서 정의한 이름 사용
                    'runtime': runtime
                })

# ===== 수정된 부분 끝 =====
# ==================================================================

df = pd.DataFrame(records)

print("로드된 데이터:")
print(df.head())

if not df.empty:
    # Benchmark 이름에서 " GPU" 제거
    df['benchmark'] = df['benchmark'].str.replace(r' GPU$', '', regex=True)

    # 평균 runtime 계산: 동일 (oversub, benchmark, method) 조합에 대해 평균
    df_mean = df.groupby(['oversub', 'benchmark', 'method'], as_index=False)['runtime'].mean()

    # Pivot 및 정규화: SUV 기준
    df_pivot = df_mean.pivot(index=['oversub', 'benchmark'], columns='method', values='runtime')
    
    # 정규화 기준 컬럼 설정
    normal_val = 'ARIADNE without PL, SD'
    
    # 데이터가 존재하는지 확인 후 정규화
    if normal_val in df_pivot.columns:
        for col in df_pivot.columns:
            if col == normal_val:
                continue
            df_pivot[col] = df_pivot[col] / df_pivot[normal_val]
        df_pivot[normal_val] = 1
    else:
        print(f"주의: 정규화 기준 컬럼 '{normal_val}'이 데이터에 없습니다.")

    # AVG(산술 평균) 및 GMEAN(기하 평균) 행 계산
    summary_rows = []
    for oversub in df_pivot.index.get_level_values(0).unique():
        group = df_pivot.loc[oversub]
        
        # 기하 평균 (GMEAN)
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

    column_order = ['ARIADNE without PL, SD', 'ARIADNE without PL', 'ARIADNE']
    # 존재하는 컬럼만 선택하여 정렬
    existing_cols = [col for col in column_order if col in df_pivot.columns]
    df_pivot = df_pivot[existing_cols]

    print(df_pivot)

    # 색상 지정
    base_colors = ["sienna", "steelblue", "darkseagreen", 'black']
    color_dict = dict(zip(column_order, base_colors))

    desired_order = ['nooversub', '130', '175', '300']
    available_indices = [idx for idx in desired_order if idx in df_pivot.index.get_level_values(0)]
    df_pivot = df_pivot.reindex(available_indices, level=0)
    df_pivot = df_pivot.rename(index={'nooversub':'No oversubscription'})

    # 그룹별(oversub) x 위치 계산
    grouped = df_pivot.groupby(level=0, sort=False)
    bar_centers = []       
    bench_labels = []      
    group_tick_positions = [] 
    group_labels = []          
    positions = {}         
    current_position = 0
    group_gap = 1.0        
    vline_positions = []
    num_groups = len(grouped)

    print(f"Groups found: {num_groups}")

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
    bar_width = 0.8 / n_methods if n_methods > 0 else 0.8

    for oversub, group in grouped:
        pos = positions[oversub]
        for i, ((os_val, benchmark), row) in enumerate(group.iterrows()):
            center = pos[i]
            for j, m in enumerate(methods):
                offset = (j - (n_methods - 1) / 2) * bar_width
                x = center + offset
                bar_height = row[m] if row[m] > 0 else 1e-9 
                ax.bar(x, bar_height, width=bar_width, color=color_dict.get(m, 'gray'), edgecolor='black')


    # Primary x축
    ax.set_xticks(bar_centers)
    ax.set_xticklabels(bench_labels, rotation=90, ha='center', fontsize=15)

    # Y축 레이블 및 제목
    ax.set_ylabel("Normalized\nExecution Time", fontsize=20)
    ax.tick_params(axis='y', labelsize=13)
    ax.grid(axis='y', linestyle='--', alpha=0.7, which='major')
    ax.grid(axis='y', linestyle=':', alpha=0.5, which='minor')

    # Secondary x축
    secax = ax.secondary_xaxis('bottom')
    secax.set_xticks(group_tick_positions)
    secax.set_xticklabels(group_labels, size=18)
    secax.tick_params(axis='x', length=0)
    secax.tick_params(axis='x', which='major', length=0)
    
    vline_positions.append(-1)
    secax.set_xticks(vline_positions, minor=True)
    secax.tick_params(axis='x', which='minor', direction='out', length=50, width=0.8, color='black')

    plt.xlim(-1, current_position - group_gap) 
    
    # 범례
    handles = [plt.Rectangle((0,0),1,1, color=color_dict.get(m, 'gray'), edgecolor='black') for m in methods]
    ax.legend(handles, methods, bbox_to_anchor=(0.5, 1.35), loc='upper center', ncols=6, frameon=False, fontsize=18, edgecolor='black')

    for ha in ax.legend_.legend_handles:
        ha.set_edgecolor("black")

    plt.tight_layout()
    plt.subplots_adjust(left=0.065, bottom=0.38, right=0.995, top=0.890)

    plt.savefig('./fig_11.png', format='png', bbox_inches='tight', pad_inches=0.01)
    plt.show()
else:
    print("데이터가 없어 그래프를 그리지 못했습니다.")
