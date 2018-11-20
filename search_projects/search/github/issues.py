from search.github.issue_worker import IssueWorker
import operator
import os

import config

class IssuesSearch:
    def run():
        last_created_at = None
        exit = False
        project_map = {}

        while(not exit):
            # TODO: instead "bug defect", use "bug OR defect"
            issue_worker = IssueWorker("Attribute attribute @", \
                    "created", True, "bug OR defect", "closed", \
                    last_created_at)
            issue_worker.analyze()
            
            temp_map = issue_worker.get_project_map()
            for key, value in issue_worker.get_project_map().items():
                if key in project_map:
                    project_map[key] = project_map[key] + value
                else:
                    project_map[key] = value

            exit = issue_worker.is_last_searcher()

            last_created_at = IssuesSearch.parse_date(str(issue_worker.get_last_created_at()))

        sorted_x = sorted(project_map.items(), key=operator.itemgetter(1), reverse=True)
        with open(os.path.join(config.OUTPUT_FOLDER, "repos.txt"), "w") as f:
            for key, value in sorted_x:
                f.write(key + ": " + str(value) + "\n")

    def parse_date(old_date):
        return "<" + old_date.replace(" ", "T") + "-03:00"
