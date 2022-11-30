for i in $(seq -w 1 163); do
	python3 K.py < `ls ./data/secret/$i-*.in` > k.out
	python3 -c "import glob; \
		from decimal import *; \
		f1 = open('k.out', 'r').read().strip(); \
		f2 = open(glob.glob('./data/secret/$i-*.ans')[0], 'r').read().strip(); \
		assert(f1.lower() == f2.lower()); \
		print('Checked test case $i')"
done
