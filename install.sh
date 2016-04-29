#!/bin/bash

dest_path='./resource/texture'
pa="$dest_path/panoramic"
pl="$dest_path/planet"
se="$dest_path/seamless"

clear
printf "\033[36m"
# cat install_header
printf ",---.          |                             \n"
printf "|---',---.,   .|--- ,---.,---.,---.,---.,---.\n"
printf "|  \ ,---||   ||    |    ,---||    |---'|    \n"
printf "\`   \`\`---^\`---|\`---'\`    \`---^\`---'\`---'\`    \n"
printf "          \`---'                              \n"
printf "\033[0m"

#check if dest_path exist
if [ ! -d $dest_path ];
then
	printf "\033[1;31mDirectory \033[1;0m%s \033[1;31mdoesn't exist\033[0m\n" "$dest_path"
	printf "\033[1;32m   Creating it ... \033[0m\n"
	mkdir $dest_path
	if [ -d $dest_path ];
	then
		printf "   --> \033[1m%s \033[0mcreated\n" "$dest_path"
	else
		printf "\033[31m install.sh : Error %s can't be created\033[0m\n" " $dest_path"
		exit []

	fi
fi

#download texture
printf "\033[32m\nDownload textures...\n\n\033[0m"
printf "\033[47;30;1m $pa\033[0m\n"
curl -L -o $pa.zip 'https://www.dropbox.com/sh/yjisoobpjoz4xpw/AABQiSaKErSLip0hPy0PQywna/panoramic?dl=1'
printf "\033[47;30;1m $pl\033[0m\n"
curl -L -o $pl.zip 'https://www.dropbox.com/sh/yjisoobpjoz4xpw/AADDDID49c4hWVwdAVHrzt1Ma/planet?dl=1'
printf "\033[47;30;1m $se\033[0m\n"
curl -L -o $se.zip 'https://www.dropbox.com/sh/yjisoobpjoz4xpw/AAAtfA2vZKjadk10vwkbDLBoa/seamless?dl=1'

#unzip files
printf "\033[32m\nUnzip textures...\n\n\033[0m"
unzip -u $pa.zip -d $pa ; rm -rf $pa.zip
unzip -u $pl.zip -d $pl ; rm -rf $pl.zip
unzip -u $se.zip -d $se ; rm -rf $se.zip

printf "\033[47;30;1m --                                 -- \n\n\033[0m"
