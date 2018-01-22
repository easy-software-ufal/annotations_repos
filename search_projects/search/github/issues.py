from github import Github
import github_token
import os
from time import sleep

class IssuesSearch:
    def run():
        g = Github(github_token.TOKEN)

#        for repo in g.get_user().get_repos():
#            print(repo.name)
        s = g.search_issues("annotation @", "created", "desc", language="Java", label="bug", state="closed")
        '''for issue in s:
            print(issue.title)
            print(issue.body)
            print("---------------------")
            sleep(10)'''
        # TODO: for each issue...
        for issue in s:
            # TODO: get issue body
            ibody = issue.body
            # TODO: search for annotations words
            # TODO: catch repo url and count, and issue url (write in json)
            # TODO: check if project is maven (write in json)
                # TODO: check if contains dependencies like spring, jboss and others (write in json)
        # TODO: sumarize projects by order of issues (get json)
