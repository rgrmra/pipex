#!/bin/bash

#make fclean all

echo -e "banana\nmaça\npera\npessego\nuva" > c

echo -e "\n\033[0;95mMANDATORY\033[0m"
echo -e "\n\033[0;93m01. Invalid infile:\033[0m"
echo -e "\033[0;92m< a grep a | grep b > /dev/null\033[0m"
< a grep a | grep b > /dev/null 
echo $? 
./pipex a "grep a" "grep b" b > /dev/null
echo $?
sleep 1

echo -e "\n\033[0;93m02. Invalid infile and first command:\033[0m"
echo -e "\033[0;92m< a ./Makefile | grep b > /dev/null\033[0m"
< a ./Makefile | grep b > /dev/null
echo $?
./pipex a ./Makefile grep\ b /dev/null
echo $?
sleep 1

echo -e "\n\033[0;93m03. Invalid infile and first command:\033[0m"
echo -e "\033[0;92m< a a | grep b > /dev/null\033[0m"
< a a | grep b > /dev/null
echo $?
./pipex a a grep\ b /dev/null
echo $?
sleep 1

echo -e "\n\033[0;93m04. Invalid infile and secound command:\033[0m"
echo -e "\033[0;92m< a grep b | ./Makefile > /dev/null\033[0m"
< a grep b | ./Makefile > /dev/null
echo $?
./pipex a grep\ b ./Makefile /dev/null
echo $?
sleep 1

echo -e "\n\033[0;93m05. Invalid infile and secound command:\033[0m"
echo -e "\033[0;92m< a grep b | a > /dev/null\033[0m"
< a grep b | a > /dev/null
echo $?
./pipex a grep\ b a /dev/null
echo $?
sleep 1

echo -e "\n\033[0;93m06. Get banana from file to terminal :\033[0m"
echo -e "\033[0;92m< c grep a | grep b > /dev/tty\033[0m"
< c grep a | grep b > /dev/tty
echo $?
./pipex c grep\ a grep\ b /dev/tty
echo $?
sleep 1

echo -e "\n\033[0;93m07. Get bonono from file to terminal:\033[0m"
echo -e "\033[0;92m< c grep a | tr 'a' 'o' > /dev/tty\033[0m"
< c grep b | tr 'a' 'o' > /dev/tty
echo $?
./pipex c grep\ b tr\ 'a'\ 'o' /dev/tty
echo $?
sleep 1

echo -e "\n\033[0;93m08. Get a and transform to o and get from file:\033[0m"
echo -e "\033[0;92m< c grep a | tr 'a' 'o' > b && cat b\033[0m"
< c grep a | tr 'a' 'o' > b
echo $?
cat b
./pipex c grep\ a tr\ 'a'\ 'o' d
echo $?
cat d
sleep 1

echo -e "\n\033[0;93m09. Get a and count lines:\033[0m"
echo -e "\033[0;92m< c grep a | wc -l > b && cat b\033[0m"
< c grep a | wc -l > b
echo $?
cat b
./pipex c grep\ a wc\ -l d
echo $?
cat d
sleep 1

echo -e "\n\033[0;93m10. Get a and count words:\033[0m"
echo -e "\033[0;92m< c grep a | wc -w > b && cat b\033[0m"
< c grep a | wc -w > b
echo $?
cat b
./pipex c grep\ a wc\ -w d
echo $?
cat d
sleep 1

echo -e "\n\033[0;93m11. Get list files and count lines:\033[0m"
echo -e "\033[0;92m< c ls -l | wc -l > b && cat b\033[0m"
< c ls -l | wc -l > b
echo $?
cat b
./pipex c ls\ -l wc\ -l d
echo $?
cat d
sleep 1

echo -e "\n\033[0;93m12. Get list and words that start with -rw-:\033[0m"
echo -e "\033[0;92m< a ls -l | grep ^-rw- > b && cat b\033[0m"
< c ls -l | grep ^-rw- > b
echo $?
cat b
./pipex c ls\ -l grep\ ^-rw- d
echo $?
cat d
sleep 1

echo -e "\n\033[0;93m13. Get list and directories:\033[0m"
echo -e "\033[0;92m< a ls -la | grep ^d > b && cat b\033[0m"
< c ls -la | grep ^d > b
echo $?
cat b
./pipex c ls\ -la grep\ ^d d
echo $?
cat d
sleep 1

