#!/usr/bin/python
"""
The MIT License (MIT)

Copyright (c) 2015 coderzh

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
"""
import shlex
import argparse
import subprocess
import re

regex = re.compile(r"\s+.*\s([\?_]+.*)")

exclude = []


def gen_header_file_for_lib(lib_path, header_path):
    shell_cmd = 'dumpbin.exe /linkermember:1 {}'.format(lib_path)
    print(shell_cmd)
    cmd = shlex.split(shell_cmd)
    lines = execute_command(cmd)
    symbols = find_matches(lines, regex, exclude)

    with open(header_path, 'w') as f:
        header_guard = "LINK_ALL_SYMBOLS_H_"
        f.write("#ifndef " + header_guard + '\n')
        f.write("#define " + header_guard + '\n')
        f.write("// Generated by GenLinkerSymbols.py. Do not modify! \n\n")

        for symbol in symbols:
            pragma_line = '#pragma comment(linker, "/include:' + symbol + '")'
            f.write(pragma_line + '\n')
        f.write("\n#endif // " + header_guard + '\n')

    print("Link symbols count: %s" % len(symbols))


def execute_command(cmd):
    p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    (stdoutput,erroutput) = p.communicate()  
    std_out_lines = stdoutput.splitlines()
    return std_out_lines



def find_matches(lines, regex, exclude_list):
    def match(line):
        m = regex.match(line.decode('utf-8'))
        if m:
            return m.group(1).split()[0]
        return None

    def exclude_filter(line):
        if not line:
            return False

        for exclude in exclude_list:
            if line.find(exclude) >= 0:
                return False
        return True

    matches = filter(exclude_filter, map(match, lines))
    return list(set(matches))


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Gen linker all symbols header file')
    parser.add_argument('lib', help='.lib file path')
    parser.add_argument('header', help='output .h file path')
    args = parser.parse_args()
    print(args.lib, args.header)
    gen_header_file_for_lib(args.lib, args.header)