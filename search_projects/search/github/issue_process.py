from github import Github

class IssueProcess:
    def __init__(self, issue):
        self.url = None
        self.valid = False
        self.issue = issue

    # TODO: implement it!
    def analyze(self):
        print("analyzing issue: " + self.issue.title)

        # self.body = self.issue.body

        self.valid = False
        for label in self.issue.labels:
            if label.name.lower() in ["bug", "defect"]:
                self.valid = True
                break
        if not self.valid:
            print(self.issue.labels)

    def is_valid(self):
        return self.valid

    def get_project_url(self):
        return self.url;

    # TODO: implement it!
    def record_info(self):
        pass
