# created by aaiakovlev(can4k)

import pandas as pd
import matplotlib.pyplot as plt
import sys
import glob
import os

def get_real_answer():
    try:
        with open('real_answer.txt', 'r') as f:
            return float(f.read().strip())
    except:
        return None


def plot_both():
    plt.figure(figsize=(12, 8))
    
    df_big = pd.read_csv('results/experiment_results_BIG.csv')
    df_small = pd.read_csv('results/experiment_results_SMALL.csv')
    
    plt.plot(df_big['Tries'], df_big['Result'], 'o-', markersize=1, linewidth=1, color='blue', label='BIG')
    plt.plot(df_small['Tries'], df_small['Result'], 'o-', markersize=1, linewidth=1, color='green', label='SMALL')
    
    real_value = get_real_answer()
    if real_value:
        plt.axhline(y=real_value, color='orange', linestyle='-', linewidth=2, label=f'Real answer: {real_value:.6f}')
    
    plt.xlabel('Tries')
    plt.ylabel('Result')
    plt.title('BIG vs SMALL Experiment Results')
    plt.legend()
    plt.grid(True, alpha=0.3)
    plt.tight_layout()
    
    plt.savefig('both_experiments.png', dpi=300, bbox_inches='tight')
    plt.show()

def plot_relative_error():
    plt.figure(figsize=(12, 8))
    
    df_big = pd.read_csv('results/experiment_results_BIG.csv')
    df_small = pd.read_csv('results/experiment_results_SMALL.csv')
    
    real_value = get_real_answer()
    if real_value:
        error_big = abs(df_big['Result'] - real_value) / real_value * 100
        error_small = abs(df_small['Result'] - real_value) / real_value * 100
        
        plt.plot(df_big['Tries'], error_big, 'o-', markersize=1, linewidth=1, color='blue', label='BIG relative error')
        plt.plot(df_small['Tries'], error_small, 'o-', markersize=1, linewidth=1, color='green', label='SMALL relative error')
    
    plt.xlabel('Tries')
    plt.ylabel('Relative Error (%)')
    plt.title('Relative Error from Real Answer: BIG vs SMALL')
    plt.legend()
    plt.grid(True, alpha=0.3)
    plt.tight_layout()
    
    plt.savefig('relative_error_plot.png', dpi=300, bbox_inches='tight')
    plt.show()

if __name__ == "__main__":
    plot_both()
    plot_relative_error()