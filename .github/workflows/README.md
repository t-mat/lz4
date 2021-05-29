## Maintenance Schedule

This CI script will remove ubuntu-16.04.  It also removes test for the following compilers:

- gcc : 4.4, 4.6, 4.7
- clang: 3.5, 3.6, 3.7, 3.8

See also official announce from GitHub : ["Ubuntu 16.04 LTS will be removed on September 20, 2021"](https://github.blog/changelog/2021-04-29-github-actions-ubuntu-16-04-lts-virtual-environment-will-be-removed-on-september-20-2021/).


## Known issues

### ubsan.yml

For now, this CI script ignores the exit code of `make usan`.
Because there're several issues which may take relatively long time to resolve.

We'll fully enable it when we ensure `make usan` is ready for all commits and PRs.

See https://github.com/lz4/lz4/pull/983 for details.


### cppcheck.yml

This test script ignores the exit code of `cppcheck`.

Because this project doesn't 100% follow their recommendation.
Also sometimes it reports false positives.


## Notes

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


## Difference with .travis.yml

The following tests are not included yet.

- name: Compile OSS-Fuzz targets
- name: tag build
- name: aarch64 real-hw tests
- name: PPC64LE real-hw tests
- name: IBM s390x real-hw tests
