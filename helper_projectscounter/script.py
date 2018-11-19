from github import Github
from collections import  defaultdict
import MyToken

g = Github(MyToken.TOKEN)

our_repo = g.get_repo("easy-software-ufal/annotations_repos")
csharp_label = our_repo.get_label("C#")
our_issues = our_repo.get_issues(state='open', labels=[csharp_label])

project_counter = defaultdict(int)
counter=0
for issue in our_issues:
    key = issue.title.split(" ")[0]
    if len(key) > 0:
        project_counter[key] += 1
    else:
        project_counter[issue.title] += 1
    counter += 1

with open("projects_table", "a") as file:
    file.write("Project,Bugs\n")
    for key, value in project_counter.items():
        file.write(key+","+str(value)+'\n')

print (counter)
