## Repository Details

This repository is for the **Computer Systems Automated Design** (CSAD) labs. The repository follows the naming convention `csad<YY1YY2><group><student's full name><student's number>`. 

In this case, the repository name would be structured as: `csad2425ki404salahubao18`

Main development branch: **develop**

## Task1 Details

1. Create a GitHub repository with the name `csad2425ki404salahubao18`, where:
   - **YY1** is the start of the studying year: **24**
   - **YY2** is the end of the studying year: **25**
   - **Group** is the student's group identifier: **ki404**
   - **Full name** is the student's full name: **Salahub Andrii Olehovych**
   - **Student's number** is: **18**

2. Grant repository access to the author/lecturer.

3. Create a branch in the following format: `feature/develop/<task number>`.
   For this task, I named the branch `feature/develop/task1`.

4. README.md file will contain:
   - Details about the repository and task.
   - Information about the student's task as per Table 1.
   - Technology, programming language, and hardware details for the next tasks.

5. Create a Git tag in the format: `<PROJECT_NAME>_<VERSION>_WW<YYWWD>`, where:
   - **YY**: Current year
   - **WW**: Work week number
   - **D**: Current day number of the week

6. Create a pull request titled `task1` and assign the lecturer as a reviewer.

7. After the reviewer approves, merge the pull request into the `develop` branch.

## Student Details and details from Table 1

| **Student Number** | **Student Name**            | **Group** | **Game**            | **Config format** |
|--------------------|-----------------------------|-----------|---------------------|-------------------|
| 18                 | Salahub Andrii Olehovych    | KI-404    | rock paper scissors | INI               |


## Technologies, Programming Language, and Hardware

For the upcoming tasks, the following languages, and hardware will be used:

- **Programming Language**: C/C++ 
- **Hardware**: Arduino Nano 

## Task2 Details

- Create a simple communication schema SW(client) <-> UART <-> HW(server).
- The client should send a message to the server. The server should modify the message and send it back to the client.
- Create YML file with next features:
 a. build all binaries (create scripts in folder ci/ if need);
 b. run tests; 
 c. create artifacts with binaries and test reports;

## Task3 Details
   Develop Server and Client.
Play modes:
   - Man vs Man
   - Man vs AI (random)
   - Man vs AI (win strategy)
   - AI (random) vs AI (win strategy)
Action:
   - New game
   - Load game
   - Save game

