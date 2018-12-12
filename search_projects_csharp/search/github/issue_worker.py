from github import Github, GithubException
from time import sleep, time
import datetime
import math
import sys
import os
from multiprocessing import Lock

import github_token
from search.github.issue_process import IssueProcess

class IssueWorker:
    def __init__(self, terms, order_by, desc, labels, state, start_created_at):
        """
        param terms: each search terms, divided by space
        param order_by: "created", "comments" and "updated"
        param desc: boolean.
        param labels: each label divided by OR operator
        param state: "open" or "closed"
        param start_created_at: string, string expression to start results.
                                maybe None
        """
        self.project_map = {}
        self.last_searcher = False
        self.last_created_at = None

        self.terms = terms
        self.order_by = order_by
        if desc == True:
            self.desc = "desc"
        else:
            self.asc = "asc"
        self.labels = labels
        self.state = state
        self.mutex = Lock()
        if start_created_at == None or start_created_at == "":
            self.start_created_at = ""
        else:
            self.start_created_at = start_created_at

    def saveStatus(self,variable,value):
        with open("status.conf","+") as file:
            with self.mutex:
                asc = {}
                for line in file:
                    line = line.split('=')
                    asc["".join(line[0].strip())] = "".join(line[1].strip())
                asc[variable] = str(value)
                for k,v in asc:
                    k.join(" = ".join(v)) 
                    file.write(k)

    def readStatus(self):
        asc = {}
        with open("status.conf","r") as file:
            with self.mutex:
                for line in file:
                    line = line.split('=')
                    asc["".join(line[0].strip())] = "".join(line[1].strip())
        return asc
         
    def analyze(self):
        github_obj = Github(github_token.TOKEN)
        
        if self.start_created_at in [None, ""]:
            results = github_obj.search_issues(self.terms, self.order_by, \
                    self.desc, language = "C#", label = self.labels, \
                    state = self.state)
        else:
            results = github_obj.search_issues(self.terms, self.order_by, \
                    self.desc, language = "C#", label = self.labels, \
                    state = self.state, created = self.start_created_at)
        
        count = 0
        max_count = 1000
        issue = None
        if results.totalCount < 1000:
            self.last_searcher = True
            max_count = results.totalCount

        print("total: " + str(results.totalCount))
        print(str(count) + " of " + str(max_count - 1))

#        status = self.readStatus()
#        count = int (status["count"])

        while count < max_count:
            try:
                issue = results[count]
                
                sys.stdout.write("\033[F") #back to previous line
                sys.stdout.write("\033[K") #clear line
                print(str(count) + " of " + str(max_count - 1))

                issue_process = IssueProcess(issue)
                
                issue_process.analyze()
                if issue_process.is_valid():
                    if issue_process.get_project_url() in self.project_map:
                        self.project_map[issue_process.get_project_url()] += 1
                    else:
                        self.project_map[issue_process.get_project_url()] = 1
                    issue_process.record_info()

                self.last_created_at = issue.created_at
                count += 1
#                self.saveStatus("count",count)
            except GithubException as e:
                print("\n######################")
                msg = str(e)
                print("error: " + msg)
                
                time_to_reset = github_obj.rate_limiting_resettime - time()
                time_to_reset = math.ceil(time_to_reset)

                if "Repository access blocked" in msg:
                    count += 1
                    time_to_reset = 0
                    print("Ignoring repository, reason:")
                    print(msg)

                print(" waiting " + str(time_to_reset) + " seconds.....")
                print(" time to reset: " + datetime.datetime.fromtimestamp( \
                        github_obj.rate_limiting_resettime).strftime( \
                        '%Y-%m-%d %H:%M:%S'))
                sleep(time_to_reset)
                print("########################\n")
            except KeyboardInterrupt:
                try:
                    sys.exit(0)
                except SystemExit:
                    os._exit(0)
            except:
                count += 1

    def get_project_map(self):
        return self.project_map

    def is_last_searcher(self):
        return self.last_searcher

    def get_last_created_at(self):
        return self.last_created_at
