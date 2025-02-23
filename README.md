# ft_irc
IRC Server

## Milestones

| Status | Milestone |
| --- | --- |
| &check; | TCP Server Non-Blocking Implementation |
| &check; | Lexical Analysis and Command Parsing |
| &check; | User Class and Basic Command Handling |
| &cross; | Mandatadory Commands Handling |


## How to use

```bash
ircserv 12345 pass
# or
make run
```

## Commands

- CAP
- PASS
- NICK
- USER

<!-- &check; -->
<!-- <input type="checkbox" disabled checked /> -->



git branch
git checkout -b branch3
git push -u origin branch3

telnet localhost 4444
PASS 123123
NICK serg
USER serg 0 * :serg Ivanov
JOIN #test
PRIVMSG serg :HELLO
PRIVMSG #test :HELLO group
KICK #test dim : spam

telnet localhost 4444
PASS 123123
NICK dim
USER dim 0 * :dim suh
JOIN #test
PRIVMSG dim :HELLO




KICK #test dim :Spamming or any reason
PRIVMSG dim : Hello
