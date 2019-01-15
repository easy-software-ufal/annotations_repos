# Generate Tables
This script generates two tables:
- Faults and operators distributed by Java projects 
- Faults and operators distributed by C# projects 

This script is written using python 3. PyGitHub is used to access GitHub
API and then gather data from this repository. Pandas is used to generate
 LaTeX tables.
 
Use
```
python ./generate_tables.py
```
To generate csv and LaTeX tables.
