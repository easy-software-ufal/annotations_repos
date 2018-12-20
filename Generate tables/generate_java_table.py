# Author: Pedro Pinheiro
# This script generates a table mapping Java projects and its bug count, plus mutation operators

from generic_projects_table_generator import generate_table


def generate():
    generate_table('Java', 'java_table')
