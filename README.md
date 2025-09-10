# colr (Colorized Regex)
Handy tool to highlight piped text

### Usage

`colr [ -<color> <pattern> ...]`

Examples

- highlight the word `blue` in blue
`cat file.txt | colr -b blue`

- highlight ok and error
`make test | colr -r ERROR -g OK`

### Colors
| flag | color |
| --- | --- |
| -r | red |
| -g | green |
| -y | yellow |
| -b | blue |
| -m | magenta |
| -c | cyan |
| -e[4m | ansi escape code |
| -xABC012 | hex color (truecolor) |

### Issues

- Doesn't support regex (even though its in the name)

### Future plans
- [ ] Actually implement regex
- [x] Improve stupid table for colors
- [x] More colors
- [x] Fix "page boundary" issues

