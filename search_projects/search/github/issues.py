from github import Github
import github_token
import os
from time import sleep

class IssuesSearch:
    def run():
        g = Github(github_token.TOKEN)

#        for repo in g.get_user().get_repos():
#            print(repo.name)
        s = g.search_issues("annotation @", "comments", "desc", language="Java", label="bug")
        '''for issue in s:
            print(issue.title)
            print(issue.body)
            print("---------------------")
            sleep(10)'''
        print(s.size)
