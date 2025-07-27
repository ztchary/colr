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

### Issues

- Doesn't support regex (even though its in the name)
- Reads chunks from stdin which causes issues on boundaries, should read line by line

### Future plans
- [ ] Actually implement regex
- [ ] Improve stupid table for colors
- [ ] More colors
- [ ] Fix "page boundary" issues

