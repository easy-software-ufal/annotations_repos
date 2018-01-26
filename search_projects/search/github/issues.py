from search.github.issue_worker import IssueWorker

class IssuesSearch:
    def run():
        last_created_at = None
        exit = False

        while(not exit):
            issue_worker = IssueWorker("Annotation annotation @", \
                    "created", True, "bug OR defect", "closed", \
                    last_created_at)
            issue_worker.analyze()
            print("---------------\n")
            print(issue_worker.get_project_map())

            exit = issue_worker.is_last_searcher()

            last_created_at = IssuesSearch.parse_date(str(issue_worker.get_last_created_at()))
            print(last_created_at)


        # TODO: sumarize projects by order of issues (get json)

    def parse_date(old_date):
        return "<" + old_date.replace(" ", "T") + "-03:00"
