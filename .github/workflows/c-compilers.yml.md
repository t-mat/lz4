`c-compilers.yml` is GitHub Actions workflow definition file for testing compatibility of various C compilers.

# `${{ matrix.??? }}` notation

It represents structured variable in `strategy.matrix.include` array in `c-compilers.yml`.


# gcc-4.5 on ubuntu-16.04

GitHub Action's `ubuntu-16.04` VM image doesn't maintain `gcc-4.5` package properly.  (Failed to install)


# x32

The following compilers crashes during `-mx32` compilation.  We set `false` to its `${{ matrix.x32 }}`.

  - `clang-3.5`
  - `clang-3.6`
  - `clang-3.7`

The following compilers doesn't support x32.  We set `false` to its `${{ matrix.x32 }}`.

  - `gcc-4.4`
  - `gcc-4.5`
  - `gcc-4.6`
  - `gcc-4.7` : It claims it supports x32 but it seems it's unreliable.
