import os

from search.github import IssuesSearch
import config

if not os.path.exists(config.OUTPUT_FOLDER):
    os.makedirs(config.OUTPUT_FOLDER)

IssuesSearch.run()

