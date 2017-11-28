#!/usr/bin/python
import os
import shutil

'''
how to get reports files: git log > repo_log
'''

REPORTS_FOLDER = "reports"
OUTPUT_FOLDER = "output"

count = 0
commit_block = []

def analyze_block(filename):
    if any("annotation" in s or "Annotation" in s for s in commit_block):
        with open(os.path.join(OUTPUT_FOLDER, filename), 'a') as output_report:
            for line in commit_block:
                output_report.write(line)

def read_reports(folder):
    for report_file in os.listdir(folder):
        with open(os.path.join(folder, report_file), "r") as f:
            for line in f:
                if line.startswith("commit"):
                    count=+1
                    analyze_block(report_file)
                    del commit_block[:]
                commit_block.append(line)

if not os.path.exists(REPORTS_FOLDER):
    os.makedirs(REPORTS_FOLDER)
if os.path.exists(OUTPUT_FOLDER):
    shutil.rmtree(OUTPUT_FOLDER)
os.makedirs(OUTPUT_FOLDER)
    
read_reports(REPORTS_FOLDER)
