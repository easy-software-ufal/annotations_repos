from github import Github
import github_token

class IssuesSearch:
    def run():
        g = Github(github_token.TOKEN)

        for repo in g.get_user().get_repos():
            print(repo.name)