echo -e "\n\033[0;93m14. Get the whole path:\033[0m"
echo -e "\033[0;92m< a /usr/bin/grep a | /usr/bin/wc -w > b && cat b\033[0m"
< c /usr/bin/grep a | /usr/bin/wc -w > b
echo $?
cat b
./pipex c /usr/bin/grep\ a /usr/bin/wc\ -w d
echo $?
cat d
sleep 1

echo -e "\n\033[0;93m15. Get the whole path, first invalid:\033[0m"
echo -e "\033[0;92m< a /usr/bin/grepp a | /usr/bin/wc -w > b && cat b\033[0m"
< c /usr/bin/grepp a | /usr/bin/wc -w > b
echo $?
cat b
./pipex c "/usr/bin/grepp a" "/usr/bin/wc -w" d
echo $?
cat d
sleep 1

echo -e "\n\033[0;93m16. Get the whole path, secound invalid:\033[0m"
echo -e "\033[0;92m< a /usr/bin/grep a | /usr/bin/wcc -w > b && cat b\033[0m"
< c /usr/bin/grep a | /usr/bin/wcc -w > b
cat b
echo $?
./pipex c "/usr/bin/grep a" "/usr/bin/wcc -w" d
echo $?
cat d
sleep 1

echo -e "\n\033[0;93m17. No parameters:\033[0m"
echo -e "\033[0;92m./pipex\033[0m"
./pipex
echo $?
sleep 1

echo -e "\n\033[0;93m18. One arguments:\033[0m"
echo -e "\033[0;92m./pipex c\033[0m"
./pipex c
echo $?
sleep 1

echo -e "\n\033[0;93m19. Two arguments:\033[0m"
echo -e "\033[0;92m./pipex c grep\\ a\033[0m"
./pipex c grep\ a
echo $?
sleep 1

echo -e "\n\033[0;93m20. Three argumets:\033[0m"
echo -e "\033[0;92m./pipex c grep\\ a grep\\ b\033[0m"
./pipex c grep\ a grep\ b
echo $?
sleep 1

echo -e "\n\033[0;93m21. Five arguments:\033[0m"
echo -e "\033[0;92m./pipex c grep\\ a grep\\ b grep\ c d\033[0m"
./pipex c grep\ a grep\ b grep\ c d
echo $?
sleep 1

chmod 000 c

echo -e "\n\033[0;93m22. Input file no permition:\033[0m"
echo -e "\033[0;92m< a grep a | grep b > b && cat b\033[0m"
< c grep a | grep b > b
echo $?
cat b
./pipex c grep\ a grep\ b d
echo $?
cat d
sleep 1

chmod 655 c
chmod 000 d b

echo -e "\n\033[0;93m23. Input file no permition:\033[0m"
echo -e "\033[0;92m< a grep a | grep b > b && cat b\033[0m"
< c grep a | grep b > b
echo $?
./pipex c grep\ a grep\ b d
echo $?
sleep 1

chmod 655 d b

echo -e "\n\033[0;93m24. Null first command:\033[0m"
echo -e "\033[0;92m< a "" | grep b > b && cat b\033[0m"
< c "" | grep b > b
echo $?
./pipex c "" grep\ b d
echo $?
sleep 1

echo -e "\n\033[0;93m25. Null secound command:\033[0m"
echo -e "\033[0;92m< a grep a | "" b && cat b\033[0m"
< c grep b | "" > b
echo $?
cat b
./pipex c grep\ b "" d
echo $?
cat d
sleep 1

echo -e "\n\033[0;93m26. Two null commands:\033[0m"
echo -e "\033[0;92m< a "" | "" b && cat b\033[0m"
< c "" | "" > b
echo $?
cat b
./pipex c "" "" d
echo $?
cat d
sleep 1

chmod 000 c d b

echo -e "\n\033[0;93m26. Two null commands and no permition files:\033[0m"
echo -e "\033[0;92m< a "" | "" b && cat b\033[0m"
< c "" | "" > b
echo $?
./pipex c "" "" d
echo $?
sleep 1

chmod 655 c d b

rm -rf b c d
