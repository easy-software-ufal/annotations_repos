# Author: Pedro Pinheiro
# This script generates a table mapping Csharp projects and its bug count, plus mutation operators
import github
from collections import  defaultdict
from tempfile import mkstemp
import MyToken
import re
from pandas import DataFrame
from pandas import read_csv

IGNORE = {'test', 'wrong processing', 'misuse', 'easy to explain',
          'C#', 'Java', 'Multiple Changes', 'no operator', 'complex'}
SUPPORTED = {'Java', 'C#'}
PROJECT_ID_REGEX = re.compile(r'(\S+\/\S+)')
GIT_REPO = "easy-software-ufal/annotations_repos"


def generate_table(target: str, file_name: str):
    g = github.Github(MyToken.TOKEN)

    if target not in SUPPORTED:
        print(target + "  is unsupported!")
        return

    our_repo = g.get_repo(GIT_REPO)
    target_label = our_repo.get_label(target)
    our_issues = our_repo.get_issues(state='open', labels=[target_label])

#   Count how many bugs
    project_counter = defaultdict(int)
#   Domain of the project string, given by the project maintainer
    project_domain = defaultdict(str)
#   Operators mapped to project given by labels
    project_operators = defaultdict(list)
#   Visited projects
    visited_projects = defaultdict(lambda: False)
    counter = 0
    for issue in our_issues:
        key_match = PROJECT_ID_REGEX.search(issue.title)

        key = ''
        if key_match:
            key = key_match.group(0)
            key = key.rstrip(':')

        else:
            print(issue.title+'\n')
            print('I can\'t understand this string. Can you type maintainer/project for me?\n')
            key = input()

#        key = issue.title.lstrip().split(" ")[0]
#       Filter out non operators labels
        labels = list(filter(lambda x: x.name not in IGNORE, issue.labels))
#       Pick name string only
        labels = [x.name for x in labels]

        project_counter[key] += 1
        project_operators[key] += labels

        counter += 1
#       Attach description/domain to projects
        if not visited_projects[key]:
            try:
                project_domain[key] = g.get_repo(key).description
                if project_domain[key] is None:
                    project_domain[key] = 'No description provided.'
            except github.UnknownObjectException:
                print(key + ' Not Found. Project description will have to be defined manually.')
            visited_projects[key] = True

    bug_count = sum(project_counter.values())
    print(target + ' bugs: ' + str(bug_count) + '\n')

    sorted_projects_names = sorted(project_counter.keys(), key=lambda x: x.split('/')[1].lower())

    with open(file_name + '.csv', 'a') as file:
        # Wipe previous file contents
        file.seek(0)
        file.truncate()
        file.write("Project Name,Domain,Operators,Number of Faults\n")
        for k in sorted_projects_names:
            # This is a list containing:
            # Project name
            # , project domain
            # , project operators
            # , bug count
            line = [k.split('/')[1]
                    , '\"' + project_domain.get(k, k + 'Is not mapped!') + '\"'
                    , '\"' + ', '.join(list(set(project_operators[k]))) + '\"'
                    , str(project_counter[k])]

            file.write(','.join(line)+'\n')
        file.write('TOTAL, , ,' + str(bug_count))

    with open(file_name + '.csv', 'r') as file:
        csv = read_csv(file)
        latex = DataFrame.to_latex(csv)
        with open(file_name + '.latex', 'a') as latex_file:
            latex_file.seek(0)
            latex_file.truncate()
            latex_file.write(latex)



