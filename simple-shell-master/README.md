# Code from https://github.com/drunkcoding/simple-shell
# This is the pro|ect of a simple shell
Makefile run for Linux/Minix by make (clang)

- 1. Write a working read/parse/execute loop and an exit command;
- 2. Clean exit, no memory leaks in any circumstance;
- 3. Handle single commands without arguments (e.g. ls);
- 4. Support commands with arguments (e.g. apt‐get update or pkgin update);
- 5. File I/O redirection:
    - 5.1. Output redirection by overwriting a file (e.g. echo 123 > 1.txt);
    - 5.2. Output redirection by appending to a file (e.g. echo 465 >> 1.txt);
    - 5.3. Input redirection (e.g. cat < 1.txt);
    - 5.4. Combine 5.1 and 5.2 with 5.3;
- 6. Support for bash style redirection syntax (e.g. cat < 1.txt 2.txt > 3.txt 4.txt); [Not yet supported for no space seperation]
- 7. Pipes: 
    - 7.1. Basic pipe support (e.g. echo 123 | grep 1);
    - 7.2. Run all ‘stages’ of piped process in parallel. (e.g. yes ve482 | grep 482);
    - 7.3. Extend 7.2 to support requirements 5 and 6 (e.g. cat < 1.txt 2.txt | grep 1 > 3.txt);
    - 7.4. Extend 7.3 to support arbitrarily deep \cascade pipes" (e.g. echo 123 | grep 1 | grep 1 | grep 1)
- 8. Support CTRL‐D (similar to bash, when there is no/an unfinished command);
- 9. Internal commands:
    - 9.1. Implement pwd as a built‐in command;
    - 9.2. Allow changing working directory using cd;
    - 9.3. Allow pwd to be piped or redirected as specified in requirement 5; [Not yet supported]
- 10. Support CTRL‐C:
    - 10.1. Properly handle CTRL‐C in the case of requirement 5;
    - 10.2. Extend 10.1 to support subtasks 7.1 to 7.3;
    - 10.3. Extend 10.2 to support requirement 8, especially on an incomplete input;
    - 10.4. Extend 10.3 to support requirement 7;
- 11. Support quotes: [Not yet supported]
    - 11.1. Handle single and double quotes (e.g. echo "de'f' ghi" '123"a"bc' a b c);
    - 11.2. Extend 11.1 to support requirement 5 and subtasks 7.1 to 7.3;
    - 11.3. Extend 11.2 in the case of incomplete quotes (e.g. Input echo "de, hit enter and input cd");
    - 11.4. Extend 11.3 to support requirements 5 and 7, together with subtask 10.3;
- 12. Wait for the command to be completed when encountering >, <, or |:
    - 12.1. Support requirements 4 and 5 together with subtasks 7.1 to 7.3;
    - 12.2. Extend 12.1 to support requirement 11 [Not yet supported]
