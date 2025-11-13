#!/usr/bin/env python3
# created by aaiakovlev(can4k)

import subprocess
import csv

# SMALL or BIG (square size)
def compile_program(variant='BIG'):
    """Compiles main.cpp with required flags"""
    try:
        result = subprocess.run([
            'g++', '-std=c++17', '-DEXP', f"-D{variant}",
            'main.cpp', '-o', 'main'
        ], capture_output=True, text=True, cwd='.')
        
        return result.returncode == 0
    except Exception as e:
        print(e)
        return False

def run_experiment(tries):
    """Runs experiment with specified number of tries"""
    try:
        result = subprocess.run(
            ['./main'],
            input=str(tries),
            capture_output=True,
            text=True,
            cwd='.'
        )
        
        if result.returncode != 0:
            return None
        
        return float(result.stdout.strip())
    except Exception:
        return None

def main(min_tries, max_tries, step, variant):
    """Main function to conduct experiments"""
    if not compile_program(variant):
        return
    
    tries_list = range(min_tries, max_tries + step, step)
    csv_filename = f'experiment_results_{variant}.csv'
    
    with open(csv_filename, 'w', newline='', encoding='utf-8') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(['Tries', 'Result'])
        
        for tries in tries_list:
            result = run_experiment(tries)
            if result is not None:
                writer.writerow([tries, result])
                print(f"Tries: {tries}, Result: {result}")

if __name__ == "__main__":
    main(100, 100000, 500, "SMALL")
