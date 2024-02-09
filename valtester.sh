#!/bin/bash

val="valgrind --leak-check=full --track-fds=yes --trace-children=yes"

if [[ $1 ]];
then
	make fclean bonus;
	echo -e "\n\033[0;95mBONUS\033[0m"
else
	make fclean all;
	echo -e "\n\033[0;95mMANDATORY\033[0m"
fi

rm -rf b c d folder

echo -e "banana\nmaça\npera\npessego\nuva" > c

echo -e "\n\033[0;93m01. Invalid infile:\033[0m"
echo -e "\033[0;92m< a grep a | grep b > /dev/null\033[0m"
$val ./pipex a "grep a" "grep b" b > /dev/null
sleep 1

echo -e "\n\033[0;93m02. Invalid infile and first command:\033[0m"
echo -e "\033[0;92m< a ./Makefile | grep b > /dev/null\033[0m"
$val ./pipex a ./Makefile grep\ b /dev/null
sleep 1

echo -e "\n\033[0;93m03. Invalid infile and first command:\033[0m"
echo -e "\033[0;92m< a a | grep b > /dev/null\033[0m"
$val ./pipex a a grep\ b /dev/null
sleep 1

echo -e "\n\033[0;93m04. Invalid infile and secound command:\033[0m"
echo -e "\033[0;92m< a grep b | ./Makefile > /dev/null\033[0m"
$val ./pipex a grep\ b ./Makefile /dev/null
sleep 1

echo -e "\n\033[0;93m05. Invalid infile and secound command:\033[0m"
echo -e "\033[0;92m< a grep b | a > /dev/null\033[0m"
$val ./pipex a grep\ b a /dev/null
sleep 1

echo -e "\n\033[0;93m06. Get banana from file to terminal :\033[0m"
echo -e "\033[0;92m< c grep a | grep b > /dev/tty\033[0m"
$val ./pipex c grep\ a grep\ b /dev/tty
sleep 1

echo -e "\n\033[0;93m07. Get bonono from file to terminal:\033[0m"
echo -e "\033[0;92m< c grep a | tr 'a' 'o' > /dev/tty\033[0m"
$val ./pipex c grep\ b tr\ 'a'\ 'o' /dev/tty
sleep 1

echo -e "\n\033[0;93m08. Get a and transform to o and get from file:\033[0m"
echo -e "\033[0;92m< c grep a | tr 'a' 'o' > b && cat b\033[0m"
$val ./pipex c grep\ a tr\ 'a'\ 'o' d
sleep 1

echo -e "\n\033[0;93m09. Get a and count lines:\033[0m"
echo -e "\033[0;92m< c grep a | wc -l > b && cat b\033[0m"
$val ./pipex c grep\ a wc\ -l d
sleep 1

echo -e "\n\033[0;93m10. Get a and count words:\033[0m"
echo -e "\033[0;92m< c grep a | wc -w > b && cat b\033[0m"
$val ./pipex c grep\ a wc\ -w d
sleep 1

echo -e "\n\033[0;93m11. Get list files and count lines:\033[0m"
echo -e "\033[0;92m< c ls -l | wc -l > b && cat b\033[0m"
$val ./pipex c ls\ -l wc\ -l d
sleep 1

echo -e "\n\033[0;93m12. Get list and words that start with -rw-:\033[0m"
echo -e "\033[0;92m< a ls -l | grep ^-rw- > b && cat b\033[0m"
$val ./pipex c ls\ -l grep\ ^-rw- d
sleep 1

echo -e "\n\033[0;93m13. Get list and directories:\033[0m"
echo -e "\033[0;92m< a ls -la | grep ^d > b && cat b\033[0m"
$val ./pipex c ls\ -la grep\ ^d d
sleep 1

echo -e "\n\033[0;93m14. Get the whole path:\033[0m"
echo -e "\033[0;92m< a /usr/bin/grep a | /usr/bin/wc -w > b && cat b\033[0m"
$val ./pipex c /usr/bin/grep\ a /usr/bin/wc\ -w d
sleep 1

echo -e "\n\033[0;93m15. Get the whole path, first invalid:\033[0m"
echo -e "\033[0;92m< a /usr/bin/grepp a | /usr/bin/wc -w > b && cat b\033[0m"
$val ./pipex c "/usr/bin/grepp a" "/usr/bin/wc -w" d
sleep 1

echo -e "\n\033[0;93m16. Get the whole path, secound invalid:\033[0m"
echo -e "\033[0;92m< a /usr/bin/grep a | /usr/bin/wcc -w > b && cat b\033[0m"
$val ./pipex c "/usr/bin/grep a" "/usr/bin/wcc -w" d
sleep 1

