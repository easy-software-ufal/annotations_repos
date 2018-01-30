from github import Github
import re
import os

import config

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

    def is_valid(self):
        return self.valid

    def get_project_url(self):
        return self.url;

    def record_info(self):
        folder_name = self.url.replace("https://github.com/","")
        folder_name = folder_name.replace("/","_")
        
        if not os.path.exists(os.path.join(config.OUTPUT_FOLDER, folder_name)):
            os.makedirs(os.path.join(config.OUTPUT_FOLDER, folder_name))
        
        if not os.path.exists(os.path.join(config.OUTPUT_FOLDER, folder_name, str(self.issue.id))):
            with open(os.path.join(config.OUTPUT_FOLDER, folder_name, str(self.issue.id)), "w") as f:
                f.write("issue: "+self.title+"\n")
                f.write("url: "+self.issue.url + "\n")
                f.write("project: "+self.url + "\n")
                f.write("labels: "+ "\n")
                for label in self.issue.labels:
                    f.write("   "+label.name + "\n")
                f.write("------------------------\n")
                f.write(self.body)
