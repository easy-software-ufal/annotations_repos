from github import Github
import re

class IssueProcess:
    def __init__(self, issue):
        self.url = issue.repository.html_url
        self.valid = False
        self.issue = issue
        self.body = issue.body
        self.title = issue.title

    def contains_annotation(self):
        searchObj1 = re.search("\\s@[a-zA-Z]+", self.title)
        searchObj2 = re.search("\\s@[a-zA-Z]+", self.body)
        return (searchObj1 or searchObj2 or ("annotation" in self.body.lower()) \
                or ("annotation" in self.title.lower()))

    def analyze(self):
        self.valid = False
        for label in self.issue.labels:
            if (label.name.lower() in ["bug", "defect"]) and \
                    self.contains_annotation():
                self.valid = True
                break
        if self.valid:
            print(self.title)
            print(self.body + "\n")

    def is_valid(self):
        return self.valid

    def get_project_url(self):
        return self.url;

    # TODO: implement it!
    def record_info(self):
        pass
