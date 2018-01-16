search projects with bugs and annotations

## Requirements

This works with Python 3. Therefore, install more recent **python 3.x** interpreter. And make sure to have **pip** tool available (in windows, this comes with more recent interpreter; in linux, install **python-pip**). In linux, **python-dev** is recomended.

With **pip** tool, install (in ubuntu, use "sudo" before each command):
```terminal
pip install virtualenv --upgrade
pip install freeze --upgrade
```

## First time use

Create virtual environment folder by running the following command in the root project:

**Linux**:
```terminal
virtualenv -p python3 .venv
```
**Windows**:
```terminal
virtualenv -p python .venv
```

This will create a *.venv* folder in the root project. This folder contains python3 interpreter (with *python* name), libraries and tools. This allow to keep libraries in the specific versions, dispite the libraries of the system. To activate this virtual environment, run:

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

## Activate the virtual environment

If the virtual environment is not yet active, run:

**Linux**:
```terminal
source .venv/bin/activate
```
**Windows**:
```terminal
.venv\Scripts\activate

## Install new libraries in the virtual environment

First, activate the virtual environment. After that, install the python library with pip:

```terminal
pip install <package>
```

And update the *requirements.txt*:

```terminal
pip freeze > requirements.txt
```

## Deactivate the virtual environment

Run:
```terminal
deactivate
```

