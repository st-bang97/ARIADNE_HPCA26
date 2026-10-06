import os
import re
from collections import defaultdict
from scipy.stats import gmean
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

def average_runtimes(data_with_lists):
    """
    런타임 리스트를 포함하는 딕셔너리를 받아 평균 런타임을 계산한 딕셔너리로 변환합니다.
    """
    averaged_data = defaultdict(dict)
    for ratio, benchmarks in data_with_lists.items():
        for bench_name, runtimes in benchmarks.items():
            if runtimes:
                averaged_data[ratio][bench_name] = sum(runtimes) / len(runtimes)
    return averaged_data

def parse_benchmark_file(filepath):
    """
    하나의 벤치마크 파일을 파싱하여 런타임 값들의 평균을 계산합니다.
    """
    data = defaultdict(lambda: defaultdict(list))
    current_ratio = None
    try:
        with open(filepath, 'r') as f:
            for line in f:
                line = line.strip()
                if not line:
                    continue
                if line.isalnum():
                    current_ratio = line
                else:
                    match = re.match(r'(.+?)\s+GPU Runtime:\s+([\d.]+s?)', line)
                    if match and current_ratio is not None:
                        benchmark_name = match.group(1).strip()
                        runtime = float(match.group(2).replace('s', ''))
                        data[current_ratio][benchmark_name].append(runtime)
    except FileNotFoundError:
        print(f"오류: 파일을 찾을 수 없습니다. {filepath}")
        return None
    except Exception as e:
        print(f"오류: 파일 파싱 중 에러 발생 {filepath}: {e}")
        return None
    return average_runtimes(data)

def process_benchmark_directory(directory_path):
    """
    디렉토리 내 모든 벤치마크 파일을 처리하고, 정규화된 성능의 기하 평균을 계산합니다.
    """
    BASELINE_PINTIME = 100
    BASELINE_SDWEIGHT = 100000
    
    # 수정된 부분: 파일명 패턴 변경
    # "sstv_pintime_{숫자}_SDweight_{숫자}" 형식을 찾습니다.
    # 혹시 모를 .txt 확장자가 붙어있을 경우를 대비해 (?:\.txt)? 를 추가하여 유연하게 처리합니다.
    filename_pattern = re.compile(
        r'sstv_pintime_(\d+)_SDweight_(\d+)(?:\.txt)?$'
    )
    
    all_data = {}
    print(f"지정된 디렉토리를 스캔합니다: {directory_path}\n")
    for filename in os.listdir(directory_path):
        match = filename_pattern.match(filename)
        if match:
            pintime = int(match.group(1))
            sdweight = int(match.group(2))
            filepath = os.path.join(directory_path, filename)
            parsed_data = parse_benchmark_file(filepath)
            if parsed_data:
                all_data[(pintime, sdweight)] = parsed_data

    baseline_key = (BASELINE_PINTIME, BASELINE_SDWEIGHT)
    if baseline_key not in all_data:
        print(f"오류: 기준 파일(pintime={BASELINE_PINTIME}, SDweight={BASELINE_SDWEIGHT})을 찾을 수 없습니다.")
        # 디버깅을 위해 현재 로드된 키들을 출력해줍니다.
        if all_data:
            print(f"현재 로드된 파일들의 키(pintime, sdweight): {list(all_data.keys())}")
        return None
        
    baseline_data = all_data[baseline_key]
    print("기준(Baseline) 데이터 로딩 및 평균 계산 완료.\n")

    geomean_results = defaultdict(dict)
    for (pintime, sdweight), scenario_data in all_data.items():
        for ratio, benchmarks in scenario_data.items():
            if ratio not in baseline_data:
                continue
            
            normalized_performances = []
            for bench_name, runtime in benchmarks.items():
                if bench_name in baseline_data[ratio] and runtime > 0:
                    baseline_runtime = baseline_data[ratio][bench_name]
                    normalized_perf = baseline_runtime / runtime
                    normalized_performances.append(normalized_perf)
            
            if normalized_performances:
                geomean_results[(pintime, sdweight)][ratio] = gmean(normalized_performances)

    if not geomean_results:
        print("결과를 표시할 데이터가 없습니다.")
        return None

    df = pd.DataFrame.from_dict(geomean_results, orient='index')
    df.index = pd.MultiIndex.from_tuples(df.index, names=['pintime', 'SDweight'])
    df = df.sort_index()
    return df

# --- 메인 스크립트 실행 ---
if __name__ == '__main__':
    current_directory = './'
    # 1. 데이터 처리 및 정규화된 성능 계산
    df_results = process_benchmark_directory(current_directory)

    if df_results is not None:
        print("--- oversubscription 별 정규화된 성능의 기하 평균 ---")
        print(df_results.to_string(float_format="%.4f"))
        
        # 2. 그래프를 위한 데이터 준비
        df_geomean_overall = df_results.apply(gmean, axis=1)
        df_geomean_overall = df_geomean_overall.reset_index()
        df_geomean_overall.columns = ['pintime', 'SDweight', 'geomean_perf']
        df_plot = df_geomean_overall.pivot(index='pintime', columns='SDweight', values='geomean_perf')
        
        print("\n--- 그래프용 데이터 (Pintime에 따른 SDweight별 전체 성능) ---")
        print(df_plot.to_string(float_format="%.4f"))

        # 3. 요청된 새 바 그래프 그리기
        plt.rcParams['font.family'] = 'Times New Roman'
        fig, ax = plt.subplots(figsize=(8, 3.2))

        unique_sdweights = sorted(df_plot.columns.tolist())
        colors = plt.cm.Set2(np.linspace(0, 1, len(unique_sdweights)))
        color_dict = dict(zip(unique_sdweights, colors))
        
        pintimes = df_plot.index
        n_pintimes = len(pintimes)
        x = np.arange(n_pintimes) # pintime 그룹의 위치
        n_sdweights = len(unique_sdweights)
        bar_width = 0.8 / n_sdweights # 각 그룹 내 바의 너비

        # 각 SDweight에 대해 바 그래프 그리기
        for i, sdweight in enumerate(unique_sdweights):
            offset = (i - (n_sdweights - 1) / 2) * bar_width
            heights = df_plot[sdweight]
            label_text = f'{int(sdweight / 1000)}us'
            ax.bar(x + offset, heights, bar_width, label=label_text, color=color_dict[sdweight], edgecolor='black')

        # x축 레이블 및 눈금 설정
        ax.set_xlabel("Pintime", fontsize=18)
        ax.set_xticks(x)
        ax.set_xticklabels([f'{pt}ms' for pt in pintimes], rotation=0, ha='center', fontsize=18)

        # y축 레이블 설정
        ax.set_ylabel("Normalized\nGeomean Performance", fontsize=20)
        ax.tick_params(axis='y', labelsize=15)
        #ax.set_ylim(0.75, 1.01)
        
        # y축에 수평선(기준선) 추가
        ax.axhline(1.0, color='grey', linestyle='--', linewidth=1)

        # 그리드 추가
        ax.grid(axis='y', linestyle='--', alpha=0.7)

        # 범례
        legend = ax.legend(title='SD Weight', bbox_to_anchor=(0.5, 1.39), loc='upper center', 
                  ncols=len(unique_sdweights), frameon=False, fontsize=16)
        legend.get_title().set_fontsize('18')

        plt.tight_layout()
        plt.subplots_adjust(left=0.124, bottom=0.190, right=0.997, top=0.81)

        # 파일로 저장
        plt.savefig('./fig_13.png', format='png', dpi=300)
        
