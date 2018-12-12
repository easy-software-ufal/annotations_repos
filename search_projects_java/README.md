# Find bugs related to Code annotations.
#### Java version.
This script is written with python. It crawls over Java projects hosted on GitHub, gets its closed issues and then returns those containing the word 'Annotation' or Java code Annotation regex @[A-z]+. Finally, it saves the results at **reports** directory, over directories named after projects, each contaning the filtered issues.

### Requirements.

Most recent version of **python 3.x** interpreter. Make sure you have **pip** tool available (for Microsoft Windows, it comes bundled with the interpreter; For GNU/Linux, install **python-pip**). For GNU/Linux, **python-dev** package is recommended.

Using **pip** tool, install (for Ubuntu, use "sudo -H" before each command):
```terminal
pip install virtualenv --upgrade
pip install freeze --upgrade
```

### GitHub token.

Create a file named `github_token.py` at the script's root directory. Inside the file, declare a constant named `TOKEN`. This constant has to be assigned to the token string. It should look like this:
```
TOKEN="6f49fc9cbe66449b58f26a007a841f7b82ab9d13"
```
Where 6f49... should be your GitHub account token. 

To generate a token, go to GitHub settings, open `development settings`, then go to `Personal access tokens`. Click on `Generate new token`, check `public_repo` (below `repo`) boxes, then click on `Generate token` at the end of page. Copy the token (store it somewhere safe) then paste it inside quotes, assigning it to the `TOKEN` constant.

**WARNING**: `github_token.py` is ignored by git, it contains sensitive information (your GitHub account token). See `.gitignore` for more details about ignored files.

### First time use.

Create a virtual environment directory by running the following command at the scrip root directory:

**Linux**:
```terminal
virtualenv -p python3 .venv
```
**Windows**:
```terminal
virtualenv -p python .venv
```

This will create a *.venv* (hidden) directory at the script's root directory. It contains a python3 interpreter (with *python* name), libraries and tools. This allows us to keep libraries in specific versions, being independet of libraries installed on the system. To activate the virtual environment, run:

**Linux**:
```terminal
source .venv/bin/activate
```
**Windows**:
```terminal
.venv\Scripts\activate
```

Now, install the project libraries:

```terminal
pip install -r requirements.txt
```

### Activate the virtual environment.

If the virtual environment has not been actived yet, run:

**Linux**:
```terminal
source .venv/bin/activate
```
**Windows**:
```terminal
.venv\Scripts\activate

## If you want to instal new libraries in the virtual environment

First, activate the virtual environment. Then, install the library you wish with pip:

```terminal
pip install <package>
```

You may update *requirements.txt* so your new libraries will always be installed on the virutal environment:

```terminal
pip freeze > requirements.txt
```

### To deactivate the virtual environment.

Run:
```terminal
deactivate
```

