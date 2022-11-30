for i in $(seq -w 1 26); do
	python3 B.py < $(ls ./data/secret/$i-*.in) > b.out
	python3 -c "import glob; \
		f1 = open(glob.glob('./data/secret/$i-*.ans')[0]).read(); \
		f2 = open('b.out').read(); \
		assert(abs(float(f1) - float(f2)) < 1e-6); \
		print('Passed test case $i')
	"
done
