`c-compilers.yml` is GitHub Actions workflow definition file for testing compatibility of various C compilers.


# x32 incompatibility

The following compilers crashes during `-mx32` compilation.  We set `false` to its `${{ matrix.x32 }}`.

  - `clang-3.5`
  - `clang-3.6`
  - `clang-3.7`

The following compilers doesn't support x32.  We set `false` to its `${{ matrix.x32 }}`.

  - `gcc-4.4`
  - `gcc-4.5`
  - `gcc-4.6`
  - `gcc-4.7` : It claims it supports x32 but it seems it's unreliable.
