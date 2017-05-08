#bash script for comparing a file outputted by indexer.c and a file outputted by indextest.c
# Yifei Yan
# May 2017


gawk -f indexsort.awk indexFile > indexFile.sorted
gawk -f indexsort.awk indexFileTested > indexFileTested.sorted


cmp -s indexFile.sorted indexFileTested.sorted

if [ $? == 0 ]
then
	echo the two files are the same
else
    echo  the two files are not the same
fi

exit 0
