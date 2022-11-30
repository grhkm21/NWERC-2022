for i in $(seq -w 1 32); do
	python3 C.py < `ls ./data/secret/$i-*.in` > c.out
	python3 -c "import glob; \
		from decimal import *; \
		f1 = Decimal(open('c.out', 'r').read()); \
		f2 = Decimal(open(glob.glob('./data/secret/$i-*.ans')[0], 'r').read()); \
		assert(abs(f1 - f2) < 1e-6); \
		print('Passed test case $i')"
done
