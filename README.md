## Mutation Operators for Code Annotations
This repository contains all scripts used on our paper.

`Example` contains a motivating example code (Java) for proposing mutation operators for code annotations.

`Generate tables`
generates csv and LaTex tables containing data regarding code annotation related faults frequency and mutation operators, given software project.

`Miner`
mine issues and pull requests given criteria. The criteria we have used is explained on readme file over Miner folder.    

#### Following table guides readers over terms used regarding code annotations.

| Paper           | Java                    | C#                        |
| --------------- |:-----------------------:| -------------------------:|
| Code annotation | Annotation              | Attribute                 |
|      -          | @Example                | \[Example\]               |
| Attribute       | Attribute               | Parameter                 |
| -               | @Example(exampleAttr=v) | \[Example(exampleAttr=v)\]|


#### Mutation operators for code annotations.
| Short | Description             |
| ----- |:-----------------------:|
| ADA   | Add code annotation     |
| ADAT  | Add attribute           |
| CHODR | Change order            |
| RMA   | Remove code annotation  |
| RMAT  | Remove attribute        |
| RPA   | Replace code annotation |
| RPAT  | Replace attribute       |
| RPAV  | Replace value           |
| SWTG  | Switch target           |
