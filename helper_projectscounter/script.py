from github import Github
from collections import  defaultdict
import MyToken

g = Github(MyToken.TOKEN)

our_repo = g.get_repo("easy-software-ufal/annotations_repos")
csharp_label = our_repo.get_label("C#")
our_issues = our_repo.get_issues(state='open', labels=[csharp_label])

project_counter = defaultdict(int)
project_domain = defaultdict(lambda: "1")
project_operators = defaultdict(list)
counter=0
for issue in our_issues:
    key = issue.title.lstrip().split(" ")[0]
    #Filter out non operators labels
    labels = list(filter(lambda x: x.name != "C#" 
        and x.name != "test"
        and x.name != "wrong processing" 
        and x.name != "misuse", issue.labels))
    labels = [x.name for x in labels]

    project_counter[key] += 1
    project_operators[key] += labels

    counter += 1
    #Attach description to projects
    if len(project_domain[key]) == 1:
        description = g.get_repo(key).description
        if description != None:
            project_domain[key] = description
        else:
            project_domain[key] = "No description"


with open("projects_table", "a") as file:
    file.write("Project Name,Domain,Operators,Number of Faults\n")
    for k, v in project_counter.items() :
        line = [k.split('/')[1],'\"'+project_domain[k]+'\"',' '.join(list(set(project_operators[k]))),str(v)]

        file.write(','.join(line)+'\n')

print (counter)
