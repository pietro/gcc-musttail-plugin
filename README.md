# GCC musttail Plugin

This plugin adds the `musttail` attribute which when declared on a function will  mark all CALL_EXPRs as being mandatory for tail-call-optimization.

## Building

Just run `make` in this directory.

## Using

Add `__attribute__((musttail))` to the functions you want to force to have tail call optimization.

Then invoke GCC with the `-fplugin` option set to the path of the plugin .so file, ex:

``` shell
export PLUGIN=$(readlink -f must_tail_call_attribute_plugin.so)
gcc -fplugin="${PLUGIN}" -c YOU_SOURCE_FILE.c
```

## Disclaimer

This is an experimental plugin. It probably has a lot of bugs and generates wrong code. Use at you own risk.

## License

This plugin has mostly been adapted from the test plugin at `gcc/testsuite/gcc.dg/plugin/must_tail_call_plugin.c` in GCC's codebase from https://gcc.gnu.org/git/gcc.git and has the same license as GCC.

```
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING3.  If not, see
<https://www.gnu.org/licenses/>.
```

## Contact

Pietro Monteiro <pietro@sociotechnical.xyz>
