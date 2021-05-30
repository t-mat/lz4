`c-compilers.yml` is GitHub Actions workflow definition file for testing compatibility of various C compilers.


# Known `make c_standards` incompatibility

- `gcc-4.4` [doesn't have](https://gcc.gnu.org/onlinedocs/gcc-4.4.7/gcc/C-Dialect-Options.html#C-Dialect-Options)
  gcc compatible `-std=c90` and `-std=gnu90` compiler switch.  We set `false` to its `${{ matrix.stdc90 }}`.


# Known `make cxxtest` incompatibility

- When we run `make cxxtest` for `clang-3.9`, it shows issue about `__STRICT_ANSI__`.  We set `false` to its `${{ matrix.cxxtest }}` because all other versions of `clang` works fine.


# Known x32 incompatibility

The following compilers crashes during `-mx32` compilation.  We set `false` to its `${{ matrix.x32 }}`.

  - `clang-3.5`
  - `clang-3.6`
  - `clang-3.7`

The following compilers doesn't support x32.  We set `false` to its `${{ matrix.x32 }}`.

  - `gcc-4.4`
  - `gcc-4.5`
  - `gcc-4.6`
  - `gcc-4.7` : It claims it supports x32 but it seems it's unreliable.
