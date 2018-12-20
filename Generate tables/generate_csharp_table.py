# Author: Pedro Pinheiro
# This script generates a table mapping Csharp projects and its bug count, plus mutation operators

from generic_projects_table_generator import generate_table


def generate():
    generate_table('C#', 'csharp_table')

