### `export`
    * marks variable to be exported when a new child `bash` is created
* `export` without args will print the bash env vars.

```shell
a=foo
echo $a
(foo)
bash
echo $a
()

a=foo
echo $a
(foo)
exprot a
bash
echo $a
(foo)
```

<br>

### `PATH`
* contains a list of dirs separated by ':'.
* Bash searches them for executables.
* users can add to path
    * `PATH=$PATH:<path>`
    * new PATH= old PATH + <path> (':' is the separator)

<br>

### PERMANENCE
* ~/.bashrc				# file containing bash env vars, among them PATH
* . ~/.bashrc				# reload .bashrc (the config file for vars such as PATH)




