# my_ls

## Module: B-PSU-100 (Grade: N/A)

## Project Description
 Recreation of the linux command 'ls'

### USAGE
 ./my_ls [-l | -R | -t | -r | -a | file]+
# Result: 100% (Mark: 20)
<details>
<summary>Click to expand test results</summary>

### 01 - basic tests (100% Passed)
| Test | Status |
| --- | --- |
| Empty directory listing (test3) | PASSED |
| Multiple file listing (test1) | PASSED |
| Sanity check 2 - error handling (test32) | PASSED |
| Sanity check 3 - error handling (test33) | PASSED |
| Single file listing (test2) | PASSED |

### 02 - '-l' option tests (100% Passed)
| Test | Status |
| --- | --- |
| Access rights on directory (test11) | PASSED |
| Access rights on regular file (test8) | PASSED |
| Date (test9) | PASSED |
| File size (test6) | PASSED |
| No access right on regular file (test10) | PASSED |
| Sticky bit (test12) | PASSED |
| UID resolving (test7) | PASSED |

### 03 - '-R' option test (100% Passed)
| Test | Status |
| --- | --- |
| Recursive file listing (test13) | PASSED |

### 04 - combining option tests (100% Passed)
| Test | Status |
| --- | --- |
| Recursive listing (-lR) , testing access rights (test14) | PASSED |
| Recursive listing including hidden file (-l -R), separated options (test16) | PASSED |
| Recursive listing including hidden file (-lR) (test15) | PASSED |

### 05 - '-t' option tests (100% Passed)
| Test | Status |
| --- | --- |
| Time sorting #1 (test17) | PASSED |
| Time sorting #2 (test18) | PASSED |

### 06 - char device tests (100% Passed)
| Test | Status |
| --- | --- |
| Testing device type & major (test21) | PASSED |

</details>


## Bonuses
padding of the -l