echo -e "\n\033[0;93m17. No parameters:\033[0m"
echo -e "\033[0;92m./pipex\033[0m"
$val ./pipex
sleep 1

echo -e "\n\033[0;93m18. One arguments:\033[0m"
echo -e "\033[0;92m./pipex c\033[0m"
$val ./pipex c
sleep 1

echo -e "\n\033[0;93m19. Two arguments:\033[0m"
echo -e "\033[0;92m./pipex c grep\\ a\033[0m"
$val ./pipex c grep\ a
sleep 1

echo -e "\n\033[0;93m20. Three argumets:\033[0m"
echo -e "\033[0;92m./pipex c grep\\ a grep\\ b\033[0m"
$val ./pipex c grep\ a grep\ b
sleep 1

echo -e "\n\033[0;93m21. Five arguments:\033[0m"
echo -e "\033[0;92m./pipex c grep\\ a grep\\ b grep\ c d\033[0m"
$val ./pipex c grep\ a grep\ b grep\ c d
sleep 1

chmod 000 c

echo -e "\n\033[0;93m22. Input file no permition:\033[0m"
echo -e "\033[0;92m< a grep a | grep b > b && cat b\033[0m"
$val ./pipex c grep\ a grep\ b d
sleep 1

chmod 655 c
chmod 000 d b

echo -e "\n\033[0;93m23. Input file no permition:\033[0m"
echo -e "\033[0;92m< a grep a | grep b > b\033[0m"
$val ./pipex c grep\ a grep\ b d
sleep 1

chmod 655 d b

echo -e "\n\033[0;93m24. Null first command:\033[0m"
echo -e "\033[0;92m< a \"\" | grep b > b && cat b\033[0m"
$val ./pipex c "" grep\ b d
sleep 1

echo -e "\n\033[0;93m25. Null secound command:\033[0m"
echo -e "\033[0;92m< a grep a | \"\" > b && cat b\033[0m"
$val ./pipex c grep\ b "" d
sleep 1

echo -e "\n\033[0;93m26. Two null commands:\033[0m"
echo -e "\033[0;92m< a \"\" | \"\" > b && cat b\033[0m"
$val ./pipex c "" "" d
sleep 1

chmod 000 c d b

echo -e "\n\033[0;93m27. Two null commands and no permition files:\033[0m"
echo -e "\033[0;92m< a \"\" | \"\" > b\033[0m"
$val ./pipex c "" "" d
sleep 1

chmod 655 c d b

mkdir folder

echo -e "\n\033[0;93m28. Secound command is a directory.\033[0m"
echo -e "\033[0;92m< a ./folder/ | cat > b\033[0m"
$val ./pipex c "cat" "./folder/" d
sleep 1

echo -e "\n\033[0;93m29. First command is a directory.\033[0m"
echo -e "\033[0;92m< a ./folder/ | cat > b\033[0m"
$val ./pipex c "./folder/" "cat" d
sleep 1

echo -e "\n\033[0;93m30. Both commands are directories.\033[0m"
echo -e "\033[0;92m< a ./folder/ | ./folder/ > b\033[0m"
$val ./pipex c "./folder/" "./folder/" d
sleep 1

echo -e "\n\033[0;93m31. Both commands are directories with first slash.\033[0m"
echo -e "\033[0;92m< a ./folder | ./folder > b\033[0m"
$val ./pipex c "./folder" "./folder" d
sleep 1

echo -e "\n\033[0;93m32. Both commands are directories with last slash.\033[0m"
echo -e "\033[0;92m< a folder/ | folder/ > b\033[0m"
$val ./pipex c "folder/" "folder/" d
sleep 1

echo -e "\n\033[0;93m33. Both commands are directories without slash.\033[0m"
echo -e "\033[0;92m< a folder | folder > b\033[0m"
$val ./pipex c "folder" "folder" d
sleep 1

echo -e "\n\033[0;93m34. Test some spaces.\033[0m"
echo -e "\033[0;92m< a grep            ^d | tr      ' '         'o'  > b\033[0m"
$val ./pipex c "grep            ^d" "tr      ' '         'o'" b
sleep 1

echo -e "\n\033[0;93m35. Something unusual.\033[0m"
echo -e "\033[0;92m< /dev/urandom cat | head -1 > b\033[0m"
$val ./pipex /dev/urandom "cat" "head -1" d
sleep 1

rm -rf b c d folder
