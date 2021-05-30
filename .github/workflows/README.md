This directory contains [GitHub Actions](https://github.com/features/actions) workflow files.


# Maintenance Schedule

`ubuntu-16.04` environment will be removed at September, 2021.
--------------------------------------------------------------

It also will remove test for the following compilers:

- gcc: 4.4, 4.6, 4.7
- clang: 3.5, 3.6, 3.7, 3.8

See also GitHub official announcement :
["Ubuntu 16.04 LTS will be removed on September 20, 2021"](https://github.blog/changelog/2021-04-29-github-actions-ubuntu-16-04-lts-virtual-environment-will-be-removed-on-september-20-2021/).


# Difference with `.travis.yml`

The following tests are not included yet.

- name: Compile OSS-Fuzz targets
- name: tag build
- name: aarch64 real-hw tests
- name: PPC64LE real-hw tests
- name: IBM s390x real-hw tests


# Known issues

## ubsan.yml

For now, `ubsan.yml` ignores the exit code of `make usan` and `make usan32`.
Because there're several issues which may take relatively long time to resolve.

We'll fully enable it when we ensure `make usan` is ready for all commits and PRs.

See https://github.com/lz4/lz4/pull/983 for details.


## c-compilers.yml

See also [c-compilers.yml.md](c-compilers.yml.md).

gcc-4.5 isn't included to this test.  Because it seems `gcc-4.5` isn't able to install to `ubuntu-16.04` by `apt-get`.

```
$ sudo apt-get install gcc-4.5 g++-4.5 gcc-multilib
...
The following packages have unmet dependencies:
 gcc-4.5 : Depends: libelfg0 (>= 0.8.12) but it is not installable
```





## cppcheck.yml

This test script ignores the exit code of `make cppcheck`.

Because this project doesn't 100% follow their recommendation.
Also sometimes it reports false positives.


# Notes

- You can investigate various information at the right pane of GitHub
  Actions report page.

| Item                      | Section in the right pane             |
| ------------------------- | ------------------------------------- |
| OS, VM                    | Set up job                            |
| git repo, commit hash     | Run actions/checkout@v2               |
| gcc, tools                | Environment info                      |

- To fail earlier, order of tests in the same job are roughly sorted by
  elapsed time.

- We use `make V=1` as much as possible.
  It helps to understand what causes error.
  And prevents to overlook basic mistakes.
