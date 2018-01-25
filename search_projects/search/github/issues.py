from github import Github
import github_token
import os
from time import sleep
import datetime

class IssuesSearch:
    def run():
        g = Github(github_token.TOKEN)

#        for repo in g.get_user().get_repos():
#            print(repo.name)
        s = g.search_issues("Annotation annotation @", "created", "desc", language="Java", label="bug OR defect", state="closed", \
                created="<2017-03-22T11:12:46-03:00")
        print(s.totalCount)
        # TODO: for each issue...
        count = 0
        issue = None
        while count < s.totalCount:
            try:
                issue = s[count]
                # TODO: get issue body
                ibody = issue.body
                # TODO: search for annotations words
                #print(issue.title)
                #print(issue.labels[0].name)
                ok = False
                for label in issue.labels:
                    if label.name.lower() in ["bug","defect"]:
                        ok = True
                        break
                if not ok:
                    print(issue.labels)
                #sleep(1)
                # TODO: catch repo url and count, and issue url (write in json)
                # TODO: check if project is maven (write in json)
                    # TODO: check if contains dependencies like spring, jboss and others (write in json)
                count += 1
            except Exception as e:
                print(str(e))
                print(issue.created_at)
                print(count)
                print(g.rate_limiting)
                print(g.rate_limiting_resettime)
                print(datetime.datetime.fromtimestamp(g.rate_limiting_resettime).strftime('%Y-%m-%d %H:%M:%S'))
                sleep(10)
        # TODO: sumarize projects by order of issues (get json)
